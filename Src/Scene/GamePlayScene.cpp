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
//�Q�[���N���A�����ʒu
const  GSvector2 UIposition_GameClear{ 400.0f,100.0f };
//�Q�[���I�[�o�[�����ʒu
const GSvector2 UIposition_GameOver{ 400.0f,100.0f };
//�L�����N�^�[�Z���N�g����
const GSvector2 UIposition_CharacterSelect{ 370.0f,300.0f };
//���g���C�����ʒu
const GSvector2 UIposition_RetryMoveButton{ 570.0f,300.0f };
//�^�C�g���V�[���ڍs�����ʒu
const GSvector2 UIposition_TitleMoveButton{ 570.0f,450.0f };
//�X���[�N�ʒu
const  GSvector2 UIposition_Smoke{ 0.0f,0.0f };
//�X���[�N�J���[
const GScolor4 UIcolor_Smoke{ 1.0f,1.0f,1.0f,0.4f };
//�N�G�X�g�̈ʒu
const GSvector2 UIposition_Quest{ 1280.0f / 2.0f, 720.0f / 2.0f };
//�N�G�X�g�̒���
const GSvector2 UIcenter_Quest{ 720.0f / 2,520.0f / 2 };
//�I������Ă��Ȃ��{�^��
const GScolor4 UIcolor_Notselect{ 1.0f,1.0f,1.0f,0.6f };
void GamePlayScene::start() {
	is_end_ = false;
	//�Q�[���v���C�V�[���̏�����
	game_start_ = false;
	//�X�P�[��
	quest_scale_ = 2.0f;
	//���[�e�[�V����
	quest_lotate_ = 800.0f;
	//�Q�[���X�^�[�g�^�C�}�[
	game_start_timer_ = 200.0f;
	//�{�^���������ꂽ���H
	push_button_ = false;
	//�X�e�[�W�^�C�}�[
	next_stage_time_ = 60.0f;
	//��x�����Ăяo���p�t���O
	only_one_ = false;
	//BGM���Ƃ߂邩
	bgm_stop_ = false;
	// ������J�����O��L���ɂ���
	gsEnable(GS_FRUSTUM_CULLING);
	// �f�t�H���g�V�F�[�_�[�̏������i���b�V���t�@�C����ǂݍ��ޑO�ɗL���ɂ���j
	gsInitDefaultShader();
	//�L�����N�^�[���b�V���ǂݍ���
	//�i�C�g���b�V���ǂݍ���
	gsLoadMesh(Mesh_Knight, "Assets/Character/Knight/Knight.msh");
	gsLoadSkeleton(Mesh_Knight, "Assets/Character/Knight/Knight.skl");
	gsLoadAnimation(Mesh_Knight, "Assets/Character/Knight/Knight.anm");
	//�t�@�C�^�[���b�V��
	gsLoadSkinMesh(Mesh_Fighter, "Assets/Character/Fighter/Fighter.msh");
	gsLoadSkeleton(Mesh_Fighter, "Assets/Character/Fighter/Fighter.skl");
	gsLoadAnimation(Mesh_Fighter, "Assets/Character/Fighter/Fighter.anm");
	//�����W���[���b�V��
	gsLoadSkinMesh(Mesh_Ranger, "Assets/Character/Ranger/Ranger.msh");
	gsLoadSkeleton(Mesh_Ranger, "Assets/Character/Ranger/Ranger.skl");
	gsLoadAnimation(Mesh_Ranger, "Assets/Character/Ranger/Ranger.anm");
	//�G�l�~�[���b�V���ǂݍ���
	//�X�P���g�����b�V��
	gsLoadMesh(Mesh_Skeleton, "Assets/Enemy/Skeleton/Skeleton.msh");
	gsLoadSkeleton(Mesh_Skeleton, "Assets/Enemy/Skeleton/Skeleton.skl");
	gsLoadAnimation(Mesh_Skeleton, "Assets/Enemy/Skeleton/Skeleton.anm");
	//�h���S�����b�V��
	gsLoadSkinMesh(Mesh_Doragon, "Assets/Enemy/Doragon/Doragon.msh");
	gsLoadSkeleton(Mesh_Doragon, "Assets/Enemy/Doragon/Doragon.skl");
	gsLoadAnimation(Mesh_Doragon, "Assets/Enemy/Doragon/Doragon.anm");
	//���@�g�����b�V��
	gsLoadSkinMesh(Mesh_Mage, "Assets/Enemy/Mage/Mage.msh");
	gsLoadSkeleton(Mesh_Mage, "Assets/Enemy/Mage/Mage.skl");
	gsLoadAnimation(Mesh_Mage, "Assets/Enemy/Mage/Mage.anm");
	//�S�[�������b�V��
	gsLoadSkinMesh(Mesh_Golem, "Assets/Enemy/Golem/Golem.msh");
	gsLoadSkeleton(Mesh_Golem, "Assets/Enemy/Golem/Golem.skl");
	gsLoadAnimation(Mesh_Golem, "Assets/Enemy/Golem/Golem.anm");
	//�I�[�N���b�V��
	gsLoadSkinMesh(Mesh_Orc, "Assets/Enemy/Orc/Orc.msh");
	gsLoadSkeleton(Mesh_Orc, "Assets/Enemy/Orc/Orc.skl");
	gsLoadAnimation(Mesh_Orc, "Assets/Enemy/Orc/Orc.anm");
	//�|��b�V��
	gsLoadMesh(Mesh_Arrow, "Assets/Weapon/Arrow.mshb");
	//�X�J�C�{�b�N�X�ǂݍ���
	gsLoadMesh(Mesh_Skybox, "Assets/Skybox/skydome.msh");
	//�I�N�c���\�ǂݍ���
	gsLoadOctree(Octree_Stage, "Assets/Octree/stage.oct");
	gsLoadOctree(Octree_Collider, "Assets/Octree/stage_collider.oct");
	//�L�����N�^�[�i���o�[�ɂ���ăv���C���[�ǉ�
	//�O�Ȃ�i�C�g�A�P�Ȃ�t�@�C�^�[�A�Q�Ȃ烌���W���[
	if (Common_Number::CharacterNum == 0)
		world_.add_actor(new Knight{ &world_, GSvector3{ -90.0f, -2.0f, -30.0f } });
	else if (Common_Number::CharacterNum == 1)
		world_.add_actor(new Fighter{ &world_, GSvector3{ -90.0f, -2.0f, -30.0f } });
	else
		world_.add_actor(new Ranger{ &world_, GSvector3{ -90.0f, -2.0f, -30.0f } });
	//�G�l�~�[�ǉ�
	//�S�[��������
	world_.add_actor(new Enemy_Golem{ &world_, GSvector3{ -90.0f, -1.0f, 60.0f  },90.0f });
	//�I�[�N����
	world_.add_actor(new Enemy_Orc{ &world_, GSvector3{ -25.0f, 0.0f, 25.0f  },180.0f });
	world_.add_actor(new Enemy_Orc{ &world_, GSvector3{ -20.0f, 0.0f, 25.0f  },180.0f });
	world_.add_actor(new Enemy_Orc{ &world_, GSvector3{ -15.0f, 0.0f, 25.0f  },180.0f });
	//���@�g������
	world_.add_actor(new Enemy_Mage{ &world_, GSvector3{ -18.0f, 0.0f, 35.0f  },180.0f });
	world_.add_actor(new Enemy_Mage{ &world_, GSvector3{ -13.0f, 0.0f, 35.0f  },180.0f });
	//�h���S������
	world_.add_actor(new Enemy_Doragon{ &world_, GSvector3{  -45.0f, -2.0f, -21.0f },-110.0f });
	world_.add_actor(new Enemy_Doragon{ &world_, GSvector3{  -45.0f, -2.0f, -12.0f },-110.0f });
	world_.add_actor(new Enemy_Doragon{ &world_, GSvector3{  -45.0f, -2.0f, -30.0f },-110.0f });
	//�X�P���g������
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
	//�����Ȃ��ǂ̒ǉ�
	world_.add_actor(new InvisibleWall{ &world_, GSvector3{ -20.0f, 0.0f, 0.0f  },"Doragon" });
	world_.add_actor(new InvisibleWall{ &world_, GSvector3{ -40.0f, 0.0f, 65.0f  },"Mage" });
	//�t�B�[���h�ǉ�
	world_.add_field(new Field{ Octree_Stage,Octree_Collider,Mesh_Skybox });
	//�J�����ǉ�
	world_.add_camera(new Camera{ &world_ , GSvector3{-0.5f, 0.0f, -0.2f}, GSvector3{0.0f, 0.0f, 0.0f} });
	//���C�g�ǉ�
	world_.add_light(new Light{ &world_ });
	//SE�ǂݍ���
	SE::Load();
	//BGM�ǂݍ���
	BGM::Load();
	//BGM�Đ�
	BGM::PlayMusic(BGM_Play);
	//�摜�ǂݍ���
	//HP����
	gsLoadTexture(UI_HP_Spel, "Assets/Texture/UI_HPspel.png");
	//�Q�[���N���A����
	gsLoadTexture(UI_GameClear_Spel, "Assets/Texture/GameClear.png");
	//�Q�[���I�[�o�[����
	gsLoadTexture(UI_GameOver_Spel, "Assets/Texture/GameOver.png");
	//���g���C����
	gsLoadTexture(UI_Retry_Spel, "Assets/Texture/UI_Retryspel.png");
	//�^�C�g������
	gsLoadTexture(UI_Title_Spel, "Assets/Texture/UI_Titlespel.png");
	//�v���C���[HP�o�[
	gsLoadTexture(UI_Player_HP_Bar, "Assets/Texture/Player_HP.png");
	//�G�l�~�[HP�o�[
	gsLoadTexture(UI_Enemy_HP_Bar, "Assets/Texture/Enemy_HP.png");
	//�G�l�~�[���O
	gsLoadTexture(UI_Enemy_Name, "Assets/Texture/GolemName.png");
	//�Q�[���I�[�o�[���X���[�N
	gsLoadTexture(GameOver_Smoke, "Assets/Texture/DeadSmoke.png");
	//�N�G�X�g��
	gsLoadTexture(Quest_Paper, "Assets/Texture/QuestPaper.png");
	//�L�����Z���N�g����
	gsLoadTexture(Select_CharacterSelect, "Assets/Texture/CharacterSelect.png");
	// �V���h�E�}�b�v�̍쐬
	static const GSuint shadow_map_size[] = { 2048, 2048 };
	gsCreateShadowMap(2, shadow_map_size, GS_TRUE);
	// �V���h�E�}�b�v��K�p���鋗��(���_����̋����j
	gsSetShadowMapDistance(60.0f);
	// �J�X�P�[�h�V���h�E�}�b�v�̕����ʒu�𒲐��i�f�t�H���g��0.5�j
	gsSetShdowMapCascadeLamda(0.7f);
	// �V���h�E�̔Z����ݒ�(0.0:�Z���`1.0:����)
	gsSetShadowMapAttenuation(0.0f);
	// ���C�g�}�b�v�̓ǂݍ���
	gsLoadLightmap(0, "Assets/Lightmap/Lightmap.txt");
	// ���t���N�V�����v���[�u�̓ǂݍ���
	gsLoadReflectionProbe(0, "Assets/RefProbe/ReflectionProbe.txt");
	//�Q�[���N���A���菉����
	Common_Number::is_game_clear_ = false;
	//�Q�[���I�[�o�[����̏�����
	Common_Number::is_game_over_ = false;
}

void GamePlayScene::update(float delta_time) {
	//�Q�[���X�^�[�g��false�Ȃ�
	if (!game_start_)
	{
		//�Q�[���X�^�[�g�^�C�}�[���������
		game_start_timer_ -= delta_time;
		if (quest_lotate_ >= 0.0f)
			quest_lotate_ -= delta_time * lotate_speed_;
		//�X�P�[����1�{�ɂȂ�܂ň���
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
		//�Q�[���X�^�[�g�^�C�}�[���O�Ȃ�
		if (game_start_timer_ <= 0)
			//�Q�[���J�n
			game_start_ = true;
	}
	else
		world_.update(delta_time);
	//�Q�[���I�[�o�[��true�Ȃ�
	if (Common_Number::is_game_over_)
	{
		if (!bgm_stop_)
		{
			//BGM���Ƃ߂�i�Q�[���v���C����)
			gsStopMusic();
			bgm_stop_ = true;
		}
		BGM::PlayMusic(BGM_GameOver);
		//���̃V�[���ɍs�����߂̑���
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
	//�Q�[���N���A�\��true�Ȃ�
	if (Common_Number::is_game_clear_)
	{
		if (!bgm_stop_)
		{
			//BGM���Ƃ߂�i�Q�[���v���C����)
			gsStopMusic();
			bgm_stop_ = true;
		}
		//���̃V�[���ɍs�����߂̑���
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
		//�^�C�}�[������
		next_stage_time_ -= delta_time;
		if (next_stage_time_ <= 0)
			is_end_ = true;     // �V�[���I��
	}
}
void GamePlayScene::draw()const {
	//�Q�[���X�^�[�g��false�Ȃ�
	if (!game_start_)
	{
		//�Q�[���J�n���̃N�G�X�g�̉��o
		const GSvector2 UIscale_Quest{ quest_scale_,quest_scale_ };
		gsDrawSprite2D(Quest_Paper, &UIposition_Quest, NULL, &UIcenter_Quest, NULL, &UIscale_Quest, quest_lotate_);
	}
	else
	{
		world_.draw();
		//�Q�[���I�[�o�[��true�Ȃ�
		if (Common_Number::is_game_over_)
		{
			//�X���[�N��������
			gsDrawSprite2D(GameOver_Smoke, &UIposition_Smoke, NULL, NULL, &UIcolor_Smoke, NULL, 0.0f);
			//�Q�[���I�[�o�[����
			gsDrawSprite2D(UI_GameOver_Spel, &UIposition_GameOver, NULL, NULL, NULL, NULL, 0.0f);
			//�I������Ă��Ȃ��{�^���̃��l��������
			if (next_title_)
				gsDrawSprite2D(UI_Retry_Spel, &UIposition_RetryMoveButton, NULL, NULL, &UIcolor_Notselect, NULL, 0.0f);
			else gsDrawSprite2D(UI_Retry_Spel, &UIposition_RetryMoveButton, NULL, NULL, NULL, NULL, 0.0f);
			if (!next_title_)
				gsDrawSprite2D(UI_Title_Spel, &UIposition_TitleMoveButton, NULL, NULL, &UIcolor_Notselect, NULL, 0.0f);
			else gsDrawSprite2D(UI_Title_Spel, &UIposition_TitleMoveButton, NULL, NULL, NULL, NULL, 0.0f);
		}
		//�Q�[���N���A��true�Ȃ�
		if (Common_Number::is_game_clear_)
		{
			gsDrawSprite2D(UI_GameClear_Spel, &UIposition_GameClear, NULL, NULL, NULL, NULL, 0.0f);
			//�I������Ă��Ȃ��{�^���̃��l��������
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
	//�Q�[���N���A��true�Ȃ�
	if (Common_Number::is_game_clear_)
	{
		//�l�N�X�g�^�C�g����false�Ȃ�L�����N�^�[�Z���N�g�Atrue�Ȃ�^�C�g��
		if (!next_title_)return "CharacterSelect";
		else return "TitleScene";
	}
	//�Q�[���I�[�o�[��true�Ȃ�
	if (Common_Number::is_game_over_)
	{
		//�l�N�X�g�^�C�g����false�Ȃ�Q�[���v���C�Atrue�Ȃ�^�C�g��
		if (!next_title_)return "GamePlayScene";
		else return "TitleScene";
	}
}
void GamePlayScene::end() {
	//���[���h�폜
	world_.clear();
	//SE�폜
	SE::DeleteSE();
	//BGM�폜
	BGM::DeleteMusic();
	//�A�Z�b�g�폜
	//�i�C�g���b�V���f�[�^
	gsDeleteMesh(Mesh_Knight);
	gsDeleteSkeleton(Mesh_Knight);
	gsDeleteAnimation(Mesh_Knight);
	//�����W���[���b�V���f�[�^
	gsDeleteMesh(Mesh_Ranger);
	gsDeleteSkeleton(Mesh_Ranger);
	gsDeleteAnimation(Mesh_Ranger);
	//�t�@�C�^�[���b�V���f�[�^
	gsDeleteMesh(Mesh_Fighter);
	gsDeleteSkeleton(Mesh_Fighter);
	gsDeleteAnimation(Mesh_Fighter);
	//�h���S�����b�V���f�[�^
	gsDeleteMesh(Mesh_Doragon);
	gsDeleteSkeleton(Mesh_Doragon);
	gsDeleteAnimation(Mesh_Doragon);
	//�X�P���g�����b�V���f�[�^
	gsDeleteMesh(Mesh_Skeleton);
	gsDeleteSkeleton(Mesh_Skeleton);
	gsDeleteAnimation(Mesh_Skeleton);
	//���@�g�����b�V���f�[�^
	gsDeleteMesh(Mesh_Mage);
	gsDeleteSkeleton(Mesh_Mage);
	gsDeleteAnimation(Mesh_Mage);
	//�I�[�N���b�V���f�[�^
	gsDeleteMesh(Mesh_Orc);
	gsDeleteSkeleton(Mesh_Orc);
	gsDeleteAnimation(Mesh_Orc);
	//�S�[�������b�V���f�[�^
	gsDeleteMesh(Mesh_Golem);
	gsDeleteSkeleton(Mesh_Golem);
	gsDeleteAnimation(Mesh_Golem);
	//�X�J�C���b�V���f�[�^
	gsDeleteMesh(Mesh_Skybox);
	//�I�N�g���[
	gsDeleteOctree(Octree_Stage);
	gsDeleteOctree(Octree_Collider);
	//�摜�폜
	//HP����
	gsDeleteTexture(UI_HP_Spel);
	//�Q�[���N���A����
	gsDeleteTexture(UI_GameClear_Spel);
	//�Q�[���I�[�o�[����
	gsDeleteTexture(UI_GameOver_Spel);
	//���g���C����
	gsDeleteTexture(UI_Retry_Spel);
	//�^�C�g������
	gsDeleteTexture(UI_Title_Spel);
	//�v���C���[HP�o�[
	gsDeleteTexture(UI_Player_HP_Bar);
	//�Q�[���I�[�o�[���X���[�N
	gsDeleteTexture(GameOver_Smoke);
	//�N�G�X�g��
	gsDeleteTexture(Quest_Paper);
	//�G�l�~�[HP
	gsDeleteTexture(UI_Enemy_HP_Bar);
	//�G�l�~�[���O
	gsDeleteTexture(UI_Enemy_Name);
}