#ifndef ANIMATED_MESH_H_
#define ANIMATED_MESH_H_

#include <gslib.h>
#include <vector>

// �A�j���[�V�����t�����b�V���N���X
class AnimatedMesh {
public:
    // �R���X�g���N�^
    AnimatedMesh(GSuint mesh, GSuint skeleton, GSuint animation, GSuint motion = 0, bool loop = true, GSuint layer_count = 1, GSuint bone_count = 256);
    // �X�V
    void update(float delta_time);
    // �`��
    void draw() const;

    // ���[�V�����̕ύX�i���C���[�w��Ȃ��j
    void change_motion(GSuint motion, bool loop = true);
    // ���[�V�����̕ύX�i���C���[�w�肠��j
    void change_motion(GSuint layer, GSuint motion, bool loop = true);
    // ���C���[�C���f�b�N�X�̐ݒ�
    void set_layer_indices(GSuint layer_index, const GSuint layer_bones[], GSuint layer_bones_count);

    // �ϊ��s���ݒ肷��
    void transform(const GSmatrix4& matrix);
    // ���[�V�����̏I�����Ԃ��擾
    float motion_end_time(GSuint layer = 0) const;
    // ���[�V�������I�����Ă��邩�H
    bool is_motion_end(GSuint layer = 0) const;
    // �{�[���̃��[���h�ϊ��s����擾
    GSmatrix4 bone_matrices(int bone_no) const;
    // ���݂̃��[�V�����̍Đ����Ԃ��擾
    float current_motion_time(GSuint layer = 0) const;
    // ���݂̃��[�V�����̍Đ����Ԃ�ݒ�
    void current_motion_time(float time, GSuint layer = 0);

private:
    // �A�j���[�V�����N���X
    class Animation {
    public:
        // �R���X�g���N�^
        Animation(GSuint animation = 0, GSuint motion = 0, bool loop = true);
        // �X�V
        void update(float delta_time);
        // ���[�V�����̕ύX
        void change_motion(GSuint motion, bool loop = true);
        // ���[�V�����̍ŏI���Ԃ��擾
        float motion_end_time() const;
        // ���ݍĐ����̃��[�V�����^�C�}���擾
        float current_motion_time() const;
        // ���ݍĐ����̃��[�V�����^�C�}��ݒ�
        void current_motion_time(float time);
        // ���[�V�������I�����Ă��邩�H
        bool is_motion_end() const;
        // �{�[���̃��[�J���ϊ��s����擾
        GSmatrix4 local_bone_matrix(GSuint bone_no) const;
        // �{�[������Ԃ�
        GSuint bone_count() const;

    private:
        // �A�j���[�V����
        GSuint      animation_{ 0 };
        // ���[�V�����ԍ�
        GSuint      motion_{ 0 };
        // ���[�V�����^�C�}
        GSfloat     motion_timer_{ 0.0f };
        // ���[�V�������[�v�t���O
        bool        motion_loop_{ true };
        // �O��Đ��������[�V�����ԍ�
        GSuint      prev_motion_{ 0 };
        // �O��Đ������ŏI�A�j���[�V�����^�C�}
        GSfloat     prev_motion_timer_{ 0.0f };
        // ��ԃA�j���[�V�����^�C�}
        GSfloat     lerp_timer_{ 0.0f };
    };
    // ���b�V��
    GSuint                  mesh_;
    // �X�P���g��
    GSuint                  skeleton_;
    // �A�j���[�V�������C���[
    std::vector<Animation>  animation_layers_;
    // �A�j���[�V�������C���[�C���f�b�N�X
    std::vector<GSuint>     animation_layer_indices_;
    // �{�[���̃��[�J���ϊ��s��
    std::vector<GSmatrix4>  local_bone_matrices_;
    // �{�[���̕ϊ��s��
    std::vector<GSmatrix4>  bone_matrices_;
    // ���W�ϊ��s��
    GSmatrix4               transform_;
};

#endif