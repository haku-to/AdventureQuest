#include"TitleScene.h"
#include"Assets.h"
#include"Music/BGM.h"
#include"Music/SE.h"
#include"Common_Number.h"
//背景位置
const  GSvector2 UIposition_BackGround{ 0.0f,0.0f };
//ボタン位置
const  GSvector2 UIposition_PushtoStart{ 460.0f,520.0f };
void TitleScene::start() {
	//画像読み込み
	gsLoadTexture(Title_BackGround, "Assets/Texture/TitleBackGround.png");
	gsLoadTexture(Title_PushtoStart, "Assets/Texture/PushtoStart.png");
	//SE読み込み
	SE::Load();
	//BGM読み込み
	BGM::Load();
	//BGM再生
	BGM::PlayMusic(BGM_Title);
	//終了フラグ初期化
	is_end_ = false;
	//ボタンフラグ初期化
	push_button_ = false;
	//ボタン点滅間隔初期化
	button_count_distance_ = 30.0f;
	//ステージタイマー初期化
	next_stage_time_ = 60.0f;
	//ゲームクリア判定初期化
	Common_Number::is_game_clear_ = false;
	//ゲームオーバー判定の初期化
	Common_Number::is_game_over_ = false;
}
void TitleScene::update(float delta_time) {
	if (push_button_)
	{
		next_stage_time_ -= delta_time;
		if (next_stage_time_ <= 0)
			is_end_ = true;     // シーン終了
	}
	else
	{
		if (gsGetJoyTrigger(0, GJOY_BUTTON_2))
		{
			push_button_ = true;
			SE::PlaySE(SE_Select);
			button_count_distance_ = 12.0f;
		}
	}
	if (button_count_ >= button_count_distance_) {
		look_button_ = !look_button_;
		button_count_ = 0.0f;
	}
	else
	{
		button_count_ += delta_time;
	}
}

//描画
void TitleScene::draw()const {
	// 背景の描画
	gsDrawSprite2D(Title_BackGround, &UIposition_BackGround, NULL, NULL, NULL, NULL, 0.0f);
	if (look_button_)gsDrawSprite2D(Title_PushtoStart, &UIposition_PushtoStart, NULL, NULL, NULL, NULL, 0.0f);
}

//終了フラグ
bool TitleScene::is_end()const {
	return is_end_;
}

//次のシーン
std::string TitleScene::next()const {
	return"CharacterSelect";
}

//終了
void TitleScene::end()
{
	//アセット削除
	//背景画像
	gsDeleteTexture(Title_BackGround);
	//タイトルボタン
	gsDeleteTexture(Title_PushtoStart);
	//SE削除
	SE::DeleteSE();
	//BGM削除
	BGM::DeleteMusic();
}