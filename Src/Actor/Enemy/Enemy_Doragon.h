#ifndef ENEMY_DORAGON_H_
#define ENEMY_DORAGON_H_
#include "Actor/Actor.h"
#include"Actor/AnimatedMesh.h"
//ドラゴンクラス
class Enemy_Doragon :public Actor {
	enum class State {
		Idle,     //アイドル
		Walk,	  //歩き
		Damage,	  //ダメージ
		Turn,	  //ターン
		Attack,	  //アタック
		Down,	  //ダウン
		Victory,  //勝利
	};
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="world">ワールド</param>
	/// <param name="position">生成時座標</param>
	/// <param name="angle">生成時向き</param>
	Enemy_Doragon(IWorld* world, const GSvector3& position, float angle);
	//更新
	virtual void update(float delta_time)override;
	//描画
	virtual void draw()const override;
	/// <summary>
	/// 衝突リアクション
	/// </summary>
	/// <param name="other">衝突したアクタ</param>
	virtual void react(Actor& other)override;
private:
	//状態の更新
	void  update_state(float delta_time);
	/// <summary>
	/// 状態の変化
	/// </summary>
	/// <param name="state">次の状態</param>
	/// <param name="motion">どのアニメーションか</param>
	/// <param name="loop">ループさせるか</param>
	void change_state(State state, GSuint motion, bool loop = true);
	//アイドル
	void idle(float delta_time);
	//歩行
	void walk(float delta_time);
	//方向転換
	void turn(float delta_time);
	//攻撃
	void attack(float delta_time);
	//ダメージ
	void damage(float delta_time);
	//ダウン
	void down(float delta_time);
	//方向転換をしているか
	bool is_turn()const;
	//攻撃をしているか
	bool is_attack()const;
	//歩いているか
	bool is_walk()const;
	//前向き方向のベクトルとターゲット方向のベクトルの角度差を求める
	float target_signed_angle()const;
	//ターゲット（プレイヤー）との角度を求める
	float target_angle()const;
	//ターゲット（プレイヤー）との距離を求める
	float target_distance()const;
	//フィールドとの当たり判定
	void collide_field();
	//他アクターとの当たり判定
	void collide_actor(Actor& other);
	//攻撃判定生成
	void generate_attack_collider();
private:
	//アニメーションメッシュ
	AnimatedMesh mesh_;
	//現在のアニメーション
	GSuint motion_;
	//ループさせるか
	bool motion_loop_;
	//状態
	State state_;
	//状態タイマー
	float state_timer_;
	//プレイヤー
	Actor* player_;
	//体力
	int health_;
};
#endif