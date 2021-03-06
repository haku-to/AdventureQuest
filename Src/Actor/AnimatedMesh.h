#ifndef ANIMATED_MESH_H_
#define ANIMATED_MESH_H_

#include <gslib.h>
#include <vector>

// アニメーション付きメッシュクラス
class AnimatedMesh {
public:
    // コンストラクタ
    AnimatedMesh(GSuint mesh, GSuint skeleton, GSuint animation, GSuint motion = 0, bool loop = true, GSuint layer_count = 1, GSuint bone_count = 256);
    // 更新
    void update(float delta_time);
    // 描画
    void draw() const;

    // モーションの変更（レイヤー指定なし）
    void change_motion(GSuint motion, bool loop = true);
    // モーションの変更（レイヤー指定あり）
    void change_motion(GSuint layer, GSuint motion, bool loop = true);
    // レイヤーインデックスの設定
    void set_layer_indices(GSuint layer_index, const GSuint layer_bones[], GSuint layer_bones_count);

    // 変換行列を設定する
    void transform(const GSmatrix4& matrix);
    // モーションの終了時間を取得
    float motion_end_time(GSuint layer = 0) const;
    // モーションが終了しているか？
    bool is_motion_end(GSuint layer = 0) const;
    // ボーンのワールド変換行列を取得
    GSmatrix4 bone_matrices(int bone_no) const;
    // 現在のモーションの再生時間を取得
    float current_motion_time(GSuint layer = 0) const;
    // 現在のモーションの再生時間を設定
    void current_motion_time(float time, GSuint layer = 0);

private:
    // アニメーションクラス
    class Animation {
    public:
        // コンストラクタ
        Animation(GSuint animation = 0, GSuint motion = 0, bool loop = true);
        // 更新
        void update(float delta_time);
        // モーションの変更
        void change_motion(GSuint motion, bool loop = true);
        // モーションの最終時間を取得
        float motion_end_time() const;
        // 現在再生中のモーションタイマを取得
        float current_motion_time() const;
        // 現在再生中のモーションタイマを設定
        void current_motion_time(float time);
        // モーションが終了しているか？
        bool is_motion_end() const;
        // ボーンのローカル変換行列を取得
        GSmatrix4 local_bone_matrix(GSuint bone_no) const;
        // ボーン数を返す
        GSuint bone_count() const;

    private:
        // アニメーション
        GSuint      animation_{ 0 };
        // モーション番号
        GSuint      motion_{ 0 };
        // モーションタイマ
        GSfloat     motion_timer_{ 0.0f };
        // モーションループフラグ
        bool        motion_loop_{ true };
        // 前回再生したモーション番号
        GSuint      prev_motion_{ 0 };
        // 前回再生した最終アニメーションタイマ
        GSfloat     prev_motion_timer_{ 0.0f };
        // 補間アニメーションタイマ
        GSfloat     lerp_timer_{ 0.0f };
    };
    // メッシュ
    GSuint                  mesh_;
    // スケルトン
    GSuint                  skeleton_;
    // アニメーションレイヤー
    std::vector<Animation>  animation_layers_;
    // アニメーションレイヤーインデックス
    std::vector<GSuint>     animation_layer_indices_;
    // ボーンのローカル変換行列
    std::vector<GSmatrix4>  local_bone_matrices_;
    // ボーンの変換行列
    std::vector<GSmatrix4>  bone_matrices_;
    // 座標変換行列
    GSmatrix4               transform_;
};

#endif