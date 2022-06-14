#include "BGM.h"
#include "Assets.h"
#include <gslib.h>
#include <GSmusic.h>

//BGM���[�h
void BGM::Load() {
	gsLoadMusic(BGM_Title, "Assets/BGM/BGM_Title.mp3", GS_TRUE);
	gsLoadMusic(BGM_CharaSelect, "Assets/BGM/BGM_CharaSelect.mp3", GS_TRUE);
	gsLoadMusic(BGM_Play, "Assets/BGM/BGM_Play.mp3", GS_TRUE);
	gsLoadMusic(BGM_GameOver, "Assets/BGM/BGM_GameOver.mp3", GS_TRUE);
}

//BGM�Đ�
void BGM::PlayMusic(int num) {
	gsBindMusic(num);
	gsPlayMusic();
}

//BGM�폜
void BGM::DeleteMusic() {
	gsDeleteMusic(BGM_Title);
	gsDeleteMusic(BGM_CharaSelect);
	gsDeleteMusic(BGM_Play);
	gsDeleteMusic(BGM_GameOver);
}