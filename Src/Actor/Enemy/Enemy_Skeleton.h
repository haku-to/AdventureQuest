#ifndef ENEMY_SKELETON_H_
#define ENEMY_SKELETON_H_
#include "Actor/Actor.h"
#include"Actor/AnimatedMesh.h"
//�X�P���g���N���X
class Enemy_Skeleton :public Actor {
	enum class State {
		Idle,     //�A�C�h��
		Walk,	  //����
		Turn,	  //�^�[��
		Damage,	  //�_���[�W
		Attack,	  //�A�^�b�N
		Down,	  //�_�E��
		Victory,  //����
	};
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="world">���[���h</param>
	/// <param name="position">�������̃|�W�V����</param>
	/// <param name="angle">�������̃A���O��</param>
	Enemy_Skeleton(IWorld* world, const GSvector3& position, float angle);
	//�X�V
	virtual void update(float delta_time)override;
	//�`��
	virtual void draw()const override;
	/// <summary>
	/// �Փ˃��A�N�V����
	/// </summary>
	/// <param name="other">�Փ˂����A�N�^�[</param>
	virtual void react(Actor& other)override;

private:
	//��ԍX�V
	void  update_state(float delta_time);
	/// <summary>
	/// ��ԕω�
	/// </summary>
	/// <param name="state">�ω���̏��</param>
	/// <param name="motion">�ω���̃��[�V����</param>
	/// <param name="loop">���[�V���������[�v�����邩</param>
	void change_state(State state, GSuint motion, bool loop = true);
	//�A�C�h����Ԏ��̍s��
	void idle(float delta_time);
	//������Ԏ��̍s��
	void walk(float delta_time);
	//�^�[����Ԏ��̍s��
	void turn(float delta_time);
	//�U����Ԏ��̍s��
	void attack(float delta_time);
	//�_���[�W��Ԏ��̍s��
	void damage(float delta_time);
	//�_�E����Ԏ��̍s��
	void down(float delta_time);
	//�^�[����Ԃ�
	bool is_turn()const;
	//�A�^�b�N��Ԃ�
	bool is_attack()const;
	//������Ԃ�
	bool is_walk()const;
	//�O���������̃x�N�g���ƃ^�[�Q�b�g�����̃x�N�g���̊p�x�������߂�
	float target_signed_angle()const;
	//�^�[�Q�b�g�i�v���C���[�j�Ƃ̊p�x�����߂�
	float target_angle()const;
	//�^�[�Q�b�g�i�v���C���[�j�Ƃ̋��������߂�
	float target_distance()const;
	//�t�B�[���h�Ƃ̓����蔻��
	void collide_field();
	/// <summary>
	/// ���A�N�^�Ƃ̓����蔻��
	/// </summary>
	/// <param name="other">���������A�N�^</param>
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