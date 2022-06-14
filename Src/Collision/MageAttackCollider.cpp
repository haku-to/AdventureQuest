#include "MageAttackCollider.h"
#include "World/IWorld.h"
#include "Rendering/Field.h"
#include "Rendering/Line.h"

//�R���X�g���N�^
MageAttackCollider::MageAttackCollider(IWorld* world, const GSvector3& position, const GSvector3& velocity) {
	//���[���h�ݒ�
	world_ = world;
	//�^�O��
	tag_ = "MageAttackTag";
	//�A�N�^�[��
	name_ = "MageAttack";
	//�ړ��ʂ̏�����
	velocity_ = velocity;
	//�Փ˔���
	collider_ = BoundingSphere{ 0.2 };
	//���W�̏�����
	transform_.position(position);
	//����
	lifespan_timer_ = 60.0f;
}

//�X�V
void MageAttackCollider::update(float delta_time) {
	//�������s�����玀�S
	if (lifespan_timer_ <= 0.0f) {
		die();
		return;
	}
	//�����X�V
	lifespan_timer_ -= delta_time;
	//�t�B�[���h�Ƃ̏Փ˔���
	Line line;
	line.start = transform_.position();
	line.end = transform_.position();
	GSvector3 intersect;
	if (world_->field()->collide(line, &intersect)) {
		//��_�̍��W�ɕ␳
		transform_.position(intersect);
		//�t�B�[���h�ɏՓ˂����玀�S
		die();
		return;
	}
	//�ړ�
	transform_.translate(velocity_ * delta_time, GStransform::Space::World);
}
//�`��
void MageAttackCollider::draw()const {
	collider().draw();
}

//�Փ˃��A�N�V����
void MageAttackCollider::react(Actor& other) {
	die();
}