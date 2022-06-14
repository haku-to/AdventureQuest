#ifndef CAMERA_H_
#define CAMERA_H_

#include "Actor/Actor.h"

// 三人称カメラクラス
class Camera : public Actor {
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="world">ワールド</param>
    /// <param name="position">生成時座標</param>
    /// <param name="at">注視点位置</param>
    Camera(IWorld* world, const GSvector3& position, const GSvector3& at);
    // 更新
    virtual void update(float delta_time) override;
    // 描画
    virtual void draw() const override;

private:
    // y軸周りの回転角度
    float yaw_{ 0.0f };
    // x軸周りの回転角度
    float pitch_{ 0.0f };
};

#endif