#ifndef MAGE_ATTACK_COLLIDER_H_
#define MAGE_ATTACK_COLLIDER_H_
#include "Actor/Actor.h"

class MageAttackCollider :public Actor {
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="world">���[���h</param>
	/// <param name="position">�������̃|�W�V����</param>
	/// <param name="velocity">�������̑��x</param>
	MageAttackCollider(IWorld* world, const GSvector3& position, const GSvector3& velocity);
	//�X�V
	virtual void update(float delta_time)override;
	//�`��
	virtual void draw()const override;
	//�Փ˃��A�N�V����
	virtual void react(Actor& other)override;
private:
	//����
	float lifespan_timer_;

};
#endif