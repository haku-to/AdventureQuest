#include "Fighter.h"
#include "World/IWorld.h"
#include "Rendering/Field.h"
#include "Rendering/Line.h"
#include "Collision/AttackCollider.h"
#include "Assets.h"
#include "Music/SE.h"
#include "Common_Number.h"

//HP�X�y���ʒu
const  GSvector2 UIposition_HP_Spel{ 0.0f,0.0f };
const  GSvector2 UIscale_HP_Spel{ 0.7f,0.7f };
//�̗�
const GSvector2 UIposition_HP_Bar{ 65.0f, 5.0f };
//�̗̓t���[��
const GSvector2 UIposition_HP_Frame{ 65.0f, 0.0f };
// ���[�V�����ԍ�
enum {
	Motion_Idle,       //�A�C�h�����[�V����
	Motion_Down,	   //�_�E�����[�V����
	Motion_Attack2,	   //�U�����[�V�����Q
	Motion_Attack3,	   //�U�����[�V�����R
	Motion_Attack1,	   //�U�����[�V�����P
	Motion_Victory,	   //�������[�V����
	Motion_Damage,	   //�_���[�W���[�V����
	Motion_Dodge,	   //������[�V����
	Motion_Walk,	   //�������[�V����
	Motion_Run,		   //���胂�[�V����
};

// �ړ����x
const float WalkSpeed{ 0.1f };
//�_�b�V�����x
const float RunSpeed{ 0.2f };
//��𑬓x
const float DodgeSpeed{ 0.1f };
// �����̍���
const float PlayerHeight{ 1.0f };
// �Փ˔���p�̔��a
const float PlayerRadius{ 0.5f };
// �����̃I�t�Z�b�g
const float FootOffset{ 0.1f };
// �d��
const float Gravity{ -0.016f };

// �R���X�g���N�^
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
	// ���[���h�̐ݒ�
	world_ = world;
	// �^�O���̐ݒ�
	tag_ = "PlayerTag";
	// ���O�̐ݒ�
	name_ = "Fighter";
	// �Փ˔��苅�̐ݒ�
	collider_ = BoundingSphere{ PlayerRadius, GSvector3{0.0f, PlayerHeight, 0.0f} };
	// ���W�̏�����
	transform_.position(position);
	// ���b�V���̕ϊ��s���������
	mesh_.transform(transform_.localToWorldMatrix());
	///�X�|�[��������
	transform_.rotate(0.0f, 50.0f, 0.0f);
}

// �X�V
void Fighter::update(float delta_time) {
	// ��Ԃ̍X�V
	update_state(delta_time);
	// �d�͒l���X�V
	velocity_.y += Gravity * delta_time;
	// �d�͂�������
	transform_.translate(0.0f, velocity_.y, 0.0f);
	// �t�B�[���h�Ƃ̏Փ˔���
	collide_field();
	// ���[�V������ύX
	mesh_.change_motion(motion_, motion_loop_);
	// ���b�V�����X�V
	mesh_.update(delta_time);
	// �s���ݒ�
	mesh_.transform(transform_.localToWorldMatrix());
	can_start_ = true;
	//�̗̓J���[�ύX
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

// �`��
void Fighter::draw() const {
	// ���b�V����`��
	mesh_.draw();
	// �Փ˔���̃f�o�b�O�\��
	//collider().draw();
}

void Fighter::draw_gui() const {
	gsDrawSprite2D(UI_HP_Spel, &UIposition_HP_Spel, NULL, NULL, NULL, &UIscale_HP_Spel, 0.0f);
	//�̗̓Q�[�W�T�C�Y
	GSvector2 UIscale_HP_{ health_, 0.5f };
	GScolor4 UIcolor_HP_Bar{ health_color_R,health_color_G,health_color_B,1.0f };
	//gsDrawSprite2D(UI_HP_Frame, &UIposition_HP_Frame, NULL, NULL, NULL, &UIscale_HPspel, 0.0f);
	gsDrawSprite2D(UI_Player_HP_Bar, &UIposition_HP_Bar, NULL, NULL, &UIcolor_HP_Bar, &UIscale_HP_, 0.0f);
}

// �Փ˃��A�N�V����
void Fighter::react(Actor& other) {
	// �_���[�W�A����A���S�A�h�䒆�̏ꍇ�͉������Ȃ�
	if (state_ == State::Damage || state_ == State::Dodge || state_ == State::Dead) return;
	// �G�̍U������ƏՓ˂������H
	if (other.tag() == "EnemyAttackTag" || other.tag() == "MageAttackTag") {
		SE::PlaySE(SE_Fighter_Damage);
		is_damage_ = true;
		// �^�[�Q�b�g�����̃x�N�g�������߂�
		GSvector3 to_target = other.transform().position() - transform().position();
		// �������͖����ɂ���
		to_target.y = 0.0f;
		// �^�[�Q�b�g�����Ƌt�����Ƀm�b�N�o�b�N����ړ��ʂ����߂�
		velocity_ = -to_target.getNormalized() * 0.25f;
		//�̗͌���
		health_ -= 1;// �_���[�W��ԂɑJ�ڂ���
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
	// �G�ƏՓ˂������H
	if (other.tag() == "EnemyBossTag" || other.tag() == "EnemyTag" || other.tag() == "InvisibleWallTag") {
		// �A�N�^�[���m�̏Փˏ���
		collide_actor(other);
	}
}
// ��Ԃ̍X�V
void Fighter::update_state(float delta_time) {
	// ��ԑJ��
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

// ��Ԃ̕ύX
void Fighter::change_state(State state, GSuint motion, bool loop) {
	// ���[�V�����ԍ��̍X�V
	motion_ = motion;
	// ���[�V�����̃��[�v�w��
	motion_loop_ = loop;
	// ��Ԃ̍X�V
	state_ = state;
	// ��ԃ^�C�}�̏�����
	state_timer_ = 0.0f;
}

// �ړ�����
void Fighter::move(float delta_time) {
	if (can_start_) {
		//�_���[�W���󂯂ĂȂ��Ƃ������U���\
		if (is_damage_ == false)
		{
			// X�{�^���ōU���P
			if (gsGetJoyTrigger(0, GJOY_BUTTON_3))
			{
				// �U����ԂɑJ�ڂ���
				SE::PlaySE(SE_Fighter_Attack1);
				change_state(State::Attack1, Motion_Attack1);
				attack_num_ = 1;
				can_attack_ = true;
				return;
			}
		}
		//A�{�^���ŉ��
		if (gsGetJoyTrigger(0, GJOY_BUTTON_1)) {
			// �����ԂɑJ�ڂ���
			change_state(State::Dodge, Motion_Dodge);
			return;
		}
		// �J�����̑O�����x�N�g�����擾
		GSvector3 forward = world_->camera()->transform().forward();
		forward.y = 0.0f;
		// �J�����̉E�����x�N�g�����擾
		GSvector3 right = world_->camera()->transform().right();
		right.y = 0.0f;
		// ���W���擾
		GSvector3 position = transform_.position();
		//// �L�[�̓��͒l����ړ��ʂ��v�Z
		GSvector3 velocity{ 0.0f, 0.0f, 0.0f };
		//L�X�e�B�b�N�̓���
		GSvector2 lAxis;
		float speed;
		gsXBoxPadGetLeftAxis(0, &lAxis);
		// �ړ����Ȃ���΃A�C�h�����
		GSint motion{ Motion_Idle };
		//RB�{�^����������Ă��邩
		if (gsXBoxPadButtonState(0, GS_XBOX_PAD_RIGHT_SHOULDER)) {
			//����p�����[�^
			speed = RunSpeed;
			is_running_ = true;
		}
		else {
			//�����p�����[�^
			speed = WalkSpeed;
			is_running_ = false;
		}

		// �ړ��ʂ��v�Z����
		velocity = forward.normalized() * lAxis.y * speed * delta_time +
			right * lAxis.x * speed * delta_time;
		// �ړ����Ă��邩�H
		if (velocity.lengthSq() != 0.0f) {
			// �����̕��
			GSquaternion rotation =
				GSquaternion::rotateTowards(transform_.rotation(), GSquaternion::lookRotation(velocity), 30.0f * delta_time);
			transform_.rotation(rotation);
			// �ړ����̃��[�V�����ɂ���
			if (is_running_) motion = Motion_Run;
			else motion = Motion_Walk;
		}
		// ���[�V�����̕ύX
		change_state(State::Move, motion);
		// �ړ��ʂ�xz�������X�V
		velocity_.x = velocity.x;
		velocity_.z = velocity.z;
		// ���s�ړ�����i���[���h��j
		transform_.translate(velocity_, GStransform::Space::World);
	}
}

// �U����
void Fighter::attack(float delta_time) {
	// �U�����[�V�����̏I����҂�
	if (state_timer_ >= mesh_.motion_end_time() * 0.7f) {
		move(delta_time);
	}
	if (state_timer_ > mesh_.motion_end_time() * 0.4f && is_damage_ == false) {
		if (attack_num_ == 1 && gsGetJoyTrigger(0, GJOY_BUTTON_3)) {
			// �U����ԂɑJ�ڂ���
			change_state(State::Attack1, Motion_Attack2);
			attack_num_ = 2;
			SE::PlaySE(SE_Fighter_Attack2);
			can_attack_ = true;
			return;
		}
		else if (attack_num_ == 2 && gsGetJoyTrigger(0, GJOY_BUTTON_3)) {
			// �U����ԂɑJ�ڂ���
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

	//�U���������O�i
	if (state_timer_ <= mesh_.motion_end_time() * 0.3f) {
		GSvector3 forward = transform().forward();
		forward.y = 0.0f;
		GSvector3 velocity = forward.normalize() * 0.03;
		// ���s�ړ�����i���[���h��j
		transform_.translate(velocity, GStransform::Space::World);
	}
	//����ōU���𒆎~
	if (gsGetJoyTrigger(0, GJOY_BUTTON_1) && state_timer_ >= mesh_.motion_end_time() * 0.4f) {
		change_state(State::Dodge, Motion_Dodge);
		return;
	}
}

// �U����
void Fighter::attack2(float delta_time) {
	// �U�����[�V�����̏I����҂�
	if (state_timer_ >= mesh_.motion_end_time()) {
		move(delta_time);
	}
	//�U���������O�i
	if (state_timer_ <= mesh_.motion_end_time() * 0.3f) {
		GSvector3 forward = transform().forward();
		forward.y = 0.0f;
		GSvector3 velocity = forward.normalize() * 0.03;
		// ���s�ړ�����i���[���h��j
		transform_.translate(velocity, GStransform::Space::World);
	}
}
//���
void Fighter::dodge(float delta_time) {
	//���
	GSvector3 velocity;
	velocity = transform().forward() * DodgeSpeed * delta_time;
	// ���s�ړ�����i���[���h��j
	transform_.translate(velocity, GStransform::Space::World);
	//������[�V�����̏I����҂�
	if (state_timer_ >= mesh_.motion_end_time() * 0.8f) {
		move(delta_time);
	}
}

// �_���[�W��
void Fighter::damage(float delta_time) {
	//�m�b�N�o�b�N����
	transform_.translate(velocity_ * delta_time, GStransform::Space::World);
	velocity_ -= GSvector3{ velocity_.x, 0.0f, velocity_.z } *0.5f * delta_time;
	// �_���\�W���[�V�����̏I����҂�
	if (state_timer_ >= mesh_.motion_end_time()) {
		move(delta_time);
		is_damage_ = false;
	}
}

//���S��
void Fighter::dead(float delta_time) {
	//if (ShareData::player_is_dead_ == true) return;
	// �_���\�W���[�V�����̏I����҂�
	if (state_timer_ >= mesh_.motion_end_time())
	{
		Common_Number::is_game_over_ = true;
	}

}

// �t�B�[���h�Ƃ̏Փ˔���
void Fighter::collide_field() {
	// �ǂƂ̏Փ˔���i���̂Ƃ̔���j
	BoundingSphere sphere{ collider_.radius, transform_.position() };
	GSvector3 center; // �Փˌ�̋��̂̒��S���W
	if (world_->field()->collide(collider(), &center)) {
		// y���W�͕ύX���Ȃ�
		center.y = transform_.position().y;
		// �␳��̍��W�ɕύX����
		transform_.position(center);
	}
	// �n�ʂƂ̏Փ˔���i�����Ƃ̌�������j
	GSvector3 position = transform_.position();
	Line line;
	line.start = position + collider_.center;
	line.end = position + GSvector3{ 0.0f, -FootOffset, 0.0f };
	GSvector3 intersect;  // �n�ʂƂ̌�_
	if (world_->field()->collide(line, &intersect)) {
		// ���������_����y���W�̂ݕ␳����
		position.y = intersect.y;
		// ���W��ύX����
		transform_.position(position);
		// �d�͂�����������
		velocity_.y = 0.0f;
	}
}

// �A�N�^�[�Ƃ̏Փˏ���
void Fighter::collide_actor(Actor& other) {
	// �����W���������W�����߂�
	GSvector3 position = transform_.position();
	position.y = 0.0f;
	GSvector3 target = other.transform().position();
	target.y = 0.0f;
	// ����Ƃ̋���
	float distance = GSvector3::distance(position, target);
	// �Փ˔��苅�̔��a���m�����������������߂�
	float length = collider_.radius + other.collider().radius;
	// �Փ˔��苅�̏d�Ȃ��Ă��钷�������߂�
	float overlap = length - distance;
	// �d�Ȃ��Ă��镔���̔����̋������������
	GSvector3 v = (position - target).getNormalized() * overlap * 0.5f;
	transform_.translate(v, GStransform::Space::World);
	// �t�B�[���h�Ƃ̏Փ˔���
	collide_field();
}

// �U������̐���
void Fighter::generate_attack_collider(const std::string name, const std::string tag, float delay) {
	// �U��������o��������ꏊ�̋���
	const float AttackColliderDistance{ 1.0f };
	// �U������̔��a
	const float AttackColliderRadius{ 1.5f };
	// �U��������o���ꏊ�̍���
	const float AttackColliderHeight{ 1.0f };
	// �U�����肪�L���ɂȂ�܂ł̒x������
	const float AttackCollideDelay{ delay };
	// �U������̎���
	const float AttackCollideLifeSpan{ 0.5f };
	// �Փ˔�����o����������W�����߂�i�O���̈ʒu�j
	GSvector3 position = transform_.position() + transform_.forward() * AttackColliderDistance;
	// �����̕␳�i��������̍����j
	position.y += AttackColliderHeight;
	// �Փ˔���p�̋����쐬
	BoundingSphere collider{ AttackColliderRadius, position };
	// �Փ˔�����o��������
	world_->add_actor(new AttackCollider{ world_, collider,
		tag, name,tag, AttackCollideLifeSpan, AttackCollideDelay });
}

void  Fighter::special_attack() {
	// �e�𐶐�����ꏊ�̋���
	const float AttackColliderDistance{ 0.5f };
	// ��������ʒu�̍����̕␳�l
	const float AttackColliderHeight{ 1.5f };
	// �e�̈ړ��X�s�[�h
	const float Speed{ 0.3f };
	// �����ʒu�̌v�Z
	GSvector3 position = transform_.position() + transform_.forward() * AttackColliderDistance;
	// �����ʒu�̍�����␳����
	position.y += AttackColliderHeight;
	// �ړ��ʂ̌v�Z
	GSvector3 velocity = transform_.forward() * Speed;
}

// �^�[�Q�b�g�����̊p�x�����߂�i�����t���j
float Fighter::target_angle(GSvector3 target_pos) const {
	// �^�[�Q�b�g�����̃x�N�g�������߂�
	GSvector3 to_target = target_pos - transform_.position();
	// �O���������̃x�N�g�����擾
	GSvector3 forward = transform_.forward();
	// �x�N�g����y�����𖳌��ɂ���
	forward.y = 0.0f;
	to_target.y = 0.0f;
	// �O���������̃x�N�g���ƃ^�[�Q�b�g�����̃x�N�g���̊p�x�������߂�
	return std::abs(GSvector3::signedAngle(forward, to_target));
}