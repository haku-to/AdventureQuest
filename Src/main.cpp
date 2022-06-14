#include<GSgame.h>
#include"Scene/SceneManager.h"
#include"Scene/TitleScene.h"
#include"Scene/GamePlayScene.h"
#include"Scene/CharacterSelectScene.h"
class MyGame :public gslib::Game {
public:MyGame() : gslib::Game{ 1280, 720 } {
}
private:
	//シーンマネージャー
	SceneManager scene_manager_;
	void start() override {
		scene_manager_.add("TitleScene", new TitleScene());
		scene_manager_.add("GamePlayScene", new GamePlayScene());
		scene_manager_.add("CharacterSelect", new CharacterSelectScene());
		scene_manager_.change("TitleScene");
	}

	//更新
	void update(float delta_time)override {
		scene_manager_.update(delta_time);
	}

	//描画
	void draw()override {
		scene_manager_.draw();
	}

	//終了
	void end()override {
		scene_manager_.end();
	}
};
int main() {
	return MyGame().run();
}