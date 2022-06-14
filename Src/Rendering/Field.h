#ifndef FIELD_H_
#define FIELD_H_
#include <gslib.h>

class Ray;
class Line;
class BoundingSphere;

// フィールドクラス
class Field {
public:
    // コンストラクタ
    Field(GSuint octree, GSuint collider, GSuint skybox);

    // 更新
    void update(float delta_time);
    // 描画
    void draw() const;

    /// <summary>
    /// 線分との衝突判定
    /// </summary>
    /// <param name="line">ライン</param>
    /// <param name="intersect">交差</param>
    /// <param name="plane">プレーン</param>
    /// <returns></returns>
    bool collide(const Line& line,
        GSvector3* intersect = nullptr, GSplane* plane = nullptr) const;
    /// <summary>
    /// レイとの衝突判定
    /// </summary>
    /// <param name="ray">レイ</param>
    /// <param name="max_distance">最大距離</param>
    /// <param name="intersect">交差</param>
    /// <param name="plane">プレーン</param>
    /// <returns></returns>
    bool collide(const Ray& ray, float max_distance,
        GSvector3* intersect = nullptr, GSplane* plane = nullptr) const;
    /// <summary>
    ///  球体との衝突判定
    /// </summary>
    /// <param name="sphere">スフィアコライダー</param>
    /// <param name="center">中心座標</param>
    /// <returns></returns>
    bool collide(const BoundingSphere& sphere, GSvector3* center = nullptr) const;

    // コピー禁止
    Field(const Field& other) = delete;
    Field& operator = (const Field& other) = delete;

private:
    // 描画用オクトリー
    GSuint	octree_;
    // 衝突判定用オクトリー
    GSuint	collider_;
    // スカイボックス
    GSuint	skybox_;
};

#endif