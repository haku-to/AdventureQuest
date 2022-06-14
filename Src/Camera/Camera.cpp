#include "Camera.h"
#include "World/IWorld.h"
#include "Common_Number.h"
// プレーヤーからの相対位置（z座標のみ）
const GSvector3 PlayerOffset{ 0.0f, 0.0f, -5.0f };
// カメラの注視点の補正値
const GSvector3 ReferencePointOffset{ 0.0f, 1.8f, 0.0f };

// コンストラクタ
Camera::Camera(IWorld* world,
    const GSvector3& position, const GSvector3& at) {
    // ワールドを設定
    world_ = world;
    // タグの設定
    tag_ = "CamaraTag";
    // 名前の設定
    name_ = "Camera";
    // 視点の位置を設定
    transform_.position(position);
    // 注視点を設定
    transform_.lookAt(at);
    // ｘ軸周りの回転角度の初期化
    pitch_ = (at - position).getPitch();
    // ｙ軸周りの回転角度の初期化
    yaw_ = (at - position).getYaw();
}
// 更新
void Camera::update(float delta_time) {
    // プレーヤーを検索
    Actor* player = world_->find_actor(Common_Number::CharaName[Common_Number::CharacterNum]);
    if (player == nullptr) return;

    GSvector2 rAxis;
    gsXBoxPadGetRightAxis(0, &rAxis);
    // y軸方向にカメラを回転させる
    if (rAxis.x < 0)  yaw_ += 3.0f * delta_time;
    if (rAxis.x > 0) yaw_ += -3.0f * delta_time;
    // x軸方向に中心にカメラを回転させる
    if (rAxis.y > 0)   pitch_ += -1.0f * delta_time;
    if (rAxis.y < 0) pitch_ += 1.0f * delta_time;
    // x軸方向の回転角度の制限をする
    pitch_ = CLAMP(pitch_, -15.0f, 30.0f);

    // 注視点の座標を求める
    GSvector3 at = player->transform().position() + ReferencePointOffset;
    // カメラの座標を求める
    GSvector3 position = at + GSquaternion::euler(pitch_, yaw_, 0.0f) * PlayerOffset;

    // 座標の設定
    transform_.position(position);
    // 注視点の方向を見る
    transform_.lookAt(at);
}

// 描画
void Camera::draw() const {
    // 視点の位置
    GSvector3 eye = transform_.position();
    // 注視点の位置
    GSvector3 at = eye + transform_.forward();
    // 視点の上方向
    GSvector3 up = transform_.up();
    // 視点の位置
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
        eye.x, eye.y, eye.z,     // 視点の位置
        at.x, at.y, at.z,     // 注視点の位置
        up.x, up.y, up.z      // 視点の上方向
    );
}