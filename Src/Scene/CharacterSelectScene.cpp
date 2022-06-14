#include"CharacterSelectScene.h"
#include"Common_Number.h"
#include"Assets.h"
#include"Music/SE.h"
#include"Music/BGM.h"
//キャラクターセレクト文字
const GSvector2 UIposition_CharacterSelect{ 370.0f,50.0f };
//背景位置
const  GSvector2 UIposition_BackGround{ 0.0f,0.0f };
//セレクトフレーム
const  GSvector2 TexCenter_SelectFrame{ 155.0f,205.0f };
//キャラクター画像ポジション
const GSvector2 Texposisition_Knight{ 100.0f,200.0f };
const GSvector2 Texposisition_Fighter{ 500.0f,200.0f };
const GSvector2 Texposisition_Ranger{ 900.0f,200.0f };
//キャラクター名前ポジション
const GSvector2 Texposisition_Knight_Name{ 190.0f,650.0f };
const GSvector2 Texposisition_Fighter_Name{ 580.0f,650.0f };
const GSvector2 Texposisition_Ranger_Name{ 970.0f,650.0f };
//各キャラクター勝利時の星位置
const GSvector2 WinStar_Position_Knight{ 100.0f,200.0f };
const GSvector2 WinStar_Position_Fighter{ 500.0f,200.0f };
const GSvector2 WinStar_Position_Ranger{ 900.0f,200.0f };

//開始
void CharacterSelectScene::start() {
	//画像読み込み
	//背景画像
	gsLoadTexture(BackGround, "Assets/Texture/BackGround.png");
	//セレクトフレーム画像
	gsLoadTexture(Select_Frame, "Assets/Texture/CharacterSelectFrame.png");
	//キャラクター画像
	//ナイト画像
	gsLoadTexture(Select_Knight, "Assets/Texture/KnightSelect.png");
	//ファイター画像
	gsLoadTexture(Select_Fighter, "Assets/Texture/FighterSelect.png");
	//レンジャー画像
	gsLoadTexture(Select_Ranger, "Assets/Texture/RangerSelect.png");
	//キャラクター名前
	//ナイト名前
	gsLoadTexture(Name_Knight, "Assets/Texture/Name_Knight.png");
	//ファイター名前
	gsLoadTexture(Name_Fighter, "Assets/Texture/Name_Fighter.png");
	//レンジャー名前
	gsLoadTexture(Name_Ranger, "Assets/Texture/Name_Ranger.png");
	//キャラクターセレクト文字
	gsLoadTexture(Select_CharacterSelect, "Assets/Texture/CharacterSelect.png");
	//星画像
	gsLoadTexture(Win_Star, "Assets/Texture/WinStar.png");
	//SE読み込み
	SE::Load();
	//BGM読み込み
	BGM::Load();
	//BGMを再生する
	BGM::PlayMusic(BGM_CharaSelect);
	//終了フラグ初期化
	is_end_ = false;
	//ボタンフラグ初期化
	push_button_ = false;
	//タイマー初期化
	next_stage_time_ = 60.0f;
}

//更新
void CharacterSelectScene::update(float delta_time) {
	//ボタンフラグがtrueなら
	if (push_button_)
	{
		//セレクトフレームの拡大率を１にする
		select_frame_scale_ = 1.0f;
		//タイマー開始
		next_stage_time_ -= delta_time;
		if (next_stage_time_ <= 0)
			// シーン終了
			is_end_ = true;
	}
	else
	{
		//Bボタンが押されたら
		if (gsGetJoyTrigger(0, GJOY_BUTTON_2)) {
			//セレクト音再生
			SE::PlaySE(SE_Select);
			//ボタンフラグをtrueにする
			push_button_ = true;
		}
	}
	//ボタンが押されていなくてジョイスティックの左が選択されたら
	if (gsGetJoyTrigger(0, GJOY_LEFT) && !push_button_)
	{
		//キャラクターの数によって
		if (Common_Number::CharacterNum > 0)
		{
			//セレクト変更音を出す
			SE::PlaySE(SE_SelectMove);
			//キャラクターナンバーを変える
			Common_Number::CharacterNum--;
			//フレームポジションを変える
			select_frame_pos_ -= select_frame_movement_;
			//スケールを１に初期化する
			select_frame_scale_ = 1.0f;
		}
	}
	//ボタンが押されていなくてジョイスティックの右が選択されたら
	if (gsGetJoyTrigger(0, GJOY_RIGHT) && !push_button_)
	{
		//キャラクターの数によってポジションを変える
		if (Common_Number::CharacterNum < 2)
		{
			//セレクト変更音を出す
			SE::PlaySE(SE_SelectMove);
			//キャラクターナンバーを変える
			Common_Number::CharacterNum++;
			//フレームポジションを変える
			select_frame_pos_ += select_frame_movement_;
			//スケールを１に初期化する
			select_frame_scale_ = 1.0f;
		}
	}
	//ボタンフラグがfalseかつフレームの拡大量が一定量を超えたら
	if (!push_button_ && select_frame_scale_ <= 1.2f)
	{
		//デルタタイムにの
		select_frame_scale_ += delta_time * select_frame_diameter_;
	}
	else
		//trueになったら
		select_frame_scale_ = 1.0f;

}

//描画
void CharacterSelectScene::draw()const {
	//ボタン位置
	const  GSvector2 TexPosition_Frame{ select_frame_pos_,400.0f };
	const  GSvector2 TexScale_Frame{ select_frame_scale_,select_frame_scale_ };
	//画像描画
	// 背景
	gsDrawSprite2D(BackGround, &UIposition_BackGround, NULL, NULL, NULL, NULL, 0.0f);
	//セレクトフレーム
	gsDrawSprite2D(Select_Frame, &TexPosition_Frame, NULL, &TexCenter_SelectFrame, NULL, &TexScale_Frame, 0.0f);
	//ナイト画像
	gsDrawSprite2D(Select_Knight, &Texposisition_Knight, NULL, NULL, NULL, NULL, 0.0f);
	//ファイター画像
	gsDrawSprite2D(Select_Fighter, &Texposisition_Fighter, NULL, NULL, NULL, NULL, 0.0f);
	//レンジャー画像
	gsDrawSprite2D(Select_Ranger, &Texposisition_Ranger, NULL, NULL, NULL, NULL, 0.0f);
	//ナイト名前
	gsDrawSprite2D(Name_Knight, &Texposisition_Knight_Name, NULL, NULL, NULL, NULL, 0.0f);
	//ファイター画像
	gsDrawSprite2D(Name_Fighter, &Texposisition_Fighter_Name, NULL, NULL, NULL, NULL, 0.0f);
	//レンジャー画像
	gsDrawSprite2D(Name_Ranger, &Texposisition_Ranger_Name, NULL, NULL, NULL, NULL, 0.0f);
	//キャラクターセレクト文字
	gsDrawSprite2D(Select_CharacterSelect, &UIposition_CharacterSelect, NULL, NULL, NULL, NULL, 0.0f);
	//ナイト星
	if(Common_Number::is_knight_win_)
	gsDrawSprite2D(Win_Star, &WinStar_Position_Knight, NULL, NULL, NULL, NULL, 0.0f);
	//ファイター星 
	if (Common_Number::is_fighter_win_)
	gsDrawSprite2D(Win_Star, &WinStar_Position_Fighter, NULL, NULL, NULL, NULL, 0.0f);
	//レンジャー星 
	if (Common_Number::is_ranger_win_)
	gsDrawSprite2D(Win_Star, &WinStar_Position_Ranger, NULL, NULL, NULL, NULL, 0.0f);
}
bool

//終了しているか
CharacterSelectScene::is_end()const {
	return is_end_;
}

//次のシーンに返す
std::string CharacterSelectScene::next()const {
	return"GamePlayScene";
}

//終了
void CharacterSelectScene::end()
{
	//画像データ削除
	//背景
	gsDeleteTexture(BackGround);
	//キャラクターセレクト文字
	gsDeleteTexture(Select_CharacterSelect);
	//ナイト画像
	gsDeleteTexture(Select_Knight);
	//レンジャー画像
	gsDeleteTexture(Select_Ranger);
	//ファイター画像
	gsDeleteTexture(Select_Fighter);
	//ネーム画像削除
	//ナイト名前
	gsDeleteTexture(Name_Knight);
	//レンジャー名前
	gsDeleteTexture(Name_Ranger);
	//ファイター名前
	gsDeleteTexture(Name_Fighter);
	//セレクトフレーム
	gsDeleteTexture(Select_Frame);
	//BGM削除
	BGM::DeleteMusic();
	//SE削除
	SE::DeleteSE();
}