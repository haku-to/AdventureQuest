#ifndef GAME_PLAY_SCENE_H_
#define GAME_PLAY_SCENE_H_
#include "IScene.h"
#include "World/World.h"
#include"Actor/Player/Knight.h"
//�Q�[���v���C�V�[��
class GamePlayScene :public IScene {
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
	//�v���C���[
	Knight player_;
	//���[���h
	World world_;
	//�{�^���������ꂽ���H
	bool push_button_{ false };
	//�X�e�[�W�J�ڎ���
	float next_stage_time_{ 60.0f };
	//�N�G�X�g�摜�̃X�P�[���l
	float quest_scale_{ 3.0f };
	//�N�G�X�g�摜�̉�]�l
	float quest_lotate_{ 700.0f };
	//�Q�[���X�^�[�g�^�C�}�[
	float game_start_timer_{ 200.0f };
	//��]���x
	float lotate_speed_{ 8.0f };
	//�g�呬�x
	float scale_speed_{ 100.0f };
	//���̃V�[���̔ԍ�
	int next_scene_{ 0 };
	//���̃V�[�����^�C�g���V�[����
	bool next_title_{ false };
	//�Q�[���X�^�[�g���Ă��邩
	bool game_start_{ false };
	//��x�����Ăяo�����߂̃u�[��
	bool only_one_{ false };
	//BGM���X�g�b�v�����邩
	bool bgm_stop_{ false };
	//�I�����Ă��邩
	bool is_end_{ false };
};
#endif