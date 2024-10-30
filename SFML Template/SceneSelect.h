#pragma once
#include "Scene.h"
class SceneSelect :
    public Scene
{
protected:
	bool startBtnPressed;
	bool quitBtnPressed;
public:
	SceneSelect();
	~SceneSelect() = default;

	void Init() override;
	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

