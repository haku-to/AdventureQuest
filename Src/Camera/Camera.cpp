#include "Camera.h"
#include "World/IWorld.h"
#include "Common_Number.h"
// �v���[���[����̑��Έʒu�iz���W�̂݁j
const GSvector3 PlayerOffset{ 0.0f, 0.0f, -5.0f };
// �J�����̒����_�̕␳�l
const GSvector3 ReferencePointOffset{ 0.0f, 1.8f, 0.0f };

// �R���X�g���N�^
Camera::Camera(IWorld* world,
    const GSvector3& position, const GSvector3& at) {
    // ���[���h��ݒ�
    world_ = world;
    // �^�O�̐ݒ�
    tag_ = "CamaraTag";
    // ���O�̐ݒ�
    name_ = "Camera";
    // ���_�̈ʒu��ݒ�
    transform_.position(position);
    // �����_��ݒ�
    transform_.lookAt(at);
    // ��������̉�]�p�x�̏�����
    pitch_ = (at - position).getPitch();
    // ��������̉�]�p�x�̏�����
    yaw_ = (at - position).getYaw();
}
// �X�V
void Camera::update(float delta_time) {
    // �v���[���[������
    Actor* player = world_->find_actor(Common_Number::CharaName[Common_Number::CharacterNum]);
    if (player == nullptr) return;

    GSvector2 rAxis;
    gsXBoxPadGetRightAxis(0, &rAxis);
    // y�������ɃJ��������]������
    if (rAxis.x < 0)  yaw_ += 3.0f * delta_time;
    if (rAxis.x > 0) yaw_ += -3.0f * delta_time;
    // x�������ɒ��S�ɃJ��������]������
    if (rAxis.y > 0)   pitch_ += -1.0f * delta_time;
    if (rAxis.y < 0) pitch_ += 1.0f * delta_time;
    // x�������̉�]�p�x�̐���������
    pitch_ = CLAMP(pitch_, -15.0f, 30.0f);

    // �����_�̍��W�����߂�
    GSvector3 at = player->transform().position() + ReferencePointOffset;
    // �J�����̍��W�����߂�
    GSvector3 position = at + GSquaternion::euler(pitch_, yaw_, 0.0f) * PlayerOffset;

    // ���W�̐ݒ�
    transform_.position(position);
    // �����_�̕���������
    transform_.lookAt(at);
}

// �`��
void Camera::draw() const {
    // ���_�̈ʒu
    GSvector3 eye = transform_.position();
    // �����_�̈ʒu
    GSvector3 at = eye + transform_.forward();
    // ���_�̏����
    GSvector3 up = transform_.up();
    // ���_�̈ʒu
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
        eye.x, eye.y, eye.z,     // ���_�̈ʒu
        at.x, at.y, at.z,     // �����_�̈ʒu
        up.x, up.y, up.z      // ���_�̏����
    );
}