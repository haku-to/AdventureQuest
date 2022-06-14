#include "SE.h"
#include "Assets.h"
#include <gslib.h>

//SE���[�h
void SE::Load() {
    //�Z���N�g��
    gsLoadSE(SE_Select, "Assets/SE/Select.wav", 1, GWAVE_DEFAULT);
    //�Z���N�g�ύX��
    gsLoadSE(SE_SelectMove, "Assets/SE/CharaSelectChange.wav", 1, GWAVE_DEFAULT);
    //�N�G�X�g�X�^�[�g��
    gsLoadSE(SE_QuestStart, "Assets/SE/QuestStart.wav", 1, GWAVE_DEFAULT);
    //�h���S���pSE
    gsLoadSE(SE_Enemy_Doragon_Down, "Assets/SE/Doragon_Down.wav", 1, GWAVE_DEFAULT);
    gsLoadSE(SE_Enemy_Doragon_Damage, "Assets/SE/Doragon_Damage.wav", 1, GWAVE_DEFAULT);
    //�S�[�����pSE
    gsLoadSE(SE_Enemy_Golem_Down, "Assets/SE/Golem_Down.wav", 1, GWAVE_DEFAULT);
    gsLoadSE(SE_Enemy_Golem_Damage, "Assets/SE/Golem_Damage.wav", 1, GWAVE_DEFAULT);
    gsLoadSE(SE_PunchHit_Golem, "Assets/SE/Golem_GetHit_Punch.wav", 1, GWAVE_DEFAULT);
    gsLoadSE(SE_ArrowHit_Golem, "Assets/SE/Golem_GetHit_Arrow.wav", 1, GWAVE_DEFAULT);
    gsLoadSE(SE_SwordHit_Golem, "Assets/SE/Golem_GetHit_Sword.wav", 1, GWAVE_DEFAULT);
    //�X�P���g���pSE
    gsLoadSE(SE_Enemy_Skeleton_Down, "Assets/SE/Skeleton_Down.wav", 1, GWAVE_DEFAULT);
    gsLoadSE(SE_Enemy_Skeleton_Damage, "Assets/SE/Skeleton_Damage.wav", 1, GWAVE_DEFAULT);
    //���@�g���pSE
    gsLoadSE(SE_Enemy_Mage_Down, "Assets/SE/Mage_Down.wav", 1, GWAVE_DEFAULT);
    gsLoadSE(SE_Enemy_Mage_Damage, "Assets/SE/Mage_Damage.wav", 1, GWAVE_DEFAULT);
    //�I�[�N�pSE
    gsLoadSE(SE_Enemy_Orc_Down, "Assets/SE/Orc_Damage.wav", 1, GWAVE_DEFAULT);
    gsLoadSE(SE_Enemy_Orc_Damage, "Assets/SE/Orc_Damage.wav", 1, GWAVE_DEFAULT);
    //�i�C�g�pSE
    gsLoadSE(SE_Knight_Attack1, "Assets/SE/Knight_Attack1.wav", 1, GWAVE_DEFAULT);
    gsLoadSE(SE_Knight_Attack2, "Assets/SE/Knight_Attack2.wav", 1, GWAVE_DEFAULT);
    gsLoadSE(SE_Knight_Attack3, "Assets/SE/Knight_Attack3.wav", 1, GWAVE_DEFAULT);
    gsLoadSE(SE_Knight_Damage, "Assets/SE/Knight_Damage.wav", 1, GWAVE_DEFAULT);
    gsLoadSE(SE_Knight_Down, "Assets/SE/Knight_Down.wav", 1, GWAVE_DEFAULT);
    //�����W���[�pSE
    gsLoadSE(SE_Ranger_Attack1, "Assets/SE/Ranger_Attack1.wav", 1, GWAVE_DEFAULT);
    gsLoadSE(SE_Ranger_Attack2, "Assets/SE/Ranger_Attack2.wav", 1, GWAVE_DEFAULT);
    gsLoadSE(SE_Ranger_Attack3, "Assets/SE/Ranger_Attack3.wav", 1, GWAVE_DEFAULT);
    gsLoadSE(SE_Ranger_Damage, "Assets/SE/Ranger_Damage.wav", 1, GWAVE_DEFAULT);
    gsLoadSE(SE_Ranger_Down, "Assets/SE/Ranger_Down.wav", 1, GWAVE_DEFAULT);
    //�t�@�C�^�[�pSE
    gsLoadSE(SE_Fighter_Attack1, "Assets/SE/Fighter_Attack1.wav", 1, GWAVE_DEFAULT);
    gsLoadSE(SE_Fighter_Attack2, "Assets/SE/Fighter_Attack1.wav", 1, GWAVE_DEFAULT);
    gsLoadSE(SE_Fighter_Attack3, "Assets/SE/Fighter_Attack1.wav", 1, GWAVE_DEFAULT);
    gsLoadSE(SE_Fighter_Damage, "Assets/SE/Fighter_Damage.wav", 1, GWAVE_DEFAULT);
    gsLoadSE(SE_Fighter_Down, "Assets/SE/Fighter_Down.wav", 1, GWAVE_DEFAULT);
    //�G�l�~�[�ɑ΂���U���q�b�g��
    gsLoadSE(SE_PunchHit, "Assets/SE/PunchHit.wav", 1, GWAVE_DEFAULT);
    gsLoadSE(SE_ArrowHit, "Assets/SE/AllowHit.wav", 1, GWAVE_DEFAULT);
    gsLoadSE(SE_SwordHit, "Assets/SE/SwordHit.wav", 1, GWAVE_DEFAULT);
    //�����Ȃ��ǉ�����
    gsLoadSE(SE_InvisibleOff, "Assets/SE/InvisibleOff.wav", 1, GWAVE_DEFAULT);
    //�N���A�����Ƃ��ɏo����
    gsLoadSE(SE_GameClear, "Assets/SE/SE_Clear.wav", 1, GWAVE_DEFAULT);
}

//SE�Đ�
void SE::PlaySE(int num) {
    gsPlaySE(num);
}

//SE�폜
void SE::DeleteSE() {
    //�Z���N�g�{�^��
    gsDeleteSE(SE_Select);
    //�N�G�X�g�X�^�[�g��
    gsDeleteSE(SE_QuestStart);
    //�Z���N�g�{�^���ύX��
    gsDeleteSE(SE_SelectMove);
    //�p���`�q�b�g��
    gsDeleteSE(SE_PunchHit);
    //�A���[�q�b�g��
    gsDeleteSE(SE_ArrowHit);
    //�\�[�h�q�b�g��
    gsDeleteSE(SE_SwordHit);
    //�h���S�����S
    gsDeleteSE(SE_Enemy_Doragon_Down);
    //�h���S���_���[�W
    gsDeleteSE(SE_Enemy_Doragon_Damage);
    //�S�[�������S
    gsDeleteSE(SE_Enemy_Golem_Down);
    //�S�[�����_���[�W
    gsDeleteSE(SE_Enemy_Golem_Damage);
    //�X�P���g�����S
    gsDeleteSE(SE_Enemy_Skeleton_Down);
    //�X�P���g���_���[�W
    gsDeleteSE(SE_Enemy_Skeleton_Damage);
    //���@�g�����S
    gsDeleteSE(SE_Enemy_Mage_Down);
    //���@�g���_���[�W
    gsDeleteSE(SE_Enemy_Mage_Damage);
    //�I�[�N���S
    gsDeleteSE(SE_Enemy_Orc_Down);
    //�I�[�N�_���[�W
    gsDeleteSE(SE_Enemy_Orc_Damage);
    //�i�C�g�U����
    gsDeleteSE(SE_Knight_Attack1);
    gsDeleteSE(SE_Knight_Attack2);
    gsDeleteSE(SE_Knight_Attack3);
    //�i�C�g�_���[�W��
    gsDeleteSE(SE_Knight_Damage);
    //�i�C�g���S��
    gsDeleteSE(SE_Knight_Down);
    //�����W���[�U����
    gsDeleteSE(SE_Ranger_Attack1);
    gsDeleteSE(SE_Ranger_Attack2);
    gsDeleteSE(SE_Ranger_Attack3);
    //�����W���[�_���[�W��
    gsDeleteSE(SE_Ranger_Damage);
    //�����W���[���S��
    gsDeleteSE(SE_Ranger_Down);
    //�t�@�C�^�[�U����
    gsDeleteSE(SE_Fighter_Attack1);
    gsDeleteSE(SE_Fighter_Attack2);
    gsDeleteSE(SE_Fighter_Attack3);
    //�t�@�C�^�[�_���[�W��
    gsDeleteSE(SE_Fighter_Damage);
    //�t�@�C�^�[���S��
    gsDeleteSE(SE_Fighter_Down);
}