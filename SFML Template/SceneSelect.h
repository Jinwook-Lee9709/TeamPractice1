#pragma once
#include "Scene.h"

class Button;
class SceneSelect :
    public Scene
{
protected:
	Button* singleBtn;
	Button* multiBtn;
	bool singleBtnPressed;
	bool multiBtnPressed;
public:
	SceneSelect();
	~SceneSelect() = default;

	void Init() override;
	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

