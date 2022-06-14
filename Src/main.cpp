#include<GSgame.h>
#include"Scene/SceneManager.h"
#include"Scene/TitleScene.h"
#include"Scene/GamePlayScene.h"
#include"Scene/CharacterSelectScene.h"
class MyGame :public gslib::Game {
public:MyGame() : gslib::Game{ 1280, 720 } {
}
private:
	//�V�[���}�l�[�W���[
	SceneManager scene_manager_;
	void start() override {
		scene_manager_.add("TitleScene", new TitleScene());
		scene_manager_.add("GamePlayScene", new GamePlayScene());
		scene_manager_.add("CharacterSelect", new CharacterSelectScene());
		scene_manager_.change("TitleScene");
	}

	//�X�V
	void update(float delta_time)override {
		scene_manager_.update(delta_time);
	}

	//�`��
	void draw()override {
		scene_manager_.draw();
	}

	//�I��
	void end()override {
		scene_manager_.end();
	}
};
int main() {
	return MyGame().run();
}