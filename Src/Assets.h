#ifndef ASSETS_H_
#define ASSETS_H_
//メッシュ
enum {
	Mesh_Knight,        //プレイヤー
	Mesh_Fighter,       //ファイター
	Mesh_Ranger,        //レンジャー
	Mesh_Skeleton,      //スケルトン
	Mesh_Doragon,       //ドラゴン
	Mesh_Mage,	        //魔法使い
	Mesh_Orc,	        //オーク
	Mesh_Golem,         //ゴーレム
	Mesh_Skybox,        //スカイボックス
	Mesh_Arrow,         //弓矢
};
//ステージ
enum {
	Octree_Stage,       //ステージメッシュ
	Octree_Collider     //ステージコライダー
};
//画像
enum
{
	BackGround,               	 //背景
	Title_BackGround,			 //タイトル文字付背景
	Title_PushtoStart,			 //タイトル繊維文字
	Select_CharacterSelect,		 //キャラクターセレクト文字
	Select_Knight,				 //ナイトの画像
	Select_Fighter,				 //ファイターの画像
	Select_Ranger,				 //レンジャーの画像
	Name_Knight,				 //ナイトの名前文字
	Name_Fighter,				 //ファイターの名前文字
	Name_Ranger,				 //レンジャーの名前文字
	Win_Star,                    //勝利したキャラクターに星印をつける
	Select_Frame,				 //キャラクターセレクトフレーム
	UI_HP_Spel,					 //HP文字
	UI_GameClear_Spel,			 //クリア文字
	UI_GameOver_Spel,			 //ゲームオーバー文字
	UI_Retry_Spel,				 //リトライ文字
	UI_Title_Spel,				 //タイトル文字
	UI_Player_HP_Frame,			 //プレイヤーHPフレーム
	UI_Player_HP_Bar,			 //プレイヤーHP
	UI_Enemy_HP_Bar,			 //エネミーのHP
	UI_Enemy_Name,  			 //エネミーの名前文字
	GameOver_Smoke,				 //ゲームオーバー時のスモーク
	Quest_Paper,				 //クエストの紙画像
};
//SE
enum {
	SE_Select,					  //セレクト音
	SE_SelectMove,			      //セレクト変更音
	SE_QuestStart,                //クエストスタート音
	SE_GameClear,                 //ゲームクリア音
	SE_PunchHit,				  //パンチヒット音
	SE_ArrowHit,                  //アローヒット音
	SE_SwordHit,                  //ソードヒット音
	SE_InvisibleOff,              //見えない壁が解除された時の音
	SE_Enemy_Doragon_Down,		  //ドラゴン死亡
	SE_Enemy_Doragon_Damage,	  //ドラゴンダメージ
	SE_Enemy_Golem_Down,		  //ゴーレム死亡
	SE_Enemy_Golem_Damage,  	  //ゴーレムダメージ
	SE_PunchHit_Golem,            //ゴーレムパンチヒット音
	SE_ArrowHit_Golem,			  //ゴーレムアローヒット音
	SE_SwordHit_Golem,			  //ゴーレムソードヒット音
	SE_Enemy_Skeleton_Down,		  //スケルトン死亡
	SE_Enemy_Skeleton_Damage,	  //スケルトンダメージ
	SE_Enemy_Mage_Down,			  //魔法使い死亡
	SE_Enemy_Mage_Damage,		  //魔法使いダメージ
	SE_Enemy_Orc_Down,			  //オーク死亡
	SE_Enemy_Orc_Damage,		  //オークダメージ
	SE_Knight_Attack1,            //ナイト攻撃１
	SE_Knight_Attack2,			  //ナイト攻撃２
	SE_Knight_Attack3,			  //ナイト攻撃３
	SE_Knight_Damage,			  //ナイトダメージ
	SE_Knight_Down,				  //ナイト死亡
	SE_Ranger_Attack1,			  //レンジャー攻撃１
	SE_Ranger_Attack2,			  //レンジャー攻撃２
	SE_Ranger_Attack3,			  //レンジャー攻撃３
	SE_Ranger_Damage,			  //レンジャーダメージ
	SE_Ranger_Down,				  //レンジャー死亡
	SE_Fighter_Attack1,			  //ファイタ―攻撃１
	SE_Fighter_Attack2,			  //ファイタ―攻撃２
	SE_Fighter_Attack3,			  //ファイタ―攻撃３
	SE_Fighter_Damage,			  //ファイタ―ダメージ
	SE_Fighter_Down,			  //ファイタ―死亡
};
//BGM
enum {
	BGM_Title,                    //タイトルBGM
	BGM_Play,                     //ゲームプレイBGM
	BGM_GameOver,                 //ゲームオーバーBGM
	BGM_CharaSelect,              //キャラセレクトBGM
};
#endif