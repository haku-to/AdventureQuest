#ifndef INVISIBLE_WALL_H_
#define INVISIBLE_WALL_H_

#include "Actor/Actor.h"
#include"World/World.h"
//見えない壁クラス
class InvisibleWall : public Actor {
public:
	//コンストラクタ
	InvisibleWall(IWorld* world, const GSvector3& position, std::string keyname);
	//更新
	virtual void update(float delta_time) override;
private:
	std::string key_name_;
};

#endif