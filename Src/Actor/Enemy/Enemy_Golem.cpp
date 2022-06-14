#include "Enemy_Golem.h"
#include "World/IWorld.h"
#include "Rendering/Field.h"
#include "Rendering/Line.h"
#include "Collision/AttackCollider.h"
#include "Assets.h"
#include "Common_Number.h"
#include "Music/SE.h"
enum
{
	MotionAttack = 0,     //�U�����[�V����
	MotionDown = 2,		  //�_�E�����[�V����
	MotionDamage = 4,	  //�_���[�W���[�V����
	MotionIdle = 6,		  //�A�C�h�����[�V����
	MotionWalk = 8,		  //�������[�V����
	MotionVictory = 12	  //�������[�V����
};
//�G�l�~�[��HP�o�[���W
const GSvector2 UIposition_Enemy_HP_Bar{ 400.0f,100.0f };
//�G�l�~�[�̖��O���W
const GSvector2 UIposition_Enemy_Name{ 640.0f, 70.0f };
//�G�l�~�[�̖��O���S
const GSvector2 UIcenter_Enemy_Name{ 130.0f,32.0f };
//�U���������̋���
const float TurnDistance{ 3.0f };
//�U������̋���
const float AttackDistance{ 3.0f };
//�ړ�����̋���
const float WalkDistance{ 20.0f };
//�ړ��X�s�[�h
const float WalkSpeed{ 0.05f };
//�U������p�x
const float TurnAngle{ 2.5f };
//�G�l�~�[�̍���
const float EnemyHeight{ 2.0f };
//�Փ˔���̔��a
const float EnemyRadius{ 1.2f };
//�����̃I�t�Z�b�g
const float FootOffset{ 0.1f };
//�d�͒l
const float Gravity{ -0.016f };

//�R���X�g���N�^
Enemy_Golem::Enemy_Golem(IWorld* world, const GSvector3& position, float angle) :
	mesh_{ Mesh_Golem,Mesh_Golem,Mesh_Golem,MotionIdle },
	motion_{ MotionIdle },
	motion_loop_{ true },
	state_{ State::Idle },
	state_timer_{ 0.0f },
	player_{ nullptr },
	health_{ 15.0f }{
	//���[���h�̐ݒ�
	world_ = world;
	//�^�O���̐ݒ�
	tag_ = "EnemyTag";
	//���O�̐ݒ�
	name_ = "Golem";
	//�Փ˔��苅�̐ݒ�
	collider_ = BoundingSphere{ EnemyRadius,GSvector3{0.0f,EnemyHeight,0.0f} };
	//���W�̏�����
	transform_.position(position);
	//���[���h���W�s��̏�����
	mesh_.transform(transform_.localToWorldMatrix());
	//�X�|�[��������
	transform_.rotate(0.0f, angle, 0.0f);
}

//�X�V
void Enemy_Golem::update(float delta_time) {
	//�v���C���[������
	player_ = world_->find_actor(Common_Number::CharaName[Common_Number::CharacterNum]);
	//��Ԃ̍X�V
	update_state(delta_time);
	//�d�͂̍X�V
	velocity_.y += Gravity * delta_time;
	//�d�͂�������
	transform_.translate(0.0f, velocity_.y, 0.0f);
	//�t�B�[���h�Ƃ̓����蔻��
	collide_field();
	//���[�V�����̕ύX
	mesh_.change_motion(motion_, motion_loop_);
	//���b�V���̍X�V
	mesh_.update(delta_time);
	//�s���ݒ�
	mesh_.transform(transform_.localToWorldMatrix());
	//�Q�[���I�[�o�[�Ȃ珟�����[�V����
	if (Common_Number::is_game_over_)
		change_state(State::Victory, MotionVictory, true);
}

//�`��
void Enemy_Golem::draw()const {
	//���b�V���̕`��
	mesh_.draw();
	//��苗���ɋ߂Â�����
	if (is_walk())
	{
		//�̗͂Ɩ��O��`��
		const GSvector2 UIscale_Enemy_HP_Bar{ health_,1.0f };
		gsDrawSprite2D(UI_Enemy_HP_Bar, &UIposition_Enemy_HP_Bar, NULL, NULL, NULL, &UIscale_Enemy_HP_Bar, 0.0f);
		gsDrawSprite2D(UI_Enemy_Name, &UIposition_Enemy_Name, NULL, &UIcenter_Enemy_Name, NULL, NULL, 0.0f);
	}
}

//�Փ˃��A�N�V����
void Enemy_Golem::react(Actor& other)
{
	//�_���[�W���ƃ_�E�����͉������Ȃ�
	if (state_ == State::Damage || state_ == State::Down)return;
	if (other.tag() == "PlayerAttackTag" || other.tag() == "PlayerBulletTag" || other.tag() == "FighterAttackTag")
	{
		change_state(State::Damage, MotionDamage, false);
		SE::PlaySE(SE_Enemy_Golem_Damage);
		//�����W���[�̏o���o���b�g�U���^�O��������
		if (other.tag() == "PlayerBulletTag")
		{
			SE::PlaySE(SE_ArrowHit_Golem);
			//�̗͂��O�D�T���炷
			health_ -= 0.5f;
		}
		//�t�@�C�^�[�̍U���^�O��������
		else if (other.tag() == "FighterAttackTag")
		{
			//�p���`�q�b�g�����o��
			SE::PlaySE(SE_PunchHit_Golem);
			//�̗͂��P�D�T���炷
			health_ -= 1.5f;
		}
		else
		{
			//�\�[�h�q�b�g�����o��
			SE::PlaySE(SE_SwordHit_Golem);
			//�i�C�g�̍U���^�O�Ȃ�P���炷
			health_--;
		}
		//�̗͂��Ȃ��Ȃ�����
		if (health_ <= 0)
		{
			//�S�[�����̎��S�����o��
			SE::PlaySE(SE_Enemy_Golem_Down);
			//�_�E�����[�V�����Ɉڂ�
			change_state(State::Down, MotionDown, false);
		}
		else
			//����ȊO�̓m�b�N�o�b�N�̐��l�ݒ�
			velocity_ = other.velocity().getNormalized() * 0.5f;
	}
	//�G�ƏՓ˂�����
	if (other.tag() == "PlayerTag" || other.tag() == "EnemyTag") {
		//�A�N�^�[���m���d�Ȃ�Ȃ��悤�ɂ���
		collide_actor(other);
	}
}

//��ԍX�V
void Enemy_Golem::update_state(float delta_time) {
	//�e��Ԃɕ��򂷂�
	switch (state_) {
	case State::Idle:idle(delta_time); break;
	case State::Attack:attack(delta_time); break;
	case State::Walk:walk(delta_time); break;
	case State::Damage:damage(delta_time); break;
	case State::Turn:turn(delta_time); break;
	case State::Down:down(delta_time); break;
	}
	//��ԃ^�C�}�[�̍X�V
	state_timer_ += delta_time;
}

//�_���[�W��
void Enemy_Golem::damage(float delta_time) {
	if (state_timer_ < mesh_.motion_end_time()) {
		//�m�b�N�o�b�N����
		transform_.translate(velocity_ * delta_time, GStransform::Space::World);
		//����������
		velocity_ -= GSvector3{ velocity_.x,0.0f,velocity_.z }*0.5f * delta_time;
		return;
	}
	//�A�C�h���ɑJ��
	idle(delta_time);
}

//���S
void Enemy_Golem::down(float delta_time) {
	//���[�V�������I��������
	if (state_timer_ >= mesh_.motion_end_time()) {
		//�Q�[���N���A��true�ɂ���
		Common_Number::is_game_clear_ = true;
		//�Q�[���N���A�����o��
		SE::PlaySE(SE_GameClear);
		//BGM���~����
		gsDeleteBGM(BGM_Play);
		//���S
		die();
	}
}

//�O���������̃x�N�g���ƃ^�[�Q�b�g�����̃x�N�g���̊p�x�������߂�
float Enemy_Golem::target_signed_angle()const {
	//�v���C���[�����Ȃ���Ή������Ȃ�
	if (player_ == nullptr)return 0.0f;
	//�^�[�Q�b�g�����̃x�N�g�������߂�
	GSvector3 to_target = player_->transform().position() - transform_.position();
	//�O���������̃x�N�g�����擾
	GSvector3 forward = transform_.forward();
	//�x�N�g����y�������O�ɂ���
	forward.y = 0.0f;
	to_target.y = 0.0f;
	//�O���������̃x�N�g���ƃ^�[�Q�b�g�����̃x�N�g���̊p�x�������߂�
	return GSvector3::signedAngle(forward, to_target);
}

//�O���������̃x�N�g���ƃ^�[�Q�b�g�����̃x�N�g���̊p�x�������߂�(�����Ȃ�)
float Enemy_Golem::target_angle() const {
	return std::abs(target_signed_angle());
}

//�^�[�Q�b�g�Ƃ̋��������߂�
float Enemy_Golem::target_distance()const {
	//�^�[�Q�b�g�Ƃ̋������v�Z����
	if (player_ == nullptr)return FLT_MAX;
	return (player_->transform().position() - transform_.position()).magnitude();
}

//�t�B�[���h�Ƃ̏Փ˔���
void Enemy_Golem::collide_field() {
	//�ǂƂ̏Փ˔���(���̂Ƃ̔���j
	GSvector3 center;//�Փˌ�̋��̂̒��S���W
	if (world_->field()->collide(collider(), &center)) {
		//y���W�͕ύX�Ȃ�
		center.y = transform_.position().y;
		//�␳��̍��W�ɕύX����
		transform_.position(center);
	}
	//�n�ʂƂ̏Փ˔���i�����Ƃ̌�������j
	GSvector3 position = transform_.position();
	Line line;
	line.start = position + collider_.center;
	line.end = position + GSvector3{ 0.0f, -FootOffset,0.0f };
	GSvector3 intersect;
	if (world_->field()->collide(line, &intersect)) {
		//�����̈ʒu����y���W�̂ݕ␳����
		position.y = intersect.y;
		//���W��ύX����
		transform_.position(position);
		//�d�͂�����������
		velocity_.y = 0.0f;
	}
}

//�A�N�^�[�Ƃ̏Փˏ���
void Enemy_Golem::collide_actor(Actor& other) {
	//y���W���������W�����߂�
	GSvector3 position = transform_.position();
	position.y = 0.0f;
	GSvector3 target = other.transform().position();
	target.y = 0.0f;
	//����Ƃ̋���
	float distance = GSvector3::distance(position, target);
	//�Փ˔��苅�̔��a���m�����������������߂�
	float length = collider_.radius + other.collider().radius;
	//�Փ˔��苅�̏d�Ȃ��Ă��钷�������߂�
	float overlap = length - distance;
	//�d�Ȃ��Ă��镔���̔����̋������������ړ��ʂ����߂�
	GSvector3 v = (position - target).getNormalized() * overlap * 0.5f;
	transform_.translate(v, GStransform::Space::World);
	//�t�B�[���h�Ƃ̏Փ˔���
	collide_field();
}

//��Ԃ̕ύX
void Enemy_Golem::change_state(State state, GSuint motion, bool loop) {
	//���[�V�����ԍ��̍X�V
	motion_ = motion;
	//���[�V�������[�v�w��
	motion_loop_ = loop;
	//��Ԃ̍X�V
	state_ = state;
	//��ԃ^�C�}�[�̏�����
	state_timer_ = 0.0f;
}

//�A�C�h�����
void Enemy_Golem::idle(float delta_time) {
	// �U�����邩�H
	if (is_attack())
	{
		// �U����ԂɑJ��
		change_state(State::Attack, MotionAttack);
		return;
	}
	// �������H
	if (is_walk())
	{
		// ������ԂɑJ��
		change_state(State::Walk, MotionWalk);
		return;
	}
	// �����Ȃ���΁A�A�C�h�����̂܂�
	change_state(State::Idle, MotionIdle);
}

//�ړ���
void Enemy_Golem::walk(float delta_time) {
	// �^�[�Q�b�g�����̊p�x�����߂�
	float angle = target_signed_angle();
	// �U������p�x�����p�x�̍������邩�H
	if (std::abs(angle) > (TurnAngle * delta_time)) {
		// �p�x�����傫���ꍇ�́A������������ς���悤�Ɋp�x�𐧌�����
		angle = CLAMP(angle, -TurnAngle, TurnAngle) * delta_time;
	}
	// ������ς���
	transform_.rotate(0.0f, angle, 0.0f);
	// �O�i����i���[�J�����W��j
	transform_.translate(0.0f, 0.0f, WalkSpeed * delta_time);
	// �U�����邩�H
	if (is_attack())
	{
		// �U����ԂɑJ�ڂ���
		change_state(State::Attack, MotionAttack);
	}
}

//�U�������
void Enemy_Golem::turn(float delta_time) {
	if (state_timer_ >= mesh_.motion_end_time()) {
		// �U��������[�V�������I��������A�C�h�����ɑJ��
		idle(delta_time);
	}
	else
	{
		// �U��������[�V���������Ȃ���^�[�Q�b�g����������
		float angle = (target_signed_angle() >= 0.0f) ? TurnAngle : -TurnAngle;
		transform_.rotate(0.0f, angle * delta_time, 0.0f);
	}
}

//�U����
void Enemy_Golem::attack(float delta_time) {
	if (state_timer_ >= mesh_.motion_end_time() * 0.4f && state_timer_ <= mesh_.motion_end_time() * 0.45f)
	{
		//�U�����萶��
		generate_attack_collider();
	}
	if (state_timer_ >= mesh_.motion_end_time())
	{
		// �U�����[�V�������I��������A�C�h�����ɑJ��
		idle(delta_time);
	}
}

//�^�[�����Ă��邩
bool Enemy_Golem::is_turn()const {
	return(target_distance() <= TurnDistance);
}

//�U�����Ă��邩
bool Enemy_Golem::is_attack()const {
	return (target_distance() <= AttackDistance) && (target_angle() <= 20.0f);
}

//�����Ă��邩
bool Enemy_Golem::is_walk()const {
	return(target_distance() <= WalkDistance) && (target_angle() <= 360.0f);
}

//�U�����萶��
void Enemy_Golem::generate_attack_collider() {
	//�U��������o��������ꏊ�̋���
	const float AttackColliderDistance{ 3.0f };
	//�U������̔��a
	const float AttackColliderRadius{ 1.5f };
	//�U��������o���ꏊ�̍���
	const float AttackColliderHeight{ 2.0f };
	//�U�����肪�L���ɂȂ�܂ł̒x������
	const float AttackCollideDelay{ 15.0f };
	//�U������̎���
	const float AttackCollideLifeSpan{ 5.0f };
	//�Փ˔�����o����������W���߂�i�O���̈ʒu�j
	GSvector3 position = transform_.position() + transform_.forward() * AttackColliderDistance;
	//�����̕␳�i�����̍����j
	position.y += AttackColliderHeight;
	//�Փ˔���p�̒e���쐬
	BoundingSphere collider{ AttackColliderRadius,position };
	//�Փ˔�����o��������
	world_->add_actor(new AttackCollider{ world_,collider,
		"EnemyAttackTag","EnemyAttack",tag_,AttackCollideLifeSpan,AttackCollideDelay });
}