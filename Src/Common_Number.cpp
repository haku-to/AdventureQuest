#include "Common_Number.h"
//�L�����N�^�[�ԍ�
int Common_Number::CharacterNum = 0;
//�L�����N�^�[�l�[���i�[
const std::string Common_Number::CharaName[3] = { "Knight",
                                                  "Fighter",
                                                  "Ranger" };
//�Q�[���N���A��
bool Common_Number::is_game_clear_ = false;
//�Q�[���I�[�o�[��
bool Common_Number::is_game_over_ = false;
//�i�C�g����������
bool Common_Number::is_knight_win_ = false;
//�t�@�C�^�[����������
bool Common_Number::is_fighter_win_ = false;
//�����W���[����������
bool Common_Number::is_ranger_win_ = false;