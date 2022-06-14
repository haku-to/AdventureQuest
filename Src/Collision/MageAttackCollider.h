#ifndef MAGE_ATTACK_COLLIDER_H_
#define MAGE_ATTACK_COLLIDER_H_
#include "Actor/Actor.h"

class MageAttackCollider :public Actor {
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="world">ワールド</param>
	/// <param name="position">生成時のポジション</param>
	/// <param name="velocity">生成時の速度</param>
	MageAttackCollider(IWorld* world, const GSvector3& position, const GSvector3& velocity);
	//更新
	virtual void update(float delta_time)override;
	//描画
	virtual void draw()const override;
	//衝突リアクション
	virtual void react(Actor& other)override;
private:
	//寿命
	float lifespan_timer_;

};
#endif