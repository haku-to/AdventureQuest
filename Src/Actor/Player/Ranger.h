#ifndef RANGER_H_
#define RANGER_H_
#include "Actor/Actor.h"
#include "Actor/AnimatedMesh.h"
#include "Camera/Camera.h"

//レンジャークラス
class Ranger : public Actor {
    //レンジャーの状態
    enum class State {
        Move,           // 通常移動
        Attack1,        // 攻撃
        Attack2,        // 攻撃
        Dodge,          //　回避
        Damage,         // ダメージ
        Dead,           //死亡
        Victory         //勝利
    };
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="world">ワールド</param>
    /// <param name="position">生成時座標</param>
    Ranger(IWorld* world = nullptr, const GSvector3& position = GSvector3{ 0.0f, 0.0f, 0.0f });
    // 更新
    virtual void update(float delta_time) override;
    // 描画
    virtual void draw()const override;
    // GUI描画
    virtual void draw_gui()const override;
    /// <summary>
    /// 衝突リアクション
    /// </summary>
    /// <param name="other">衝突したアクタ</param>
    virtual void react(Actor& other) override;

private:
    // 状態の更新
    void update_state(float delta_time);
    // 状態の変更
    void change_state(State state, GSuint motion, bool loop = true);
    // 移動処理
    void move(float delta_time);
    // 攻撃中
    void attack(float delta_time);
    // 攻撃中2
    void attack2(float delta_time);
    //回避中
    void dodge(float delta_time);
    // ダメージ中
    void damage(float delta_time);
    //死亡中
    void dead(float delta_time);
    // フィールドとの衝突処理
    void collide_field();
    // アクターとの衝突処理
    void collide_actor(Actor& other);
    // 攻撃判定の生成
    void generate_attack_collider(const std::string name, const std::string tag, float delay);
    //必殺技
    void special_attack();
    //角度を求める
    float target_angle(GSvector3 target_pos) const;
private:
    // アニメーションメッシュ
    AnimatedMesh    mesh_;
    // モーション番号
    GSuint          motion_;
    // モーションのループ指定
    bool            motion_loop_;
    //ダッシュ状態か
    bool is_running_;
    //ゲーム開始
    bool can_start_;
    // 状態
    State  state_;
    // 状態タイマ
    float state_timer_;
    //ボタンが押されている時間
    float pushed_button_timer_;
    //ゲーム開始カウント
    float start_timer_;
    //攻撃状態番号
    int attack_num_;
    //攻撃判定を出していいか
    bool can_attack_;
    //体力カラー
    float health_color_R;
    float health_color_G;
    float health_color_B;
    //体力
    float health_;
};

#endif