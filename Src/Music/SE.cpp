#include "SE.h"
#include "Assets.h"
#include <gslib.h>

//SEロード
void SE::Load() {
    //セレクト音
    gsLoadSE(SE_Select, "Assets/SE/Select.wav", 1, GWAVE_DEFAULT);
    //セレクト変更音
    gsLoadSE(SE_SelectMove, "Assets/SE/CharaSelectChange.wav", 1, GWAVE_DEFAULT);
    //クエストスタート音
    gsLoadSE(SE_QuestStart, "Assets/SE/QuestStart.wav", 1, GWAVE_DEFAULT);
    //ドラゴン用SE
    gsLoadSE(SE_Enemy_Doragon_Down, "Assets/SE/Doragon_Down.wav", 1, GWAVE_DEFAULT);
    gsLoadSE(SE_Enemy_Doragon_Damage, "Assets/SE/Doragon_Damage.wav", 1, GWAVE_DEFAULT);
    //ゴーレム用SE
    gsLoadSE(SE_Enemy_Golem_Down, "Assets/SE/Golem_Down.wav", 1, GWAVE_DEFAULT);
    gsLoadSE(SE_Enemy_Golem_Damage, "Assets/SE/Golem_Damage.wav", 1, GWAVE_DEFAULT);
    gsLoadSE(SE_PunchHit_Golem, "Assets/SE/Golem_GetHit_Punch.wav", 1, GWAVE_DEFAULT);
    gsLoadSE(SE_ArrowHit_Golem, "Assets/SE/Golem_GetHit_Arrow.wav", 1, GWAVE_DEFAULT);
    gsLoadSE(SE_SwordHit_Golem, "Assets/SE/Golem_GetHit_Sword.wav", 1, GWAVE_DEFAULT);
    //スケルトン用SE
    gsLoadSE(SE_Enemy_Skeleton_Down, "Assets/SE/Skeleton_Down.wav", 1, GWAVE_DEFAULT);
    gsLoadSE(SE_Enemy_Skeleton_Damage, "Assets/SE/Skeleton_Damage.wav", 1, GWAVE_DEFAULT);
    //魔法使い用SE
    gsLoadSE(SE_Enemy_Mage_Down, "Assets/SE/Mage_Down.wav", 1, GWAVE_DEFAULT);
    gsLoadSE(SE_Enemy_Mage_Damage, "Assets/SE/Mage_Damage.wav", 1, GWAVE_DEFAULT);
    //オーク用SE
    gsLoadSE(SE_Enemy_Orc_Down, "Assets/SE/Orc_Damage.wav", 1, GWAVE_DEFAULT);
    gsLoadSE(SE_Enemy_Orc_Damage, "Assets/SE/Orc_Damage.wav", 1, GWAVE_DEFAULT);
    //ナイト用SE
    gsLoadSE(SE_Knight_Attack1, "Assets/SE/Knight_Attack1.wav", 1, GWAVE_DEFAULT);
    gsLoadSE(SE_Knight_Attack2, "Assets/SE/Knight_Attack2.wav", 1, GWAVE_DEFAULT);
    gsLoadSE(SE_Knight_Attack3, "Assets/SE/Knight_Attack3.wav", 1, GWAVE_DEFAULT);
    gsLoadSE(SE_Knight_Damage, "Assets/SE/Knight_Damage.wav", 1, GWAVE_DEFAULT);
    gsLoadSE(SE_Knight_Down, "Assets/SE/Knight_Down.wav", 1, GWAVE_DEFAULT);
    //レンジャー用SE
    gsLoadSE(SE_Ranger_Attack1, "Assets/SE/Ranger_Attack1.wav", 1, GWAVE_DEFAULT);
    gsLoadSE(SE_Ranger_Attack2, "Assets/SE/Ranger_Attack2.wav", 1, GWAVE_DEFAULT);
    gsLoadSE(SE_Ranger_Attack3, "Assets/SE/Ranger_Attack3.wav", 1, GWAVE_DEFAULT);
    gsLoadSE(SE_Ranger_Damage, "Assets/SE/Ranger_Damage.wav", 1, GWAVE_DEFAULT);
    gsLoadSE(SE_Ranger_Down, "Assets/SE/Ranger_Down.wav", 1, GWAVE_DEFAULT);
    //ファイター用SE
    gsLoadSE(SE_Fighter_Attack1, "Assets/SE/Fighter_Attack1.wav", 1, GWAVE_DEFAULT);
    gsLoadSE(SE_Fighter_Attack2, "Assets/SE/Fighter_Attack1.wav", 1, GWAVE_DEFAULT);
    gsLoadSE(SE_Fighter_Attack3, "Assets/SE/Fighter_Attack1.wav", 1, GWAVE_DEFAULT);
    gsLoadSE(SE_Fighter_Damage, "Assets/SE/Fighter_Damage.wav", 1, GWAVE_DEFAULT);
    gsLoadSE(SE_Fighter_Down, "Assets/SE/Fighter_Down.wav", 1, GWAVE_DEFAULT);
    //エネミーに対する攻撃ヒット音
    gsLoadSE(SE_PunchHit, "Assets/SE/PunchHit.wav", 1, GWAVE_DEFAULT);
    gsLoadSE(SE_ArrowHit, "Assets/SE/AllowHit.wav", 1, GWAVE_DEFAULT);
    gsLoadSE(SE_SwordHit, "Assets/SE/SwordHit.wav", 1, GWAVE_DEFAULT);
    //見えない壁解除音
    gsLoadSE(SE_InvisibleOff, "Assets/SE/InvisibleOff.wav", 1, GWAVE_DEFAULT);
    //クリアしたときに出す音
    gsLoadSE(SE_GameClear, "Assets/SE/SE_Clear.wav", 1, GWAVE_DEFAULT);
}

//SE再生
void SE::PlaySE(int num) {
    gsPlaySE(num);
}

//SE削除
void SE::DeleteSE() {
    //セレクトボタン
    gsDeleteSE(SE_Select);
    //クエストスタート音
    gsDeleteSE(SE_QuestStart);
    //セレクトボタン変更音
    gsDeleteSE(SE_SelectMove);
    //パンチヒット音
    gsDeleteSE(SE_PunchHit);
    //アローヒット音
    gsDeleteSE(SE_ArrowHit);
    //ソードヒット音
    gsDeleteSE(SE_SwordHit);
    //ドラゴン死亡
    gsDeleteSE(SE_Enemy_Doragon_Down);
    //ドラゴンダメージ
    gsDeleteSE(SE_Enemy_Doragon_Damage);
    //ゴーレム死亡
    gsDeleteSE(SE_Enemy_Golem_Down);
    //ゴーレムダメージ
    gsDeleteSE(SE_Enemy_Golem_Damage);
    //スケルトン死亡
    gsDeleteSE(SE_Enemy_Skeleton_Down);
    //スケルトンダメージ
    gsDeleteSE(SE_Enemy_Skeleton_Damage);
    //魔法使い死亡
    gsDeleteSE(SE_Enemy_Mage_Down);
    //魔法使いダメージ
    gsDeleteSE(SE_Enemy_Mage_Damage);
    //オーク死亡
    gsDeleteSE(SE_Enemy_Orc_Down);
    //オークダメージ
    gsDeleteSE(SE_Enemy_Orc_Damage);
    //ナイト攻撃音
    gsDeleteSE(SE_Knight_Attack1);
    gsDeleteSE(SE_Knight_Attack2);
    gsDeleteSE(SE_Knight_Attack3);
    //ナイトダメージ音
    gsDeleteSE(SE_Knight_Damage);
    //ナイト死亡音
    gsDeleteSE(SE_Knight_Down);
    //レンジャー攻撃音
    gsDeleteSE(SE_Ranger_Attack1);
    gsDeleteSE(SE_Ranger_Attack2);
    gsDeleteSE(SE_Ranger_Attack3);
    //レンジャーダメージ音
    gsDeleteSE(SE_Ranger_Damage);
    //レンジャー死亡音
    gsDeleteSE(SE_Ranger_Down);
    //ファイター攻撃音
    gsDeleteSE(SE_Fighter_Attack1);
    gsDeleteSE(SE_Fighter_Attack2);
    gsDeleteSE(SE_Fighter_Attack3);
    //ファイターダメージ音
    gsDeleteSE(SE_Fighter_Damage);
    //ファイター死亡音
    gsDeleteSE(SE_Fighter_Down);
}