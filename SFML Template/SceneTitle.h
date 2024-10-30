#pragma once
#include "Scene.h"

class Button;

class SceneTitle : public Scene
{
protected:
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
};

