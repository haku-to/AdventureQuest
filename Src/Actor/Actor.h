#ifndef ACTOR_H_
#define ACTOR_H_
#include<gslib.h>
#include<GStransform.h>
#include<string>
#include"Collision/BoundingSphere.h"
//���[���h���ۃC���^�[�t�F�[�X�̑O���錾
class IWorld;
//�A�N�^�[�N���X
class Actor {
public:
	//�R���X�g���N�^
	Actor() = default;
	//���z�f�X�g���N�^
	virtual ~Actor() = default;
	//�X�V
	virtual void update(float delta_time);
	//�x���X�V
	virtual void late_update(float delta_time);
	//�`��
	virtual void draw()const;
	//�������̕`��
	virtual void draw_transparent()const;
	//GUI�̕`��
	virtual void draw_gui()const;
	/// <summary>
	/// �Փ˃��A�N�V����
	/// </summary>
	/// <param name="other">�Փ˂������A�N�^</param>
	virtual void react(Actor& other);
	/// <summary>
	/// ���b�Z�[�W����
	/// </summary>
	/// <param name="message">���b�Z�[�W</param>
	/// <param name="param">�p�����[�^</param>
	virtual void handle_message(const std::string& message, void* param);
	/// <summary>
	/// �Փ˔���
	/// </summary>
	/// <param name="other">�Փ˂������A�N�^</param>
	void collide(Actor& other);
	//���S
	void die();
	/// <summary>
	/// �Փ˂��Ă��邩
	/// </summary>
	/// <param name="other">�Փ˂������A�N�^</param>
	/// <returns></returns>
	bool is_collide(const Actor& other)const;
	//���S���Ă��邩
	bool is_dead()const;
	//�_���[�W���󂯂Ă��邩
	bool is_damage()const;
	// ���O���擾
	const std::string& name()const;
	//�^�O���擾
	const std::string& tag()const;
	//�̗͂��擾
	const int& health()const;
	//�g�����X�t�H�[�����擾(const)
	const GStransform& transform()const;
	//�g�����X�t�H�[�����擾
	GStransform& transform();
	//�ړ��ʂ��擾
	GSvector3 velocity()const;
	//�Փ˔���f�[�^�̎擾
	BoundingSphere collider() const;
	//�R�s�[�֎~
	Actor(const Actor& other) = delete;
	Actor& operator = (const Actor& other) = delete;
protected:
	//���[���h
	IWorld* world_{ nullptr };
	//�^�O��
	std::string tag_;
	//���O
	std::string name_;
	//�g�����X�t�H�[��
	GStransform transform_;
	//�ړ���
	GSvector3 velocity_{ 0.0f,0.0f,0.0f };
	//�Փ˔��肪�L����
	bool enable_collider_{ true };
	//�Փ˔���
	BoundingSphere collider_;
	//�̗�
	int health_ = 0;
	//���S�t���O
	bool dead_{ false };
	//�_���[�W�t���O
	bool is_damage_{ false };
};
#endif
