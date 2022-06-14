#include "Actor/Player/Knight.h"
#include "Actor/Player/Fighter.h"
#include "Actor/Player/Ranger.h"
#include "Actor/Enemy/Enemy_Skeleton.h"
#include "Actor/Enemy/Enemy_Doragon.h"
#include "Actor/Enemy/Enemy_Mage.h"
#include "Actor/Enemy/Enemy_Orc.h"
#include "Actor/Enemy/Enemy_Golem.h"
#include "Camera/Camera.h"
#include "Rendering/Field.h"
#include "Rendering/Light.h"
#include "Collision/InvisibleWall.h"
#include "GamePlayScene.h"
#include "Music/SE.h"
#include "Music/BGM.h"
#include "Common_Number.h"
#include "Assets.h"
#include <GSmusic.h>
#include <GSstandard_shader.h> 
//ゲームクリア文字位置
const  GSvector2 UIposition_GameClear{ 400.0f,100.0f };
//ゲームオーバー文字位置
const GSvector2 UIposition_GameOver{ 400.0f,100.0f };
//キャラクターセレクト文字
const GSvector2 UIposition_CharacterSelect{ 370.0f,300.0f };
//リトライ文字位置
const GSvector2 UIposition_RetryMoveButton{ 570.0f,300.0f };
//タイトルシーン移行文字位置
const GSvector2 UIposition_TitleMoveButton{ 570.0f,450.0f };
//スモーク位置
const  GSvector2 UIposition_Smoke{ 0.0f,0.0f };
//スモークカラー
const GScolor4 UIcolor_Smoke{ 1.0f,1.0f,1.0f,0.4f };
//クエストの位置
const GSvector2 UIposition_Quest{ 1280.0f / 2.0f, 720.0f / 2.0f };
//クエストの中央
const GSvector2 UIcenter_Quest{ 720.0f / 2,520.0f / 2 };
//選択されていないボタン
const GScolor4 UIcolor_Notselect{ 1.0f,1.0f,1.0f,0.6f };
void GamePlayScene::start() {
	is_end_ = false;
	//ゲームプレイシーンの初期化
	game_start_ = false;
	//スケール
	quest_scale_ = 2.0f;
	//ローテーション
	quest_lotate_ = 800.0f;
	//ゲームスタートタイマー
	game_start_timer_ = 200.0f;
	//ボタンが押されたか？
	push_button_ = false;
	//ステージタイマー
	next_stage_time_ = 60.0f;
	//一度だけ呼び出す用フラグ
	only_one_ = false;
	//BGMをとめるか
	bgm_stop_ = false;
	// 視錐台カリングを有効にする
	gsEnable(GS_FRUSTUM_CULLING);
	// デフォルトシェーダーの初期化（メッシュファイルを読み込む前に有効にする）
	gsInitDefaultShader();
	//キャラクターメッシュ読み込み
	//ナイトメッシュ読み込み
	gsLoadMesh(Mesh_Knight, "Assets/Character/Knight/Knight.msh");
	gsLoadSkeleton(Mesh_Knight, "Assets/Character/Knight/Knight.skl");
	gsLoadAnimation(Mesh_Knight, "Assets/Character/Knight/Knight.anm");
	//ファイターメッシュ
	gsLoadSkinMesh(Mesh_Fighter, "Assets/Character/Fighter/Fighter.msh");
	gsLoadSkeleton(Mesh_Fighter, "Assets/Character/Fighter/Fighter.skl");
	gsLoadAnimation(Mesh_Fighter, "Assets/Character/Fighter/Fighter.anm");
	//レンジャーメッシュ
	gsLoadSkinMesh(Mesh_Ranger, "Assets/Character/Ranger/Ranger.msh");
	gsLoadSkeleton(Mesh_Ranger, "Assets/Character/Ranger/Ranger.skl");
	gsLoadAnimation(Mesh_Ranger, "Assets/Character/Ranger/Ranger.anm");
	//エネミーメッシュ読み込み
	//スケルトンメッシュ
	gsLoadMesh(Mesh_Skeleton, "Assets/Enemy/Skeleton/Skeleton.msh");
	gsLoadSkeleton(Mesh_Skeleton, "Assets/Enemy/Skeleton/Skeleton.skl");
	gsLoadAnimation(Mesh_Skeleton, "Assets/Enemy/Skeleton/Skeleton.anm");
	//ドラゴンメッシュ
	gsLoadSkinMesh(Mesh_Doragon, "Assets/Enemy/Doragon/Doragon.msh");
	gsLoadSkeleton(Mesh_Doragon, "Assets/Enemy/Doragon/Doragon.skl");
	gsLoadAnimation(Mesh_Doragon, "Assets/Enemy/Doragon/Doragon.anm");
	//魔法使いメッシュ
	gsLoadSkinMesh(Mesh_Mage, "Assets/Enemy/Mage/Mage.msh");
	gsLoadSkeleton(Mesh_Mage, "Assets/Enemy/Mage/Mage.skl");
	gsLoadAnimation(Mesh_Mage, "Assets/Enemy/Mage/Mage.anm");
	//ゴーレムメッシュ
	gsLoadSkinMesh(Mesh_Golem, "Assets/Enemy/Golem/Golem.msh");
	gsLoadSkeleton(Mesh_Golem, "Assets/Enemy/Golem/Golem.skl");
	gsLoadAnimation(Mesh_Golem, "Assets/Enemy/Golem/Golem.anm");
	//オークメッシュ
	gsLoadSkinMesh(Mesh_Orc, "Assets/Enemy/Orc/Orc.msh");
	gsLoadSkeleton(Mesh_Orc, "Assets/Enemy/Orc/Orc.skl");
	gsLoadAnimation(Mesh_Orc, "Assets/Enemy/Orc/Orc.anm");
	//弓矢メッシュ
	gsLoadMesh(Mesh_Arrow, "Assets/Weapon/Arrow.mshb");
	//スカイボックス読み込み
	gsLoadMesh(Mesh_Skybox, "Assets/Skybox/skydome.msh");
	//オクツリ―読み込み
	gsLoadOctree(Octree_Stage, "Assets/Octree/stage.oct");
	gsLoadOctree(Octree_Collider, "Assets/Octree/stage_collider.oct");
	//キャラクターナンバーによってプレイヤー追加
	//０ならナイト、１ならファイター、２ならレンジャー
	if (Common_Number::CharacterNum == 0)
		world_.add_actor(new Knight{ &world_, GSvector3{ -90.0f, -2.0f, -30.0f } });
	else if (Common_Number::CharacterNum == 1)
		world_.add_actor(new Fighter{ &world_, GSvector3{ -90.0f, -2.0f, -30.0f } });
	else
		world_.add_actor(new Ranger{ &world_, GSvector3{ -90.0f, -2.0f, -30.0f } });
	//エネミー追加
	//ゴーレム生成
	world_.add_actor(new Enemy_Golem{ &world_, GSvector3{ -90.0f, -1.0f, 60.0f  },90.0f });
	//オーク生成
	world_.add_actor(new Enemy_Orc{ &world_, GSvector3{ -25.0f, 0.0f, 25.0f  },180.0f });
	world_.add_actor(new Enemy_Orc{ &world_, GSvector3{ -20.0f, 0.0f, 25.0f  },180.0f });
	world_.add_actor(new Enemy_Orc{ &world_, GSvector3{ -15.0f, 0.0f, 25.0f  },180.0f });
	//魔法使い生成
	world_.add_actor(new Enemy_Mage{ &world_, GSvector3{ -18.0f, 0.0f, 35.0f  },180.0f });
	world_.add_actor(new Enemy_Mage{ &world_, GSvector3{ -13.0f, 0.0f, 35.0f  },180.0f });
	//ドラゴン生成
	world_.add_actor(new Enemy_Doragon{ &world_, GSvector3{  -45.0f, -2.0f, -21.0f },-110.0f });
	world_.add_actor(new Enemy_Doragon{ &world_, GSvector3{  -45.0f, -2.0f, -12.0f },-110.0f });
	world_.add_actor(new Enemy_Doragon{ &world_, GSvector3{  -45.0f, -2.0f, -30.0f },-110.0f });
	//スケルトン生成
	world_.add_actor(new Enemy_Skeleton{ &world_, GSvector3{ -50.0f, -2.0f, -25.0f  } ,-110.0f });
	world_.add_actor(new Enemy_Skeleton{ &world_, GSvector3{ -50.0f, -2.0f, -20.0f  } ,-110.0f });
	world_.add_actor(new Enemy_Skeleton{ &world_, GSvector3{ -55.0f, -2.0f, -15.0f  } ,-110.0f });
	world_.add_actor(new Enemy_Skeleton{ &world_, GSvector3{ -55.0f, -2.0f, -30.0f  } ,-110.0f });
	world_.add_actor(new Enemy_Skeleton{ &world_, GSvector3{ -60.0f, -2.0f, -10.0f  } ,-110.0f });
	world_.add_actor(new Enemy_Skeleton{ &world_, GSvector3{ -60.0f, -2.0f, -35.0f  } ,-110.0f });
	world_.add_actor(new Enemy_Skeleton{ &world_, GSvector3{ -60.0f, -2.0f, 75.0f  } ,90.0f });
	world_.add_actor(new Enemy_Skeleton{ &world_, GSvector3{ -60.0f, -2.0f, 50.0f  } ,90.0f });
	world_.add_actor(new Enemy_Skeleton{ &world_, GSvector3{ -75.0f, -2.0f, 55.0f  } ,90.0f });
	world_.add_actor(new Enemy_Skeleton{ &world_, GSvector3{ -75.0f, -2.0f, 70.0f  } ,90.0f });
	world_.add_actor(new Enemy_Skeleton{ &world_, GSvector3{ -80.0f, -2.0f, 60.0f  } ,90.0f });
	world_.add_actor(new Enemy_Skeleton{ &world_, GSvector3{ -80.0f, -2.0f, 65.0f  } ,90.0f });
	//見えない壁の追加
	world_.add_actor(new InvisibleWall{ &world_, GSvector3{ -20.0f, 0.0f, 0.0f  },"Doragon" });
	world_.add_actor(new InvisibleWall{ &world_, GSvector3{ -40.0f, 0.0f, 65.0f  },"Mage" });
	//フィールド追加
	world_.add_field(new Field{ Octree_Stage,Octree_Collider,Mesh_Skybox });
	//カメラ追加
	world_.add_camera(new Camera{ &world_ , GSvector3{-0.5f, 0.0f, -0.2f}, GSvector3{0.0f, 0.0f, 0.0f} });
	//ライト追加
	world_.add_light(new Light{ &world_ });
	//SE読み込み
	SE::Load();
	//BGM読み込み
	BGM::Load();
	//BGM再生
	BGM::PlayMusic(BGM_Play);
	//画像読み込み
	//HP文字
	gsLoadTexture(UI_HP_Spel, "Assets/Texture/UI_HPspel.png");
	//ゲームクリア文字
	gsLoadTexture(UI_GameClear_Spel, "Assets/Texture/GameClear.png");
	//ゲームオーバー文字
	gsLoadTexture(UI_GameOver_Spel, "Assets/Texture/GameOver.png");
	//リトライ文字
	gsLoadTexture(UI_Retry_Spel, "Assets/Texture/UI_Retryspel.png");
	//タイトル文字
	gsLoadTexture(UI_Title_Spel, "Assets/Texture/UI_Titlespel.png");
	//プレイヤーHPバー
	gsLoadTexture(UI_Player_HP_Bar, "Assets/Texture/Player_HP.png");
	//エネミーHPバー
	gsLoadTexture(UI_Enemy_HP_Bar, "Assets/Texture/Enemy_HP.png");
	//エネミー名前
	gsLoadTexture(UI_Enemy_Name, "Assets/Texture/GolemName.png");
	//ゲームオーバー時スモーク
	gsLoadTexture(GameOver_Smoke, "Assets/Texture/DeadSmoke.png");
	//クエスト紙
	gsLoadTexture(Quest_Paper, "Assets/Texture/QuestPaper.png");
	//キャラセレクト文字
	gsLoadTexture(Select_CharacterSelect, "Assets/Texture/CharacterSelect.png");
	// シャドウマップの作成
	static const GSuint shadow_map_size[] = { 2048, 2048 };
	gsCreateShadowMap(2, shadow_map_size, GS_TRUE);
	// シャドウマップを適用する距離(視点からの距離）
	gsSetShadowMapDistance(60.0f);
	// カスケードシャドウマップの分割位置を調整（デフォルトは0.5）
	gsSetShdowMapCascadeLamda(0.7f);
	// シャドウの濃さを設定(0.0:濃い～1.0:薄い)
	gsSetShadowMapAttenuation(0.0f);
	// ライトマップの読み込み
	gsLoadLightmap(0, "Assets/Lightmap/Lightmap.txt");
	// リフレクションプローブの読み込み
	gsLoadReflectionProbe(0, "Assets/RefProbe/ReflectionProbe.txt");
	//ゲームクリア判定初期化
	Common_Number::is_game_clear_ = false;
	//ゲームオーバー判定の初期化
	Common_Number::is_game_over_ = false;
}

void GamePlayScene::update(float delta_time) {
	//ゲームスタートがfalseなら
	if (!game_start_)
	{
		//ゲームスタートタイマーから引いて
		game_start_timer_ -= delta_time;
		if (quest_lotate_ >= 0.0f)
			quest_lotate_ -= delta_time * lotate_speed_;
		//スケールが1倍になるまで引く
		if (quest_scale_ >= 1.0f)
			quest_scale_ -= delta_time / scale_speed_;
		else
		{
			if (!only_one_)
			{
				only_one_ = true;
				SE::PlaySE(SE_QuestStart);
			}
		}
		//ゲームスタートタイマーが０なら
		if (game_start_timer_ <= 0)
			//ゲーム開始
			game_start_ = true;
	}
	else
		world_.update(delta_time);
	//ゲームオーバーがtrueなら
	if (Common_Number::is_game_over_)
	{
		if (!bgm_stop_)
		{
			//BGMをとめる（ゲームプレイ中の)
			gsStopMusic();
			bgm_stop_ = true;
		}
		BGM::PlayMusic(BGM_GameOver);
		//次のシーンに行くための操作
		if (gsGetJoyTrigger(0, GJOY_UP)) {
			SE::PlaySE(SE_SelectMove);
			next_title_ = false;
		}
		if (gsGetJoyTrigger(0, GJOY_DOWN))
		{
			SE::PlaySE(SE_SelectMove);
			next_title_ = true;
		}
		if (gsGetJoyTrigger(0, GJOY_BUTTON_2))
		{
			push_button_ = true;
			SE::PlaySE(SE_Select);
		}
	}
	//ゲームクリア―がtrueなら
	if (Common_Number::is_game_clear_)
	{
		if (!bgm_stop_)
		{
			//BGMをとめる（ゲームプレイ中の)
			gsStopMusic();
			bgm_stop_ = true;
		}
		//次のシーンに行くための操作
		if (gsGetJoyTrigger(0, GJOY_UP))
		{
			SE::PlaySE(SE_SelectMove);
			next_title_ = false;
		}
		if (gsGetJoyTrigger(0, GJOY_DOWN))
		{
			SE::PlaySE(SE_SelectMove);
			next_title_ = true;
		}
		if (gsGetJoyTrigger(0, GJOY_BUTTON_2))
		{
			SE::PlaySE(SE_Select);
			push_button_ = true;
		}
	}
	if (push_button_)
	{
		//タイマーを減少
		next_stage_time_ -= delta_time;
		if (next_stage_time_ <= 0)
			is_end_ = true;     // シーン終了
	}
}
void GamePlayScene::draw()const {
	//ゲームスタートがfalseなら
	if (!game_start_)
	{
		//ゲーム開始時のクエストの演出
		const GSvector2 UIscale_Quest{ quest_scale_,quest_scale_ };
		gsDrawSprite2D(Quest_Paper, &UIposition_Quest, NULL, &UIcenter_Quest, NULL, &UIscale_Quest, quest_lotate_);
	}
	else
	{
		world_.draw();
		//ゲームオーバーがtrueなら
		if (Common_Number::is_game_over_)
		{
			//スモークをかける
			gsDrawSprite2D(GameOver_Smoke, &UIposition_Smoke, NULL, NULL, &UIcolor_Smoke, NULL, 0.0f);
			//ゲームオーバー文字
			gsDrawSprite2D(UI_GameOver_Spel, &UIposition_GameOver, NULL, NULL, NULL, NULL, 0.0f);
			//選択されていないボタンのα値を下げる
			if (next_title_)
				gsDrawSprite2D(UI_Retry_Spel, &UIposition_RetryMoveButton, NULL, NULL, &UIcolor_Notselect, NULL, 0.0f);
			else gsDrawSprite2D(UI_Retry_Spel, &UIposition_RetryMoveButton, NULL, NULL, NULL, NULL, 0.0f);
			if (!next_title_)
				gsDrawSprite2D(UI_Title_Spel, &UIposition_TitleMoveButton, NULL, NULL, &UIcolor_Notselect, NULL, 0.0f);
			else gsDrawSprite2D(UI_Title_Spel, &UIposition_TitleMoveButton, NULL, NULL, NULL, NULL, 0.0f);
		}
		//ゲームクリアがtrueなら
		if (Common_Number::is_game_clear_)
		{
			gsDrawSprite2D(UI_GameClear_Spel, &UIposition_GameClear, NULL, NULL, NULL, NULL, 0.0f);
			//選択されていないボタンのα値を下げる
			if (next_title_)
				gsDrawSprite2D(Select_CharacterSelect, &UIposition_CharacterSelect, NULL, NULL, &UIcolor_Notselect, NULL, 0.0f);
			else gsDrawSprite2D(Select_CharacterSelect, &UIposition_CharacterSelect, NULL, NULL, NULL, NULL, 0.0f);
			if (!next_title_)
				gsDrawSprite2D(UI_Title_Spel, &UIposition_TitleMoveButton, NULL, NULL, &UIcolor_Notselect, NULL, 0.0f);
			else gsDrawSprite2D(UI_Title_Spel, &UIposition_TitleMoveButton, NULL, NULL, NULL, NULL, 0.0f);
		}
	}
}
bool GamePlayScene::is_end()const {
	return is_end_;
}
std::string GamePlayScene::next()const {
	//ゲームクリアがtrueなら
	if (Common_Number::is_game_clear_)
	{
		//ネクストタイトルがfalseならキャラクターセレクト、trueならタイトル
		if (!next_title_)return "CharacterSelect";
		else return "TitleScene";
	}
	//ゲームオーバーがtrueなら
	if (Common_Number::is_game_over_)
	{
		//ネクストタイトルがfalseならゲームプレイ、trueならタイトル
		if (!next_title_)return "GamePlayScene";
		else return "TitleScene";
	}
}
void GamePlayScene::end() {
	//ワールド削除
	world_.clear();
	//SE削除
	SE::DeleteSE();
	//BGM削除
	BGM::DeleteMusic();
	//アセット削除
	//ナイトメッシュデータ
	gsDeleteMesh(Mesh_Knight);
	gsDeleteSkeleton(Mesh_Knight);
	gsDeleteAnimation(Mesh_Knight);
	//レンジャーメッシュデータ
	gsDeleteMesh(Mesh_Ranger);
	gsDeleteSkeleton(Mesh_Ranger);
	gsDeleteAnimation(Mesh_Ranger);
	//ファイターメッシュデータ
	gsDeleteMesh(Mesh_Fighter);
	gsDeleteSkeleton(Mesh_Fighter);
	gsDeleteAnimation(Mesh_Fighter);
	//ドラゴンメッシュデータ
	gsDeleteMesh(Mesh_Doragon);
	gsDeleteSkeleton(Mesh_Doragon);
	gsDeleteAnimation(Mesh_Doragon);
	//スケルトンメッシュデータ
	gsDeleteMesh(Mesh_Skeleton);
	gsDeleteSkeleton(Mesh_Skeleton);
	gsDeleteAnimation(Mesh_Skeleton);
	//魔法使いメッシュデータ
	gsDeleteMesh(Mesh_Mage);
	gsDeleteSkeleton(Mesh_Mage);
	gsDeleteAnimation(Mesh_Mage);
	//オークメッシュデータ
	gsDeleteMesh(Mesh_Orc);
	gsDeleteSkeleton(Mesh_Orc);
	gsDeleteAnimation(Mesh_Orc);
	//ゴーレムメッシュデータ
	gsDeleteMesh(Mesh_Golem);
	gsDeleteSkeleton(Mesh_Golem);
	gsDeleteAnimation(Mesh_Golem);
	//スカイメッシュデータ
	gsDeleteMesh(Mesh_Skybox);
	//オクトリー
	gsDeleteOctree(Octree_Stage);
	gsDeleteOctree(Octree_Collider);
	//画像削除
	//HP文字
	gsDeleteTexture(UI_HP_Spel);
	//ゲームクリア文字
	gsDeleteTexture(UI_GameClear_Spel);
	//ゲームオーバー文字
	gsDeleteTexture(UI_GameOver_Spel);
	//リトライ文字
	gsDeleteTexture(UI_Retry_Spel);
	//タイトル文字
	gsDeleteTexture(UI_Title_Spel);
	//プレイヤーHPバー
	gsDeleteTexture(UI_Player_HP_Bar);
	//ゲームオーバー時スモーク
	gsDeleteTexture(GameOver_Smoke);
	//クエスト紙
	gsDeleteTexture(Quest_Paper);
	//エネミーHP
	gsDeleteTexture(UI_Enemy_HP_Bar);
	//エネミー名前
	gsDeleteTexture(UI_Enemy_Name);
}