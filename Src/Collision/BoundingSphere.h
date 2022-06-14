#ifndef BOUNDING_SPHERE_H_
#define BOUNDING_SPHERE_H_
#include <gslib.h>
//境界球クラス
class BoundingSphere {
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="radius">半径</param>
	/// <param name="center">中心</param>
	BoundingSphere(float radius = 0.0f, const GSvector3& center = GSvector3{ 0.0f,0.0f,0.0f });
	/// <summary>
	/// 平行移動
	/// </summary>
	/// <param name="position">座標</param>
	/// <returns></returns>
	BoundingSphere translate(const GSvector3& position)const;
	/// <summary>
	/// 座標変換
	/// </summary>
	/// <param name="matrix">行列</param>
	/// <returns></returns>
	BoundingSphere transform(const GSmatrix4& matrix)const;
	/// <summary>
	/// 重なっているか
	/// </summary>
	/// <param name="other">重なっている球</param>
	/// <returns></returns>
	bool intersects(const BoundingSphere& other)const;
	//デバック表示
	void draw()const;
public:
	//半径
	float radius{ 0.0f };
	//中心座標
	GSvector3 center{ 0.0f,0.0f,0.0f };

};
#endif