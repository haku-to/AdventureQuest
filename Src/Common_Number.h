#ifndef COMMON_NUMBER_H_
#define COMMON_NUMBER_H_
#include <string>
//���ʃN���X
class Common_Number {
public:
	//�L�����N�^�[�ԍ�
	static int CharacterNum;

	//�L�����N�^�[�l�[���i�[
	static const std::string CharaName[3];

	//�Q�[���N���A��
	static bool is_game_clear_;

	//�Q�[���I�[�o�[��
	static bool is_game_over_;

	//�i�C�g����������
	static bool is_knight_win_;

	//�t�@�C�^�[����������
	static bool is_fighter_win_;

	//�����W���[����������
	static bool is_ranger_win_;
};
#endif