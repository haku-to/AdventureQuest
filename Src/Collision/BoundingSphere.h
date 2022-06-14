#ifndef BOUNDING_SPHERE_H_
#define BOUNDING_SPHERE_H_
#include <gslib.h>
//���E���N���X
class BoundingSphere {
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="radius">���a</param>
	/// <param name="center">���S</param>
	BoundingSphere(float radius = 0.0f, const GSvector3& center = GSvector3{ 0.0f,0.0f,0.0f });
	/// <summary>
	/// ���s�ړ�
	/// </summary>
	/// <param name="position">���W</param>
	/// <returns></returns>
	BoundingSphere translate(const GSvector3& position)const;
	/// <summary>
	/// ���W�ϊ�
	/// </summary>
	/// <param name="matrix">�s��</param>
	/// <returns></returns>
	BoundingSphere transform(const GSmatrix4& matrix)const;
	/// <summary>
	/// �d�Ȃ��Ă��邩
	/// </summary>
	/// <param name="other">�d�Ȃ��Ă��鋅</param>
	/// <returns></returns>
	bool intersects(const BoundingSphere& other)const;
	//�f�o�b�N�\��
	void draw()const;
public:
	//���a
	float radius{ 0.0f };
	//���S���W
	GSvector3 center{ 0.0f,0.0f,0.0f };

};
#endif