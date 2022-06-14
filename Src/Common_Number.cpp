#include "Common_Number.h"
//キャラクター番号
int Common_Number::CharacterNum = 0;
//キャラクターネーム格納
const std::string Common_Number::CharaName[3] = { "Knight",
                                                  "Fighter",
                                                  "Ranger" };
//ゲームクリアか
bool Common_Number::is_game_clear_ = false;
//ゲームオーバーか
bool Common_Number::is_game_over_ = false;
//ナイトが勝ったか
bool Common_Number::is_knight_win_ = false;
//ファイターが勝ったか
bool Common_Number::is_fighter_win_ = false;
//レンジャーが勝ったか
bool Common_Number::is_ranger_win_ = false;