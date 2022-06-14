#ifndef TITLE_SCENE_H_
#define TITLE_SCENE_H_
#include "IScene.h"
#include <gslib.h>
//タイトルシーンクラス
class TitleScene :public IScene {
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
	//ボタン点滅
	bool look_button_{ true };
	//ボタン点滅時間
	float button_count_{ 0.0f };
	//ボタン点滅間隔
	float button_count_distance_{ 30.0f };
	//ステージ遷移時間
	float next_stage_time_{ 60.0f };
	//次のステージの名前
	std::string next_stage_set;
};
#endif
