#ifndef ACTOR_H_
#define ACTOR_H_
#include<gslib.h>
#include<GStransform.h>
#include<string>
#include"Collision/BoundingSphere.h"
//ワールド抽象インターフェースの前方宣言
class IWorld;
//アクタークラス
class Actor {
public:
	//コンストラクタ
	Actor() = default;
	//仮想デストラクタ
	virtual ~Actor() = default;
	//更新
	virtual void update(float delta_time);
	//遅延更新
	virtual void late_update(float delta_time);
	//描画
	virtual void draw()const;
	//半透明の描画
	virtual void draw_transparent()const;
	//GUIの描画
	virtual void draw_gui()const;
	/// <summary>
	/// 衝突リアクション
	/// </summary>
	/// <param name="other">衝突した他アクタ</param>
	virtual void react(Actor& other);
	/// <summary>
	/// メッセージ処理
	/// </summary>
	/// <param name="message">メッセージ</param>
	/// <param name="param">パラメータ</param>
	virtual void handle_message(const std::string& message, void* param);
	/// <summary>
	/// 衝突判定
	/// </summary>
	/// <param name="other">衝突した他アクタ</param>
	void collide(Actor& other);
	//死亡
	void die();
	/// <summary>
	/// 衝突しているか
	/// </summary>
	/// <param name="other">衝突した他アクタ</param>
	/// <returns></returns>
	bool is_collide(const Actor& other)const;
	//死亡しているか
	bool is_dead()const;
	//ダメージを受けているか
	bool is_damage()const;
	// 名前を取得
	const std::string& name()const;
	//タグを取得
	const std::string& tag()const;
	//体力を取得
	const int& health()const;
	//トランスフォームを取得(const)
	const GStransform& transform()const;
	//トランスフォームを取得
	GStransform& transform();
	//移動量を取得
	GSvector3 velocity()const;
	//衝突判定データの取得
	BoundingSphere collider() const;
	//コピー禁止
	Actor(const Actor& other) = delete;
	Actor& operator = (const Actor& other) = delete;
protected:
	//ワールド
	IWorld* world_{ nullptr };
	//タグ名
	std::string tag_;
	//名前
	std::string name_;
	//トランスフォーム
	GStransform transform_;
	//移動量
	GSvector3 velocity_{ 0.0f,0.0f,0.0f };
	//衝突判定が有効か
	bool enable_collider_{ true };
	//衝突判定
	BoundingSphere collider_;
	//体力
	int health_ = 0;
	//死亡フラグ
	bool dead_{ false };
	//ダメージフラグ
	bool is_damage_{ false };
};
#endif
