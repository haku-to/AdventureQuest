#ifndef ASSETS_H_
#define ASSETS_H_
//���b�V��
enum {
	Mesh_Knight,        //�v���C���[
	Mesh_Fighter,       //�t�@�C�^�[
	Mesh_Ranger,        //�����W���[
	Mesh_Skeleton,      //�X�P���g��
	Mesh_Doragon,       //�h���S��
	Mesh_Mage,	        //���@�g��
	Mesh_Orc,	        //�I�[�N
	Mesh_Golem,         //�S�[����
	Mesh_Skybox,        //�X�J�C�{�b�N�X
	Mesh_Arrow,         //�|��
};
//�X�e�[�W
enum {
	Octree_Stage,       //�X�e�[�W���b�V��
	Octree_Collider     //�X�e�[�W�R���C�_�[
};
//�摜
enum
{
	BackGround,               	 //�w�i
	Title_BackGround,			 //�^�C�g�������t�w�i
	Title_PushtoStart,			 //�^�C�g���@�ە���
	Select_CharacterSelect,		 //�L�����N�^�[�Z���N�g����
	Select_Knight,				 //�i�C�g�̉摜
	Select_Fighter,				 //�t�@�C�^�[�̉摜
	Select_Ranger,				 //�����W���[�̉摜
	Name_Knight,				 //�i�C�g�̖��O����
	Name_Fighter,				 //�t�@�C�^�[�̖��O����
	Name_Ranger,				 //�����W���[�̖��O����
	Win_Star,                    //���������L�����N�^�[�ɐ��������
	Select_Frame,				 //�L�����N�^�[�Z���N�g�t���[��
	UI_HP_Spel,					 //HP����
	UI_GameClear_Spel,			 //�N���A����
	UI_GameOver_Spel,			 //�Q�[���I�[�o�[����
	UI_Retry_Spel,				 //���g���C����
	UI_Title_Spel,				 //�^�C�g������
	UI_Player_HP_Frame,			 //�v���C���[HP�t���[��
	UI_Player_HP_Bar,			 //�v���C���[HP
	UI_Enemy_HP_Bar,			 //�G�l�~�[��HP
	UI_Enemy_Name,  			 //�G�l�~�[�̖��O����
	GameOver_Smoke,				 //�Q�[���I�[�o�[���̃X���[�N
	Quest_Paper,				 //�N�G�X�g�̎��摜
};
//SE
enum {
	SE_Select,					  //�Z���N�g��
	SE_SelectMove,			      //�Z���N�g�ύX��
	SE_QuestStart,                //�N�G�X�g�X�^�[�g��
	SE_GameClear,                 //�Q�[���N���A��
	SE_PunchHit,				  //�p���`�q�b�g��
	SE_ArrowHit,                  //�A���[�q�b�g��
	SE_SwordHit,                  //�\�[�h�q�b�g��
	SE_InvisibleOff,              //�����Ȃ��ǂ��������ꂽ���̉�
	SE_Enemy_Doragon_Down,		  //�h���S�����S
	SE_Enemy_Doragon_Damage,	  //�h���S���_���[�W
	SE_Enemy_Golem_Down,		  //�S�[�������S
	SE_Enemy_Golem_Damage,  	  //�S�[�����_���[�W
	SE_PunchHit_Golem,            //�S�[�����p���`�q�b�g��
	SE_ArrowHit_Golem,			  //�S�[�����A���[�q�b�g��
	SE_SwordHit_Golem,			  //�S�[�����\�[�h�q�b�g��
	SE_Enemy_Skeleton_Down,		  //�X�P���g�����S
	SE_Enemy_Skeleton_Damage,	  //�X�P���g���_���[�W
	SE_Enemy_Mage_Down,			  //���@�g�����S
	SE_Enemy_Mage_Damage,		  //���@�g���_���[�W
	SE_Enemy_Orc_Down,			  //�I�[�N���S
	SE_Enemy_Orc_Damage,		  //�I�[�N�_���[�W
	SE_Knight_Attack1,            //�i�C�g�U���P
	SE_Knight_Attack2,			  //�i�C�g�U���Q
	SE_Knight_Attack3,			  //�i�C�g�U���R
	SE_Knight_Damage,			  //�i�C�g�_���[�W
	SE_Knight_Down,				  //�i�C�g���S
	SE_Ranger_Attack1,			  //�����W���[�U���P
	SE_Ranger_Attack2,			  //�����W���[�U���Q
	SE_Ranger_Attack3,			  //�����W���[�U���R
	SE_Ranger_Damage,			  //�����W���[�_���[�W
	SE_Ranger_Down,				  //�����W���[���S
	SE_Fighter_Attack1,			  //�t�@�C�^�\�U���P
	SE_Fighter_Attack2,			  //�t�@�C�^�\�U���Q
	SE_Fighter_Attack3,			  //�t�@�C�^�\�U���R
	SE_Fighter_Damage,			  //�t�@�C�^�\�_���[�W
	SE_Fighter_Down,			  //�t�@�C�^�\���S
};
//BGM
enum {
	BGM_Title,                    //�^�C�g��BGM
	BGM_Play,                     //�Q�[���v���CBGM
	BGM_GameOver,                 //�Q�[���I�[�o�[BGM
	BGM_CharaSelect,              //�L�����Z���N�gBGM
};
#endif