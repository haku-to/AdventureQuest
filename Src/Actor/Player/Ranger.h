#ifndef RANGER_H_
#define RANGER_H_
#include "Actor/Actor.h"
#include "Actor/AnimatedMesh.h"
#include "Camera/Camera.h"

//�����W���[�N���X
class Ranger : public Actor {
    //�����W���[�̏��
    enum class State {
        Move,           // �ʏ�ړ�
        Attack1,        // �U��
        Attack2,        // �U��
        Dodge,          //�@���
        Damage,         // �_���[�W
        Dead,           //���S
        Victory         //����
    };
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="world">���[���h</param>
    /// <param name="position">���������W</param>
    Ranger(IWorld* world = nullptr, const GSvector3& position = GSvector3{ 0.0f, 0.0f, 0.0f });
    // �X�V
    virtual void update(float delta_time) override;
    // �`��
    virtual void draw()const override;
    // GUI�`��
    virtual void draw_gui()const override;
    /// <summary>
    /// �Փ˃��A�N�V����
    /// </summary>
    /// <param name="other">�Փ˂����A�N�^</param>
    virtual void react(Actor& other) override;

private:
    // ��Ԃ̍X�V
    void update_state(float delta_time);
    // ��Ԃ̕ύX
    void change_state(State state, GSuint motion, bool loop = true);
    // �ړ�����
    void move(float delta_time);
    // �U����
    void attack(float delta_time);
    // �U����2
    void attack2(float delta_time);
    //���
    void dodge(float delta_time);
    // �_���[�W��
    void damage(float delta_time);
    //���S��
    void dead(float delta_time);
    // �t�B�[���h�Ƃ̏Փˏ���
    void collide_field();
    // �A�N�^�[�Ƃ̏Փˏ���
    void collide_actor(Actor& other);
    // �U������̐���
    void generate_attack_collider(const std::string name, const std::string tag, float delay);
    //�K�E�Z
    void special_attack();
    //�p�x�����߂�
    float target_angle(GSvector3 target_pos) const;
private:
    // �A�j���[�V�������b�V��
    AnimatedMesh    mesh_;
    // ���[�V�����ԍ�
    GSuint          motion_;
    // ���[�V�����̃��[�v�w��
    bool            motion_loop_;
    //�_�b�V����Ԃ�
    bool is_running_;
    //�Q�[���J�n
    bool can_start_;
    // ���
    State  state_;
    // ��ԃ^�C�}
    float state_timer_;
    //�{�^����������Ă��鎞��
    float pushed_button_timer_;
    //�Q�[���J�n�J�E���g
    float start_timer_;
    //�U����Ԕԍ�
    int attack_num_;
    //�U��������o���Ă�����
    bool can_attack_;
    //�̗̓J���[
    float health_color_R;
    float health_color_G;
    float health_color_B;
    //�̗�
    float health_;
};

#endif