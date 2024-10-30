#pragma once
#include "Scene.h"

class TextGo;
class Button;

class SceneDev2 : public Scene
{	
protected:
	Button* startBtn;
	Button* quitBtn;
	bool startBtnPressed;
	bool quitBtnPressed;
public:
	SceneDev2();
	~SceneDev2() = default;

	void Init() override;
	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

