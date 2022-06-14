#ifndef ATTACK_COLLIDER_H_
#define ATTACK_COLLIDER_H_
#include "Actor/Actor.h"
// �U������
class AttackCollider : public Actor {
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="world">���[���h</param>
    /// <param name="collider">�����蔻��</param>
    /// <param name="tag">�^�O</param>
    /// <param name="name">���O</param>
    /// <param name="owner_tag">�g�p�҂̃^�O</param>
    /// <param name="lifespan">����</param>
    /// <param name="delay">�x��</param>
    AttackCollider(IWorld* world, const BoundingSphere& collider,
        const std::string& tag, const std::string& name,
        const std::string& owner_tag = "",
        float lifespan = 1.0f, float delay = 0.0f);
    // �X�V
    virtual void update(float delta_time) override;
    // �Փ˃��A�N�V����
    virtual void react(Actor& other) override;
private:
    // �U��������o���������A�N�^�[�̃^�O
    std::string owner_tag_;
    // ����
    float       lifespan_timer_;
    // �Փ˔��肪�L���ɂȂ�܂ł̒x������
    float       delay_timer_;
};
#endif