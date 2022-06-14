#ifndef GAME_PLAY_SCENE_H_
#define GAME_PLAY_SCENE_H_
#include "IScene.h"
#include "World/World.h"
#include"Actor/Player/Knight.h"
//ゲームプレイシーン
class GamePlayScene :public IScene {
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
	//プレイヤー
	Knight player_;
	//ワールド
	World world_;
	//ボタンが押されたか？
	bool push_button_{ false };
	//ステージ遷移時間
	float next_stage_time_{ 60.0f };
	//クエスト画像のスケール値
	float quest_scale_{ 3.0f };
	//クエスト画像の回転値
	float quest_lotate_{ 700.0f };
	//ゲームスタートタイマー
	float game_start_timer_{ 200.0f };
	//回転速度
	float lotate_speed_{ 8.0f };
	//拡大速度
	float scale_speed_{ 100.0f };
	//次のシーンの番号
	int next_scene_{ 0 };
	//次のシーンがタイトルシーンか
	bool next_title_{ false };
	//ゲームスタートしているか
	bool game_start_{ false };
	//一度だけ呼び出すためのブール
	bool only_one_{ false };
	//BGMをストップさせるか
	bool bgm_stop_{ false };
	//終了しているか
	bool is_end_{ false };
};
#endif