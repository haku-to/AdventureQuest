#ifndef CHARACTER_SELECT_SCENE_H_
#define CHARACTER_SELECT_SCENE_H_
#include "IScene.h"
#include <gslib.h>
//�L�����N�^�[�Z���N�g�V�[���N���X
class CharacterSelectScene :public IScene {
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
	//�X�e�[�W�J�ڎ���
	float next_stage_time_{ 60.0f };
	//�Z���N�g�t���[���̃X�P�[���{��
	const float select_frame_diameter_{ 0.01f };
	//�Z���N�g�t���[���̈ړ��l
	const float select_frame_movement_{ 400.0f };
	//�Z���N�g�t���[����X�ʒu
	float select_frame_pos_{ 250.0f };
	//�Z���N�g�t���[���̃X�P�[���ύX�l
	float select_frame_scale_{ 1.0f };
	//���̃X�e�[�W�ԍ�
	int next_stage_{ 0 };
	//���̃X�e�[�W�̖��O
	std::string next_stage_set;
};
#endif