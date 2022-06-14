#include"BoundingSphere.h"
//�R���X�g���N�^
BoundingSphere::BoundingSphere(float radius, const GSvector3& center) :
	radius{ radius }, center{ center }{
}

//���s�ړ�
BoundingSphere BoundingSphere::translate(const GSvector3& position)const {
	return BoundingSphere{ radius,center + position };
}

//���W�ϊ�
BoundingSphere BoundingSphere::transform(const GSmatrix4& matrix)const {
	return BoundingSphere{ radius * matrix.getScale().y,matrix.transform(center) };
}

//�d�Ȃ��Ă��邩
bool BoundingSphere::intersects(const BoundingSphere& other)const {
	return gsCollisionSphereAndSphere(
		&center, radius, &other.center, other.radius) == GS_TRUE;
}

//�f�o�b�N�\��
void BoundingSphere::draw()const {
	glPushMatrix();
	glTranslatef(center.x, center.y, center.z);
	//���C���[�t���[���̋���
	glutWireSphere(radius, 16, 16);
	glPopMatrix();
}