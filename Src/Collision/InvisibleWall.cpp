#include "InvisibleWall.h"
#include "World/IWorld.h"
#include"Assets.h"
#include"Music/SE.h"
InvisibleWall::InvisibleWall(IWorld* world, const GSvector3& position, std::string keyname) {
	// ワールドを設定
	world_ = world;
	// タグ名
	tag_ = "InvisibleWallTag";
	// アクター名
	name_ = "InvisibleWall";
	// 衝突判定
	collider_ = BoundingSphere{ 25.0f };
	//衝突判定が有効か
	enable_collider_ = true;
	// 座標の初期化
	transform_.position(position);
	key_name_ = keyname;
}
//更新
void InvisibleWall::update(float delta_time) {
	//壁解除のキーエネミーを検索する
	Actor* keyenemy_ = world_->find_actor(key_name_);
	//ワールドからキーエネミーが消えたら死ぬ
	if (keyenemy_ == nullptr) {
		//見えない壁解除音を鳴らす
		SE::PlaySE(SE_InvisibleOff);
		die();
	}
}