#ifndef ATTACK_COLLIDER_H_
#define ATTACK_COLLIDER_H_
#include "Actor/Actor.h"
// 攻撃判定
class AttackCollider : public Actor {
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="world">ワールド</param>
    /// <param name="collider">当たり判定</param>
    /// <param name="tag">タグ</param>
    /// <param name="name">名前</param>
    /// <param name="owner_tag">使用者のタグ</param>
    /// <param name="lifespan">寿命</param>
    /// <param name="delay">遅延</param>
    AttackCollider(IWorld* world, const BoundingSphere& collider,
        const std::string& tag, const std::string& name,
        const std::string& owner_tag = "",
        float lifespan = 1.0f, float delay = 0.0f);
    // 更新
    virtual void update(float delta_time) override;
    // 衝突リアクション
    virtual void react(Actor& other) override;
private:
    // 攻撃判定を出現させたアクターのタグ
    std::string owner_tag_;
    // 寿命
    float       lifespan_timer_;
    // 衝突判定が有効になるまでの遅延時間
    float       delay_timer_;
};
#endif