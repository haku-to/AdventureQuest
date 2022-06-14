#ifndef CHARACTER_SELECT_SCENE_H_
#define CHARACTER_SELECT_SCENE_H_
#include "IScene.h"
#include <gslib.h>
//キャラクターセレクトシーンクラス
class CharacterSelectScene :public IScene {
	//開始
	virtual void start()override;
	//更新
	virtual void update(float delta_time)override;
	//描画
	virtual void draw()const override;
	//終了しているか？
	virtual bool is_end()const override;
	//次のシーンを返す
	virtual std::string  next()const override;
	//終了
	virtual void end()override;
private:
	//終了フラグ
	bool is_end_{ false };
	//ボタンが押されたか？
	bool push_button_{ false };
	//ステージ遷移時間
	float next_stage_time_{ 60.0f };
	//セレクトフレームのスケール倍率
	const float select_frame_diameter_{ 0.01f };
	//セレクトフレームの移動値
	const float select_frame_movement_{ 400.0f };
	//セレクトフレームのX位置
	float select_frame_pos_{ 250.0f };
	//セレクトフレームのスケール変更値
	float select_frame_scale_{ 1.0f };
	//次のステージ番号
	int next_stage_{ 0 };
	//次のステージの名前
	std::string next_stage_set;
};
#endif