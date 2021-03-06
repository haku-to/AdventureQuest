#include "Enemy_Mage.h"
#include "World/IWorld.h"
#include "Rendering/Field.h"
#include "Rendering/Line.h"
#include "Collision/MageAttackCollider.h"
#include "Assets.h"
#include "Common_Number.h"
#include "Music/SE.h"
enum
{
	MotionAttack = 0,    //アタックモーション
	MotionDown = 2,		 //ダウンモーション
	MotionDamage = 4,	 //ダメージモーション
	MotionIdle = 6,		 //アイドルモーション
	MotionWalk = 8,		 //歩きモーション
	MotionVictory = 12,  //勝利モーション
};
//振り向き判定の距離
const float TurnDistance{ 3.0f };
//攻撃判定の距離
const float AttackDistance{ 12.0f };
//移動判定の距離
const float WalkDistance{ 20.0f };
//移動スピード
const float WalkSpeed{ 0.025f };
//振り向く角度
const float TurnAngle{ 2.5f };
//エネミーの高さ
const float EnemyHeight{ 1.0f };
//エネミーの衝突判定の大きさ
const float EnemyRadius{ 0.6f };
//足元のオフセット
const float FootOffset{ 0.1f };
//重力
const float Gravity{ -0.016f };

//コンストラクタ
Enemy_Mage::Enemy_Mage(IWorld* world, const GSvector3& position, float angle) :
	mesh_{ Mesh_Mage,Mesh_Mage,Mesh_Mage,MotionIdle },
	motion_{ MotionIdle },
	motion_loop_{ true },
	state_{ State::Idle },
	state_timer_{ 0.0f },
	player_{ nullptr },
	health_{ 4 }{
	//ワールドの設定
	world_ = world;
	//タグ名の設定
	tag_ = "EnemyTag";
	//名前の設定
	name_ = "Mage";
	//衝突判定球の設定
	collider_ = BoundingSphere{ EnemyRadius,GSvector3{0.0f,EnemyHeight,0.0f} };
	//座標の初期化
	transform_.position(position);
	//ワールド座標行列の初期化
	mesh_.transform(transform_.localToWorldMatrix());
	//スポーン時方向
	transform_.rotate(0.0f, angle, 0.0f);
}

//更新
void Enemy_Mage::update(float delta_time) {
	//プレイヤー検索
	player_ = world_->find_actor(Common_Number::CharaName[Common_Number::CharacterNum]);
	//状態の更新
	update_state(delta_time);
	//重力の更新
	velocity_.y += Gravity * delta_time;
	//重力を加える
	transform_.translate(0.0f, velocity_.y, 0.0f);
	//フィールドとの当たり判定
	collide_field();
	//モーションの変更
	mesh_.change_motion(motion_, motion_loop_);
	//メッシュの更新
	mesh_.update(delta_time);
	//行列を設定
	mesh_.transform(transform_.localToWorldMatrix());
	//ゲームオーバーなら勝利モーション
	if (Common_Number::is_game_over_)
		change_state(State::Victory, MotionVictory, true);
	//ゲームクリアなら死亡
	if (Common_Number::is_game_clear_)
		change_state(State::Down, MotionDown, false);
}

//描画
void Enemy_Mage::draw()const {
	//メッシュの描画
	mesh_.draw();
	//collider().draw();
}

//衝突リアクション
void Enemy_Mage::react(Actor& other) {
	//ダメージ中とダウン中は何もしない
	if (state_ == State::Damage || state_ == State::Down)return;
	if (other.tag() == "PlayerAttackTag" || other.tag() == "PlayerBulletTag" || other.tag() == "FighterAttackTag")
	{
		SE::PlaySE(SE_Enemy_Mage_Damage);
		change_state(State::Damage, MotionDamage, false);
		//レンジャーの出すバレット攻撃タグだったら
		if (other.tag() == "PlayerBulletTag")
		{
			SE::PlaySE(SE_ArrowHit);
			//体力を０．５減らす
			health_ -= 0.5f;
		}
		//ファイターの攻撃タグだったら
		else if (other.tag() == "FighterAttackTag")
		{
			//パンチヒット音を出す
			SE::PlaySE(SE_PunchHit);
			//体力を１．５減らす
			health_ -= 1.5f;
		}
		else
		{
			//ソードヒット音を出す
			SE::PlaySE(SE_SwordHit);
			//ナイトの攻撃タグなら１減らす
			health_--;
		}
		if (health_ <= 0)
		{
			//魔法使い死亡音を出す
			SE::PlaySE(SE_Enemy_Mage_Down);
			//ダウンモーションに移る
			change_state(State::Down, MotionDown, false);
		}
		else
			//ノックバックの数値
			velocity_ = other.velocity().getNormalized() * 0.5f;

	}
	//敵と衝突したか
	if (other.tag() == "PlayerTag" || other.tag() == "EnemyTag") {
		//アクター同士が重ならないようにする
		collide_actor(other);
	}
}

//状態更新
void Enemy_Mage::update_state(float delta_time) {
	//各状態に分岐する
	switch (state_) {
	case State::Idle:idle(delta_time); break;
	case State::Attack:attack(delta_time); break;
	case State::Walk:walk(delta_time); break;
	case State::Damage:damage(delta_time); break;
	case State::Turn:turn(delta_time); break;
	case State::Down:down(delta_time); break;
	}
	//状態タイマーの更新
	state_timer_ += delta_time;
}

//ダメージ中
void Enemy_Mage::damage(float delta_time) {
	if (state_timer_ < mesh_.motion_end_time()) {
		//ノックバックする
		transform_.translate(velocity_ * delta_time, GStransform::Space::World);
		//減速させる
		velocity_ -= GSvector3{ velocity_.x,0.0f,velocity_.z }*0.5f * delta_time;
		return;
	}
	//アイドルに遷移
	idle(delta_time);
}

//死亡
void Enemy_Mage::down(float delta_time) {
	if (state_timer_ >= mesh_.motion_end_time()) {
		die();
	}
}

//前向き方向のベクトルとターゲット方向のベクトルの角度差を求める
float Enemy_Mage::target_signed_angle()const {
	//プレイヤーがいなければ何もしない
	if (player_ == nullptr)return 0.0f;
	//ターゲット方向のベクトルを求める
	GSvector3 to_target = player_->transform().position() - transform_.position();
	//前向き方向のベクトルを取得
	GSvector3 forward = transform_.forward();
	//ベクトルのy成分を０にする
	forward.y = 0.0f;
	to_target.y = 0.0f;
	//前向き方向のベクトルとターゲット方向のベクトルの角度差を求める
	return GSvector3::signedAngle(forward, to_target);
}

//前向き方向のベクトルとターゲット方向のベクトルの角度差を求める(符号なし)
float Enemy_Mage::target_angle() const {
	return std::abs(target_signed_angle());
}

//ターゲットとの距離を求める
float Enemy_Mage::target_distance()const {
	//ターゲットとの距離を計算する
	if (player_ == nullptr)return FLT_MAX;
	return (player_->transform().position() - transform_.position()).magnitude();
}

//フィールドとの衝突判定
void Enemy_Mage::collide_field() {
	//壁との衝突判定(球体との判定）
	GSvector3 center;//衝突後の球体の中心座標
	if (world_->field()->collide(collider(), &center)) {
		//y座標は変更なし
		center.y = transform_.position().y;
		//補正後の座標に変更する
		transform_.position(center);
	}
	//地面との衝突判定（線分との交差判定）
	GSvector3 position = transform_.position();
	Line line;
	line.start = position + collider_.center;
	line.end = position + GSvector3{ 0.0f, -FootOffset,0.0f };
	GSvector3 intersect;
	if (world_->field()->collide(line, &intersect)) {
		//交差の位置からy座標のみ補正する
		position.y = intersect.y;
		//座標を変更する
		transform_.position(position);
		//重力を初期化する
		velocity_.y = 0.0f;
	}
}

//アクターとの衝突処理
void Enemy_Mage::collide_actor(Actor& other) {
	//y座標を除く座標を求める
	GSvector3 position = transform_.position();
	position.y = 0.0f;
	GSvector3 target = other.transform().position();
	target.y = 0.0f;
	//相手との距離
	float distance = GSvector3::distance(position, target);
	//衝突判定球の半径同士を加えた長さを求める
	float length = collider_.radius + other.collider().radius;
	//衝突判定球の重なっている長さを求める
	float overlap = length - distance;
	//重なっている部分の半分の距離だけ離れる移動量を求める
	GSvector3 v = (position - target).getNormalized() * overlap * 0.5f;
	transform_.translate(v, GStransform::Space::World);
	//フィールドとの衝突判定
	collide_field();
}

//状態の変更
void Enemy_Mage::change_state(State state, GSuint motion, bool loop) {
	//モーション番号の更新
	motion_ = motion;
	//モーションループ指定
	motion_loop_ = loop;
	//状態の更新
	state_ = state;
	//状態タイマーの初期化
	state_timer_ = 0.0f;
}

//アイドル状態
void Enemy_Mage::idle(float delta_time) {
	// 攻撃するか？
	if (is_attack())
	{
		// 攻撃状態に遷移
		change_state(State::Attack, MotionAttack);
		return;
	}
	// 歩くか？
	if (is_walk())
	{
		// 歩き状態に遷移
		change_state(State::Walk, MotionWalk);
		return;
	}
	// 何もなければ、アイドル中のまま
	change_state(State::Idle, MotionIdle);
}


//移動中
void Enemy_Mage::walk(float delta_time) {
	// ターゲット方向の角度を求める
	float angle = target_signed_angle();
	// 振り向き角度よりも角度の差があるか？
	if (std::abs(angle) > (TurnAngle * delta_time)) {
		// 角度差が大きい場合は、少しずつ向きを変えるように角度を制限する
		angle = CLAMP(angle, -TurnAngle, TurnAngle) * delta_time;
	}
	// 向きを変える
	transform_.rotate(0.0f, angle, 0.0f);
	// 前進する（ローカル座標基準）
	transform_.translate(0.0f, 0.0f, WalkSpeed * delta_time);
	// 攻撃するか？
	if (is_attack())
	{
		// 攻撃状態に遷移する
		change_state(State::Attack, MotionAttack);
	}
}

//振り向き中
void Enemy_Mage::turn(float delta_time) {
	if (state_timer_ >= mesh_.motion_end_time())
	{
		// 振り向きモーションが終了したらアイドル中に遷移
		idle(delta_time);
	}
	else
	{
		// 振り向きモーションをしながらターゲット方向を向く
		float angle = (target_signed_angle() >= 0.0f) ? TurnAngle : -TurnAngle;
		transform_.rotate(0.0f, angle * delta_time, 0.0f);
	}
}


void Enemy_Mage::attack(float delta_time) {
	if (state_timer_ >= mesh_.motion_end_time() * 0.2f && state_timer_ <= mesh_.motion_end_time() * 0.21f)
	{
		//攻撃判定生成
		generate_attack_collider();
	}
	if (state_timer_ >= mesh_.motion_end_time())
	{
		// 攻撃モーションが終了したらアイドル中に遷移
		idle(delta_time);
	}
}

//ターンしているか
bool Enemy_Mage::is_turn()const {
	return(target_distance() <= TurnDistance);
}

//攻撃しているか
bool Enemy_Mage::is_attack()const {
	return (target_distance() <= AttackDistance) && (target_angle() <= 5.0f);
}

//歩いているか
bool Enemy_Mage::is_walk()const {
	return(target_distance() <= WalkDistance) && (target_angle() <= 360.0f);
}

//攻撃判定生成
void Enemy_Mage::generate_attack_collider() {
	// 弾を生成する場所の距離
	const float GenerateDistance{ 1.0f };
	// 生成する位置の高さの補正値
	const float GenerateHeight{ 1.0f };
	// 弾の移動スピード
	const float Speed{ 0.3f };
	// 生成位置の計算
	GSvector3 position = transform_.position() + transform_.forward() * GenerateDistance;
	// 生成位置の高さを補正する
	position.y += GenerateHeight;
	// 移動量の計算
	GSvector3 velocity = transform_.forward() * Speed;
	// 弾の生成
	world_->add_actor(new MageAttackCollider{ world_, position, velocity });
}