#ifndef INVISIBLE_WALL_H_
#define INVISIBLE_WALL_H_

#include "Actor/Actor.h"
#include"World/World.h"
//�����Ȃ��ǃN���X
class InvisibleWall : public Actor {
public:
	//�R���X�g���N�^
	InvisibleWall(IWorld* world, const GSvector3& position, std::string keyname);
	//�X�V
	virtual void update(float delta_time) override;
private:
	std::string key_name_;
};

#endif