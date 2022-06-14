#include"TitleScene.h"
#include"Assets.h"
#include"Music/BGM.h"
#include"Music/SE.h"
#include"Common_Number.h"
//�w�i�ʒu
const  GSvector2 UIposition_BackGround{ 0.0f,0.0f };
//�{�^���ʒu
const  GSvector2 UIposition_PushtoStart{ 460.0f,520.0f };
void TitleScene::start() {
	//�摜�ǂݍ���
	gsLoadTexture(Title_BackGround, "Assets/Texture/TitleBackGround.png");
	gsLoadTexture(Title_PushtoStart, "Assets/Texture/PushtoStart.png");
	//SE�ǂݍ���
	SE::Load();
	//BGM�ǂݍ���
	BGM::Load();
	//BGM�Đ�
	BGM::PlayMusic(BGM_Title);
	//�I���t���O������
	is_end_ = false;
	//�{�^���t���O������
	push_button_ = false;
	//�{�^���_�ŊԊu������
	button_count_distance_ = 30.0f;
	//�X�e�[�W�^�C�}�[������
	next_stage_time_ = 60.0f;
	//�Q�[���N���A���菉����
	Common_Number::is_game_clear_ = false;
	//�Q�[���I�[�o�[����̏�����
	Common_Number::is_game_over_ = false;
}
void TitleScene::update(float delta_time) {
	if (push_button_)
	{
		next_stage_time_ -= delta_time;
		if (next_stage_time_ <= 0)
			is_end_ = true;     // �V�[���I��
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

//�`��
void TitleScene::draw()const {
	// �w�i�̕`��
	gsDrawSprite2D(Title_BackGround, &UIposition_BackGround, NULL, NULL, NULL, NULL, 0.0f);
	if (look_button_)gsDrawSprite2D(Title_PushtoStart, &UIposition_PushtoStart, NULL, NULL, NULL, NULL, 0.0f);
}

//�I���t���O
bool TitleScene::is_end()const {
	return is_end_;
}

//���̃V�[��
std::string TitleScene::next()const {
	return"CharacterSelect";
}

//�I��
void TitleScene::end()
{
	//�A�Z�b�g�폜
	//�w�i�摜
	gsDeleteTexture(Title_BackGround);
	//�^�C�g���{�^��
	gsDeleteTexture(Title_PushtoStart);
	//SE�폜
	SE::DeleteSE();
	//BGM�폜
	BGM::DeleteMusic();
}