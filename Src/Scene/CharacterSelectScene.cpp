#include"CharacterSelectScene.h"
#include"Common_Number.h"
#include"Assets.h"
#include"Music/SE.h"
#include"Music/BGM.h"
//�L�����N�^�[�Z���N�g����
const GSvector2 UIposition_CharacterSelect{ 370.0f,50.0f };
//�w�i�ʒu
const  GSvector2 UIposition_BackGround{ 0.0f,0.0f };
//�Z���N�g�t���[��
const  GSvector2 TexCenter_SelectFrame{ 155.0f,205.0f };
//�L�����N�^�[�摜�|�W�V����
const GSvector2 Texposisition_Knight{ 100.0f,200.0f };
const GSvector2 Texposisition_Fighter{ 500.0f,200.0f };
const GSvector2 Texposisition_Ranger{ 900.0f,200.0f };
//�L�����N�^�[���O�|�W�V����
const GSvector2 Texposisition_Knight_Name{ 190.0f,650.0f };
const GSvector2 Texposisition_Fighter_Name{ 580.0f,650.0f };
const GSvector2 Texposisition_Ranger_Name{ 970.0f,650.0f };
//�e�L�����N�^�[�������̐��ʒu
const GSvector2 WinStar_Position_Knight{ 100.0f,200.0f };
const GSvector2 WinStar_Position_Fighter{ 500.0f,200.0f };
const GSvector2 WinStar_Position_Ranger{ 900.0f,200.0f };

//�J�n
void CharacterSelectScene::start() {
	//�摜�ǂݍ���
	//�w�i�摜
	gsLoadTexture(BackGround, "Assets/Texture/BackGround.png");
	//�Z���N�g�t���[���摜
	gsLoadTexture(Select_Frame, "Assets/Texture/CharacterSelectFrame.png");
	//�L�����N�^�[�摜
	//�i�C�g�摜
	gsLoadTexture(Select_Knight, "Assets/Texture/KnightSelect.png");
	//�t�@�C�^�[�摜
	gsLoadTexture(Select_Fighter, "Assets/Texture/FighterSelect.png");
	//�����W���[�摜
	gsLoadTexture(Select_Ranger, "Assets/Texture/RangerSelect.png");
	//�L�����N�^�[���O
	//�i�C�g���O
	gsLoadTexture(Name_Knight, "Assets/Texture/Name_Knight.png");
	//�t�@�C�^�[���O
	gsLoadTexture(Name_Fighter, "Assets/Texture/Name_Fighter.png");
	//�����W���[���O
	gsLoadTexture(Name_Ranger, "Assets/Texture/Name_Ranger.png");
	//�L�����N�^�[�Z���N�g����
	gsLoadTexture(Select_CharacterSelect, "Assets/Texture/CharacterSelect.png");
	//���摜
	gsLoadTexture(Win_Star, "Assets/Texture/WinStar.png");
	//SE�ǂݍ���
	SE::Load();
	//BGM�ǂݍ���
	BGM::Load();
	//BGM���Đ�����
	BGM::PlayMusic(BGM_CharaSelect);
	//�I���t���O������
	is_end_ = false;
	//�{�^���t���O������
	push_button_ = false;
	//�^�C�}�[������
	next_stage_time_ = 60.0f;
}

//�X�V
void CharacterSelectScene::update(float delta_time) {
	//�{�^���t���O��true�Ȃ�
	if (push_button_)
	{
		//�Z���N�g�t���[���̊g�嗦���P�ɂ���
		select_frame_scale_ = 1.0f;
		//�^�C�}�[�J�n
		next_stage_time_ -= delta_time;
		if (next_stage_time_ <= 0)
			// �V�[���I��
			is_end_ = true;
	}
	else
	{
		//B�{�^���������ꂽ��
		if (gsGetJoyTrigger(0, GJOY_BUTTON_2)) {
			//�Z���N�g���Đ�
			SE::PlaySE(SE_Select);
			//�{�^���t���O��true�ɂ���
			push_button_ = true;
		}
	}
	//�{�^����������Ă��Ȃ��ăW���C�X�e�B�b�N�̍����I�����ꂽ��
	if (gsGetJoyTrigger(0, GJOY_LEFT) && !push_button_)
	{
		//�L�����N�^�[�̐��ɂ����
		if (Common_Number::CharacterNum > 0)
		{
			//�Z���N�g�ύX�����o��
			SE::PlaySE(SE_SelectMove);
			//�L�����N�^�[�i���o�[��ς���
			Common_Number::CharacterNum--;
			//�t���[���|�W�V������ς���
			select_frame_pos_ -= select_frame_movement_;
			//�X�P�[�����P�ɏ���������
			select_frame_scale_ = 1.0f;
		}
	}
	//�{�^����������Ă��Ȃ��ăW���C�X�e�B�b�N�̉E���I�����ꂽ��
	if (gsGetJoyTrigger(0, GJOY_RIGHT) && !push_button_)
	{
		//�L�����N�^�[�̐��ɂ���ă|�W�V������ς���
		if (Common_Number::CharacterNum < 2)
		{
			//�Z���N�g�ύX�����o��
			SE::PlaySE(SE_SelectMove);
			//�L�����N�^�[�i���o�[��ς���
			Common_Number::CharacterNum++;
			//�t���[���|�W�V������ς���
			select_frame_pos_ += select_frame_movement_;
			//�X�P�[�����P�ɏ���������
			select_frame_scale_ = 1.0f;
		}
	}
	//�{�^���t���O��false���t���[���̊g��ʂ����ʂ𒴂�����
	if (!push_button_ && select_frame_scale_ <= 1.2f)
	{
		//�f���^�^�C���ɂ�
		select_frame_scale_ += delta_time * select_frame_diameter_;
	}
	else
		//true�ɂȂ�����
		select_frame_scale_ = 1.0f;

}

//�`��
void CharacterSelectScene::draw()const {
	//�{�^���ʒu
	const  GSvector2 TexPosition_Frame{ select_frame_pos_,400.0f };
	const  GSvector2 TexScale_Frame{ select_frame_scale_,select_frame_scale_ };
	//�摜�`��
	// �w�i
	gsDrawSprite2D(BackGround, &UIposition_BackGround, NULL, NULL, NULL, NULL, 0.0f);
	//�Z���N�g�t���[��
	gsDrawSprite2D(Select_Frame, &TexPosition_Frame, NULL, &TexCenter_SelectFrame, NULL, &TexScale_Frame, 0.0f);
	//�i�C�g�摜
	gsDrawSprite2D(Select_Knight, &Texposisition_Knight, NULL, NULL, NULL, NULL, 0.0f);
	//�t�@�C�^�[�摜
	gsDrawSprite2D(Select_Fighter, &Texposisition_Fighter, NULL, NULL, NULL, NULL, 0.0f);
	//�����W���[�摜
	gsDrawSprite2D(Select_Ranger, &Texposisition_Ranger, NULL, NULL, NULL, NULL, 0.0f);
	//�i�C�g���O
	gsDrawSprite2D(Name_Knight, &Texposisition_Knight_Name, NULL, NULL, NULL, NULL, 0.0f);
	//�t�@�C�^�[�摜
	gsDrawSprite2D(Name_Fighter, &Texposisition_Fighter_Name, NULL, NULL, NULL, NULL, 0.0f);
	//�����W���[�摜
	gsDrawSprite2D(Name_Ranger, &Texposisition_Ranger_Name, NULL, NULL, NULL, NULL, 0.0f);
	//�L�����N�^�[�Z���N�g����
	gsDrawSprite2D(Select_CharacterSelect, &UIposition_CharacterSelect, NULL, NULL, NULL, NULL, 0.0f);
	//�i�C�g��
	if(Common_Number::is_knight_win_)
	gsDrawSprite2D(Win_Star, &WinStar_Position_Knight, NULL, NULL, NULL, NULL, 0.0f);
	//�t�@�C�^�[�� 
	if (Common_Number::is_fighter_win_)
	gsDrawSprite2D(Win_Star, &WinStar_Position_Fighter, NULL, NULL, NULL, NULL, 0.0f);
	//�����W���[�� 
	if (Common_Number::is_ranger_win_)
	gsDrawSprite2D(Win_Star, &WinStar_Position_Ranger, NULL, NULL, NULL, NULL, 0.0f);
}
bool

//�I�����Ă��邩
CharacterSelectScene::is_end()const {
	return is_end_;
}

//���̃V�[���ɕԂ�
std::string CharacterSelectScene::next()const {
	return"GamePlayScene";
}

//�I��
void CharacterSelectScene::end()
{
	//�摜�f�[�^�폜
	//�w�i
	gsDeleteTexture(BackGround);
	//�L�����N�^�[�Z���N�g����
	gsDeleteTexture(Select_CharacterSelect);
	//�i�C�g�摜
	gsDeleteTexture(Select_Knight);
	//�����W���[�摜
	gsDeleteTexture(Select_Ranger);
	//�t�@�C�^�[�摜
	gsDeleteTexture(Select_Fighter);
	//�l�[���摜�폜
	//�i�C�g���O
	gsDeleteTexture(Name_Knight);
	//�����W���[���O
	gsDeleteTexture(Name_Ranger);
	//�t�@�C�^�[���O
	gsDeleteTexture(Name_Fighter);
	//�Z���N�g�t���[��
	gsDeleteTexture(Select_Frame);
	//BGM�폜
	BGM::DeleteMusic();
	//SE�폜
	SE::DeleteSE();
}