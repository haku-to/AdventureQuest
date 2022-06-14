#ifndef CAMERA_H_
#define CAMERA_H_

#include "Actor/Actor.h"

// �O�l�̃J�����N���X
class Camera : public Actor {
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="world">���[���h</param>
    /// <param name="position">���������W</param>
    /// <param name="at">�����_�ʒu</param>
    Camera(IWorld* world, const GSvector3& position, const GSvector3& at);
    // �X�V
    virtual void update(float delta_time) override;
    // �`��
    virtual void draw() const override;

private:
    // y������̉�]�p�x
    float yaw_{ 0.0f };
    // x������̉�]�p�x
    float pitch_{ 0.0f };
};

#endif