#include "InvisibleWall.h"
#include "World/IWorld.h"
#include"Assets.h"
#include"Music/SE.h"
InvisibleWall::InvisibleWall(IWorld* world, const GSvector3& position, std::string keyname) {
	// ���[���h��ݒ�
	world_ = world;
	// �^�O��
	tag_ = "InvisibleWallTag";
	// �A�N�^�[��
	name_ = "InvisibleWall";
	// �Փ˔���
	collider_ = BoundingSphere{ 25.0f };
	//�Փ˔��肪�L����
	enable_collider_ = true;
	// ���W�̏�����
	transform_.position(position);
	key_name_ = keyname;
}
//�X�V
void InvisibleWall::update(float delta_time) {
	//�ǉ����̃L�[�G�l�~�[����������
	Actor* keyenemy_ = world_->find_actor(key_name_);
	//���[���h����L�[�G�l�~�[���������玀��
	if (keyenemy_ == nullptr) {
		//�����Ȃ��ǉ�������炷
		SE::PlaySE(SE_InvisibleOff);
		die();
	}
}