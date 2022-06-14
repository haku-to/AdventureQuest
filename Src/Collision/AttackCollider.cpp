#include "AttackCollider.h"
// �R���X�g���N�^
AttackCollider::AttackCollider(IWorld* world, const BoundingSphere& collider,
    const std::string& tag, const std::string& name,
    const std::string& owner_tag, float lifespan, float delay) :
    lifespan_timer_{ lifespan }, delay_timer_{ delay } {
    // ���[���h�̐ݒ�
    world_ = world;
    // �^�O���̐ݒ�
    tag_ = tag;
    // �����҂̃^�O����ݒ�
    owner_tag_ = owner_tag;
    // ���O�̐ݒ�
    name_ = name;
    // �Փ˔����������
    collider_ = BoundingSphere{ collider.radius };
    // ���W�̏�����
    transform_.position(collider.center);
    // �Փ˔���𖳌��ɂ���
    enable_collider_ = false;
}

// �X�V
void AttackCollider::update(float delta_time) {
    // �x�����Ԃ��o�߂�����Փ˔����L���ɂ���
    if (delay_timer_ <= 0.0f)
    {
        // �Փ˔����L���ɂ���
        enable_collider_ = true;
        // �������s�����玀�S
        if (lifespan_timer_ <= 0.0f)
        {
            die();
        }
        // �����̍X�V
        lifespan_timer_ -= delta_time;
    }
    // �x�����Ԃ̍X�V
    delay_timer_ -= delta_time;
}

//�Փ˃��A�N�V����
void AttackCollider::react(Actor& other) {
    if (other.tag() == tag() || other.tag() == owner_tag_)return;
    die();
}