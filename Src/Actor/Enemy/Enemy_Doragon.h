#ifndef ENEMY_DORAGON_H_
#define ENEMY_DORAGON_H_
#include "Actor/Actor.h"
#include"Actor/AnimatedMesh.h"
//�h���S���N���X
class Enemy_Doragon :public Actor {
	enum class State {
		Idle,     //�A�C�h��
		Walk,	  //����
		Damage,	  //�_���[�W
		Turn,	  //�^�[��
		Attack,	  //�A�^�b�N
		Down,	  //�_�E��
		Victory,  //����
	};
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="world">���[���h</param>
	/// <param name="position">���������W</param>
	/// <param name="angle">����������</param>
	Enemy_Doragon(IWorld* world, const GSvector3& position, float angle);
	//�X�V
	virtual void update(float delta_time)override;
	//�`��
	virtual void draw()const override;
	/// <summary>
	/// �Փ˃��A�N�V����
	/// </summary>
	/// <param name="other">�Փ˂����A�N�^</param>
	virtual void react(Actor& other)override;
private:
	//��Ԃ̍X�V
	void  update_state(float delta_time);
	/// <summary>
	/// ��Ԃ̕ω�
	/// </summary>
	/// <param name="state">���̏��</param>
	/// <param name="motion">�ǂ̃A�j���[�V������</param>
	/// <param name="loop">���[�v�����邩</param>
	void change_state(State state, GSuint motion, bool loop = true);
	//�A�C�h��
	void idle(float delta_time);
	//���s
	void walk(float delta_time);
	//�����]��
	void turn(float delta_time);
	//�U��
	void attack(float delta_time);
	//�_���[�W
	void damage(float delta_time);
	//�_�E��
	void down(float delta_time);
	//�����]�������Ă��邩
	bool is_turn()const;
	//�U�������Ă��邩
	bool is_attack()const;
	//�����Ă��邩
	bool is_walk()const;
	//�O���������̃x�N�g���ƃ^�[�Q�b�g�����̃x�N�g���̊p�x�������߂�
	float target_signed_angle()const;
	//�^�[�Q�b�g�i�v���C���[�j�Ƃ̊p�x�����߂�
	float target_angle()const;
	//�^�[�Q�b�g�i�v���C���[�j�Ƃ̋��������߂�
	float target_distance()const;
	//�t�B�[���h�Ƃ̓����蔻��
	void collide_field();
	//���A�N�^�[�Ƃ̓����蔻��
	void collide_actor(Actor& other);
	//�U�����萶��
	void generate_attack_collider();
private:
	//�A�j���[�V�������b�V��
	AnimatedMesh mesh_;
	//���݂̃A�j���[�V����
	GSuint motion_;
	//���[�v�����邩
	bool motion_loop_;
	//���
	State state_;
	//��ԃ^�C�}�[
	float state_timer_;
	//�v���C���[
	Actor* player_;
	//�̗�
	int health_;
};
#endif