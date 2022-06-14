#ifndef COMMON_NUMBER_H_
#define COMMON_NUMBER_H_
#include <string>
//共通クラス
class Common_Number {
public:
	//キャラクター番号
	static int CharacterNum;

	//キャラクターネーム格納
	static const std::string CharaName[3];

	//ゲームクリアか
	static bool is_game_clear_;

	//ゲームオーバーか
	static bool is_game_over_;

	//ナイトが勝ったか
	static bool is_knight_win_;

	//ファイターが勝ったか
	static bool is_fighter_win_;

	//レンジャーが勝ったか
	static bool is_ranger_win_;
};
#endif