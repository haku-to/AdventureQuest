#ifndef KNIGHT_H_
#define KNIGHT_H_
#include "Actor/Actor.h"
#include "Actor/AnimatedMesh.h"
#include "Camera/Camera.h"

//ナイトクラス
class Knight : public Actor {
    //ナイトの状態
    enum class State {
        Move,           // 通常移動
        Attack1,        // 攻撃
        Attack2,        // 攻撃
        ShieldOn,       //ガーと初め
        ShieldNow,      //ガード待ち
        ShieldOff,      //ガード終わり
        ShieldDamage,   //ガードダメージ
        Dodge,          //　回避
        Damage,         // ダメージ
        Dead,           //死亡
        Victory         //勝利
    };
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="world"></param>
    /// <param name="position">ポジション</param>
    Knight(IWorld* world = nullptr, const GSvector3& position = GSvector3{ 0.0f, 0.0f, 0.0f });
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="delta_time"></param>
    virtual void update(float delta_time) override;
    //描画
    virtual void draw()const override;
    //GUI描画
    virtual void draw_gui()const override;
    /// <summary>
    /// 衝突リアクション
    /// </summary>
    /// <param name="other">当たったアクター</param>
    virtual void react(Actor& other) override;

private:
    // 状態の更新
    void update_state(float delta_time);
    /// <summary>
    /// 状態変化
    /// </summary>
    /// <param name="state">変更する状態</param>
    /// <param name="motion">次のモーション</param>
    /// <param name="loop">ループするのか</param>
    void change_state(State state, GSuint motion, bool loop = true);
    // 移動処理
    void move(float delta_time);
    // 攻撃中
    void attack(float delta_time);
    // 攻撃中2
    void attack2(float delta_time);
    //ガード切り替え
    void shield_on(float delta_time);
    void shield_now(float delta_time);
    void shield_off(float delta_time);
    void hit_shield(float delta_time);
    //回避中
    void dodge(float delta_time);
    // ダメージ中
    void damage(float delta_time);
    //死亡中
    void dead(float delta_time);

    // フィールドとの衝突処理
    void collide_field();
    /// <summary>
    /// アクターの衝突判定
    /// </summary>
    /// <param name="other">衝突したアクター</param>
    void collide_actor(Actor& other);
    /// <summary>
    /// 攻撃判定生成
    /// </summary>
    /// <param name="name">攻撃者の名前</param>
    /// <param name="tag">攻撃者のタグ</param>
    /// <param name="delay">どれくらいで消えるか</param>
    void generate_attack_collider(const std::string name, const std::string tag, float delay);
    //必殺技
    void special_attack();
    /// <summary>
    /// 角度を求める
    /// </summary>
    /// <param name="target_pos">ターゲットのポジション</param>
    /// <returns></returns>
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
    float           state_timer_;
    //ボタンが押されている時間
    float           pushed_button_timer_;
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
