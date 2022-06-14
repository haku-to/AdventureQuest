#ifndef FIELD_H_
#define FIELD_H_
#include <gslib.h>

class Ray;
class Line;
class BoundingSphere;

// �t�B�[���h�N���X
class Field {
public:
    // �R���X�g���N�^
    Field(GSuint octree, GSuint collider, GSuint skybox);

    // �X�V
    void update(float delta_time);
    // �`��
    void draw() const;

    /// <summary>
    /// �����Ƃ̏Փ˔���
    /// </summary>
    /// <param name="line">���C��</param>
    /// <param name="intersect">����</param>
    /// <param name="plane">�v���[��</param>
    /// <returns></returns>
    bool collide(const Line& line,
        GSvector3* intersect = nullptr, GSplane* plane = nullptr) const;
    /// <summary>
    /// ���C�Ƃ̏Փ˔���
    /// </summary>
    /// <param name="ray">���C</param>
    /// <param name="max_distance">�ő勗��</param>
    /// <param name="intersect">����</param>
    /// <param name="plane">�v���[��</param>
    /// <returns></returns>
    bool collide(const Ray& ray, float max_distance,
        GSvector3* intersect = nullptr, GSplane* plane = nullptr) const;
    /// <summary>
    ///  ���̂Ƃ̏Փ˔���
    /// </summary>
    /// <param name="sphere">�X�t�B�A�R���C�_�[</param>
    /// <param name="center">���S���W</param>
    /// <returns></returns>
    bool collide(const BoundingSphere& sphere, GSvector3* center = nullptr) const;

    // �R�s�[�֎~
    Field(const Field& other) = delete;
    Field& operator = (const Field& other) = delete;

private:
    // �`��p�I�N�g���[
    GSuint	octree_;
    // �Փ˔���p�I�N�g���[
    GSuint	collider_;
    // �X�J�C�{�b�N�X
    GSuint	skybox_;
};

#endif