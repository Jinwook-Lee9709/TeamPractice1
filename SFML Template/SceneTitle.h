#pragma once
#include "Scene.h"

class Button;
class SpriteGo;

class SceneTitle : public Scene
{
protected:
	SpriteGo* title;
	sf::Vector2f titleScale = { 0.5f, 0.5f };
	float scaleMultiply = 0.02f;
	Button* startBtn;
	Button* quitBtn;
	bool startBtnPressed;
	bool quitBtnPressed;
public:
	SceneTitle();
	~SceneTitle() = default;

	void Init() override;
	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void TitleMove(float dt);
};

