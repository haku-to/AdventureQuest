#include "Fighter.h"
#include "World/IWorld.h"
#include "Rendering/Field.h"
#include "Rendering/Line.h"
#include "Collision/AttackCollider.h"
#include "Assets.h"
#include "Music/SE.h"
#include "Common_Number.h"

//HPスペル位置
const  GSvector2 UIposition_HP_Spel{ 0.0f,0.0f };
const  GSvector2 UIscale_HP_Spel{ 0.7f,0.7f };
//体力
const GSvector2 UIposition_HP_Bar{ 65.0f, 5.0f };
//体力フレーム
const GSvector2 UIposition_HP_Frame{ 65.0f, 0.0f };
// モーション番号
enum {
	Motion_Idle,       //アイドルモーション
	Motion_Down,	   //ダウンモーション
	Motion_Attack2,	   //攻撃モーション２
	Motion_Attack3,	   //攻撃モーション３
	Motion_Attack1,	   //攻撃モーション１
	Motion_Victory,	   //勝利モーション
	Motion_Damage,	   //ダメージモーション
	Motion_Dodge,	   //回避モーション
	Motion_Walk,	   //歩きモーション
	Motion_Run,		   //走りモーション
};

// 移動速度
const float WalkSpeed{ 0.1f };
//ダッシュ速度
const float RunSpeed{ 0.2f };
//回避速度
const float DodgeSpeed{ 0.1f };
// 自分の高さ
const float PlayerHeight{ 1.0f };
// 衝突判定用の半径
const float PlayerRadius{ 0.5f };
// 足元のオフセット
const float FootOffset{ 0.1f };
// 重力
const float Gravity{ -0.016f };

// コンストラクタ
Fighter::Fighter(IWorld* world, const GSvector3& position) :
	mesh_{ Mesh_Fighter, Mesh_Fighter, Mesh_Fighter, Motion_Idle },
	motion_{ Motion_Idle },
	motion_loop_{ true },
	is_running_{ false },
	can_start_{ false },
	state_{ State::Move },
	state_timer_{ 0.0f },
	start_timer_{ 360.0f },
	pushed_button_timer_{ 0.0f },
	attack_num_{ 1 },
	can_attack_{ false },
	health_{ 10.0f } {
	// ワールドの設定
	world_ = world;
	// タグ名の設定
	tag_ = "PlayerTag";
	// 名前の設定
	name_ = "Fighter";
	// 衝突判定球の設定
	collider_ = BoundingSphere{ PlayerRadius, GSvector3{0.0f, PlayerHeight, 0.0f} };
	// 座標の初期化
	transform_.position(position);
	// メッシュの変換行列を初期化
	mesh_.transform(transform_.localToWorldMatrix());
	///スポーン時方向
	transform_.rotate(0.0f, 50.0f, 0.0f);
}

// 更新
void Fighter::update(float delta_time) {
	// 状態の更新
	update_state(delta_time);
	// 重力値を更新
	velocity_.y += Gravity * delta_time;
	// 重力を加える
	transform_.translate(0.0f, velocity_.y, 0.0f);
	// フィールドとの衝突判定
	collide_field();
	// モーションを変更
	mesh_.change_motion(motion_, motion_loop_);
	// メッシュを更新
	mesh_.update(delta_time);
	// 行列を設定
	mesh_.transform(transform_.localToWorldMatrix());
	can_start_ = true;
	//体力カラー変更
	if (health_ >= 6) {
		health_color_G = 1.0f;
		health_color_R = 0.0f;
		health_color_B = 0.0f;
	}
	else if (health_ >= 3) {
		health_color_G = 1.0f;
		health_color_R = 1.0f;
		health_color_B = 0.0f;
	}
	else {
		health_color_G = 0.0f;
		health_color_R = 1.0f;
		health_color_B = 0.0f;
	}
	if (Common_Number::is_game_clear_) {
		Common_Number::is_fighter_win_ = true;
		change_state(State::Victory, Motion_Victory, true);
	}
}

// 描画
void Fighter::draw() const {
	// メッシュを描画
	mesh_.draw();
	// 衝突判定のデバッグ表示
	//collider().draw();
}

void Fighter::draw_gui() const {
	gsDrawSprite2D(UI_HP_Spel, &UIposition_HP_Spel, NULL, NULL, NULL, &UIscale_HP_Spel, 0.0f);
	//体力ゲージサイズ
	GSvector2 UIscale_HP_{ health_, 0.5f };
	GScolor4 UIcolor_HP_Bar{ health_color_R,health_color_G,health_color_B,1.0f };
	//gsDrawSprite2D(UI_HP_Frame, &UIposition_HP_Frame, NULL, NULL, NULL, &UIscale_HPspel, 0.0f);
	gsDrawSprite2D(UI_Player_HP_Bar, &UIposition_HP_Bar, NULL, NULL, &UIcolor_HP_Bar, &UIscale_HP_, 0.0f);
}

// 衝突リアクション
void Fighter::react(Actor& other) {
	// ダメージ、回避、死亡、防御中の場合は何もしない
	if (state_ == State::Damage || state_ == State::Dodge || state_ == State::Dead) return;
	// 敵の攻撃判定と衝突したか？
	if (other.tag() == "EnemyAttackTag" || other.tag() == "MageAttackTag") {
		SE::PlaySE(SE_Fighter_Damage);
		is_damage_ = true;
		// ターゲット方向のベクトルを求める
		GSvector3 to_target = other.transform().position() - transform().position();
		// ｙ成分は無効にする
		to_target.y = 0.0f;
		// ターゲット方向と逆方向にノックバックする移動量を求める
		velocity_ = -to_target.getNormalized() * 0.25f;
		//体力減少
		health_ -= 1;// ダメージ状態に遷移する
		if (health_ > 0) {
			change_state(State::Damage, Motion_Damage, false);
		}
		else
		{
			SE::PlaySE(SE_Fighter_Down);
			change_state(State::Dead, Motion_Down, false);
		}
		return;
	}
	// 敵と衝突したか？
	if (other.tag() == "EnemyBossTag" || other.tag() == "EnemyTag" || other.tag() == "InvisibleWallTag") {
		// アクター同士の衝突処理
		collide_actor(other);
	}
}
// 状態の更新
void Fighter::update_state(float delta_time) {
	// 状態遷移
	switch (state_) {
	case State::Move:   move(delta_time);   break;
	case State::Attack1: attack(delta_time); break;
	case State::Attack2: attack2(delta_time); break;
	case State::Dodge: dodge(delta_time); break;
	case State::Damage: damage(delta_time); break;
	case State::Dead: dead(delta_time); break;
	}
	state_timer_ += delta_time;
}

// 状態の変更
void Fighter::change_state(State state, GSuint motion, bool loop) {
	// モーション番号の更新
	motion_ = motion;
	// モーションのループ指定
	motion_loop_ = loop;
	// 状態の更新
	state_ = state;
	// 状態タイマの初期化
	state_timer_ = 0.0f;
}

// 移動処理
void Fighter::move(float delta_time) {
	if (can_start_) {
		//ダメージを受けてないときだけ攻撃可能
		if (is_damage_ == false)
		{
			// Xボタンで攻撃１
			if (gsGetJoyTrigger(0, GJOY_BUTTON_3))
			{
				// 攻撃状態に遷移する
				SE::PlaySE(SE_Fighter_Attack1);
				change_state(State::Attack1, Motion_Attack1);
				attack_num_ = 1;
				can_attack_ = true;
				return;
			}
		}
		//Aボタンで回避
		if (gsGetJoyTrigger(0, GJOY_BUTTON_1)) {
			// 回避状態に遷移する
			change_state(State::Dodge, Motion_Dodge);
			return;
		}
		// カメラの前方向ベクトルを取得
		GSvector3 forward = world_->camera()->transform().forward();
		forward.y = 0.0f;
		// カメラの右方向ベクトルを取得
		GSvector3 right = world_->camera()->transform().right();
		right.y = 0.0f;
		// 座標を取得
		GSvector3 position = transform_.position();
		//// キーの入力値から移動量を計算
		GSvector3 velocity{ 0.0f, 0.0f, 0.0f };
		//Lスティックの入力
		GSvector2 lAxis;
		float speed;
		gsXBoxPadGetLeftAxis(0, &lAxis);
		// 移動しなければアイドル状態
		GSint motion{ Motion_Idle };
		//RBボタンが押されているか
		if (gsXBoxPadButtonState(0, GS_XBOX_PAD_RIGHT_SHOULDER)) {
			//走りパラメータ
			speed = RunSpeed;
			is_running_ = true;
		}
		else {
			//歩きパラメータ
			speed = WalkSpeed;
			is_running_ = false;
		}

		// 移動量を計算する
		velocity = forward.normalized() * lAxis.y * speed * delta_time +
			right * lAxis.x * speed * delta_time;
		// 移動しているか？
		if (velocity.lengthSq() != 0.0f) {
			// 向きの補間
			GSquaternion rotation =
				GSquaternion::rotateTowards(transform_.rotation(), GSquaternion::lookRotation(velocity), 30.0f * delta_time);
			transform_.rotation(rotation);
			// 移動中のモーションにする
			if (is_running_) motion = Motion_Run;
			else motion = Motion_Walk;
		}
		// モーションの変更
		change_state(State::Move, motion);
		// 移動量のxz成分を更新
		velocity_.x = velocity.x;
		velocity_.z = velocity.z;
		// 平行移動する（ワールド基準）
		transform_.translate(velocity_, GStransform::Space::World);
	}
}

// 攻撃中
void Fighter::attack(float delta_time) {
	// 攻撃モーションの終了を待つ
	if (state_timer_ >= mesh_.motion_end_time() * 0.7f) {
		move(delta_time);
	}
	if (state_timer_ > mesh_.motion_end_time() * 0.4f && is_damage_ == false) {
		if (attack_num_ == 1 && gsGetJoyTrigger(0, GJOY_BUTTON_3)) {
			// 攻撃状態に遷移する
			change_state(State::Attack1, Motion_Attack2);
			attack_num_ = 2;
			SE::PlaySE(SE_Fighter_Attack2);
			can_attack_ = true;
			return;
		}
		else if (attack_num_ == 2 && gsGetJoyTrigger(0, GJOY_BUTTON_3)) {
			// 攻撃状態に遷移する
			change_state(State::Attack1, Motion_Attack3);
			attack_num_ = 3;
			SE::PlaySE(SE_Fighter_Attack3);
			can_attack_ = true;
			return;
		}
	}
	if (state_timer_ >= mesh_.motion_end_time() * 0.2f && can_attack_) {
		generate_attack_collider("PlayerAttack", "FighterAttackTag", 0.0f);
		can_attack_ = false;
	}
	if (state_timer_ >= mesh_.motion_end_time() * 0.9f && can_attack_ && attack_num_ == 3) {
		generate_attack_collider("PlayerAttack", "FighterAttackTag", 0.0f);
		can_attack_ = false;
	}

	//攻撃中少し前進
	if (state_timer_ <= mesh_.motion_end_time() * 0.3f) {
		GSvector3 forward = transform().forward();
		forward.y = 0.0f;
		GSvector3 velocity = forward.normalize() * 0.03;
		// 平行移動する（ワールド基準）
		transform_.translate(velocity, GStransform::Space::World);
	}
	//回避で攻撃を中止
	if (gsGetJoyTrigger(0, GJOY_BUTTON_1) && state_timer_ >= mesh_.motion_end_time() * 0.4f) {
		change_state(State::Dodge, Motion_Dodge);
		return;
	}
}

// 攻撃中
void Fighter::attack2(float delta_time) {
	// 攻撃モーションの終了を待つ
	if (state_timer_ >= mesh_.motion_end_time()) {
		move(delta_time);
	}
	//攻撃中少し前進
	if (state_timer_ <= mesh_.motion_end_time() * 0.3f) {
		GSvector3 forward = transform().forward();
		forward.y = 0.0f;
		GSvector3 velocity = forward.normalize() * 0.03;
		// 平行移動する（ワールド基準）
		transform_.translate(velocity, GStransform::Space::World);
	}
}
//回避中
void Fighter::dodge(float delta_time) {
	//回避
	GSvector3 velocity;
	velocity = transform().forward() * DodgeSpeed * delta_time;
	// 平行移動する（ワールド基準）
	transform_.translate(velocity, GStransform::Space::World);
	//回避モーションの終了を待つ
	if (state_timer_ >= mesh_.motion_end_time() * 0.8f) {
		move(delta_time);
	}
}

// ダメージ中
void Fighter::damage(float delta_time) {
	//ノックバックする
	transform_.translate(velocity_ * delta_time, GStransform::Space::World);
	velocity_ -= GSvector3{ velocity_.x, 0.0f, velocity_.z } *0.5f * delta_time;
	// ダメ―ジモーションの終了を待つ
	if (state_timer_ >= mesh_.motion_end_time()) {
		move(delta_time);
		is_damage_ = false;
	}
}

//死亡中
void Fighter::dead(float delta_time) {
	//if (ShareData::player_is_dead_ == true) return;
	// ダメ―ジモーションの終了を待つ
	if (state_timer_ >= mesh_.motion_end_time())
	{
		Common_Number::is_game_over_ = true;
	}

}

// フィールドとの衝突判定
void Fighter::collide_field() {
	// 壁との衝突判定（球体との判定）
	BoundingSphere sphere{ collider_.radius, transform_.position() };
	GSvector3 center; // 衝突後の球体の中心座標
	if (world_->field()->collide(collider(), &center)) {
		// y座標は変更しない
		center.y = transform_.position().y;
		// 補正後の座標に変更する
		transform_.position(center);
	}
	// 地面との衝突判定（線分との交差判定）
	GSvector3 position = transform_.position();
	Line line;
	line.start = position + collider_.center;
	line.end = position + GSvector3{ 0.0f, -FootOffset, 0.0f };
	GSvector3 intersect;  // 地面との交点
	if (world_->field()->collide(line, &intersect)) {
		// 交差した点からy座標のみ補正する
		position.y = intersect.y;
		// 座標を変更する
		transform_.position(position);
		// 重力を初期化する
		velocity_.y = 0.0f;
	}
}

// アクターとの衝突処理
void Fighter::collide_actor(Actor& other) {
	// ｙ座標を除く座標を求める
	GSvector3 position = transform_.position();
	position.y = 0.0f;
	GSvector3 target = other.transform().position();
	target.y = 0.0f;
	// 相手との距離
	float distance = GSvector3::distance(position, target);
	// 衝突判定球の半径同士を加えた長さを求める
	float length = collider_.radius + other.collider().radius;
	// 衝突判定球の重なっている長さを求める
	float overlap = length - distance;
	// 重なっている部分の半分の距離だけ離れる
	GSvector3 v = (position - target).getNormalized() * overlap * 0.5f;
	transform_.translate(v, GStransform::Space::World);
	// フィールドとの衝突判定
	collide_field();
}

// 攻撃判定の生成
void Fighter::generate_attack_collider(const std::string name, const std::string tag, float delay) {
	// 攻撃判定を出現させる場所の距離
	const float AttackColliderDistance{ 1.0f };
	// 攻撃判定の半径
	const float AttackColliderRadius{ 1.5f };
	// 攻撃判定を出す場所の高さ
	const float AttackColliderHeight{ 1.0f };
	// 攻撃判定が有効になるまでの遅延時間
	const float AttackCollideDelay{ delay };
	// 攻撃判定の寿命
	const float AttackCollideLifeSpan{ 0.5f };
	// 衝突判定を出現させる座標を求める（前方の位置）
	GSvector3 position = transform_.position() + transform_.forward() * AttackColliderDistance;
	// 高さの補正（足元からの高さ）
	position.y += AttackColliderHeight;
	// 衝突判定用の球を作成
	BoundingSphere collider{ AttackColliderRadius, position };
	// 衝突判定を出現させる
	world_->add_actor(new AttackCollider{ world_, collider,
		tag, name,tag, AttackCollideLifeSpan, AttackCollideDelay });
}

void  Fighter::special_attack() {
	// 弾を生成する場所の距離
	const float AttackColliderDistance{ 0.5f };
	// 生成する位置の高さの補正値
	const float AttackColliderHeight{ 1.5f };
	// 弾の移動スピード
	const float Speed{ 0.3f };
	// 生成位置の計算
	GSvector3 position = transform_.position() + transform_.forward() * AttackColliderDistance;
	// 生成位置の高さを補正する
	position.y += AttackColliderHeight;
	// 移動量の計算
	GSvector3 velocity = transform_.forward() * Speed;
}

// ターゲット方向の角度を求める（符号付き）
float Fighter::target_angle(GSvector3 target_pos) const {
	// ターゲット方向のベクトルを求める
	GSvector3 to_target = target_pos - transform_.position();
	// 前向き方向のベクトルを取得
	GSvector3 forward = transform_.forward();
	// ベクトルのy成分を無効にする
	forward.y = 0.0f;
	to_target.y = 0.0f;
	// 前向き方向のベクトルとターゲット方向のベクトルの角度差を求める
	return std::abs(GSvector3::signedAngle(forward, to_target));
}