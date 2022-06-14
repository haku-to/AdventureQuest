#include "MageAttackCollider.h"
#include "World/IWorld.h"
#include "Rendering/Field.h"
#include "Rendering/Line.h"

//コンストラクタ
MageAttackCollider::MageAttackCollider(IWorld* world, const GSvector3& position, const GSvector3& velocity) {
	//ワールド設定
	world_ = world;
	//タグ名
	tag_ = "MageAttackTag";
	//アクター名
	name_ = "MageAttack";
	//移動量の初期化
	velocity_ = velocity;
	//衝突判定
	collider_ = BoundingSphere{ 0.2 };
	//座標の初期化
	transform_.position(position);
	//寿命
	lifespan_timer_ = 60.0f;
}

//更新
void MageAttackCollider::update(float delta_time) {
	//寿命が尽きたら死亡
	if (lifespan_timer_ <= 0.0f) {
		die();
		return;
	}
	//寿命更新
	lifespan_timer_ -= delta_time;
	//フィールドとの衝突判定
	Line line;
	line.start = transform_.position();
	line.end = transform_.position();
	GSvector3 intersect;
	if (world_->field()->collide(line, &intersect)) {
		//交点の座標に補正
		transform_.position(intersect);
		//フィールドに衝突したら死亡
		die();
		return;
	}
	//移動
	transform_.translate(velocity_ * delta_time, GStransform::Space::World);
}
//描画
void MageAttackCollider::draw()const {
	collider().draw();
}

//衝突リアクション
void MageAttackCollider::react(Actor& other) {
	die();
}