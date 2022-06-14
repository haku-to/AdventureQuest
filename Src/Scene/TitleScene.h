#ifndef TITLE_SCENE_H_
#define TITLE_SCENE_H_
#include "IScene.h"
#include <gslib.h>
//�^�C�g���V�[���N���X
class TitleScene :public IScene {
	//�J�n
	virtual void start()override;
	//�X�V
	virtual void update(float delta_time)override;
	//�`��
	virtual void draw()const override;
	//�I�����Ă��邩�H
	virtual bool is_end()const override;
	//���̃V�[����Ԃ�
	virtual std::string  next()const override;
	//�I��
	virtual void end()override;
private:
	//�I���t���O
	bool is_end_{ false };
	//�{�^���������ꂽ���H
	bool push_button_{ false };
	//�{�^���_��
	bool look_button_{ true };
	//�{�^���_�Ŏ���
	float button_count_{ 0.0f };
	//�{�^���_�ŊԊu
	float button_count_distance_{ 30.0f };
	//�X�e�[�W�J�ڎ���
	float next_stage_time_{ 60.0f };
	//���̃X�e�[�W�̖��O
	std::string next_stage_set;
};
#endif
