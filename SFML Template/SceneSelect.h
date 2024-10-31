#pragma once
#include "Scene.h"

class SpriteButton;
class SpriteGo; 
class SelectPlate;

class SceneSelect :
    public Scene
{
public:
	enum class Status
	{
		None = -1,
		SelectMode,
		SelectCharacter,
	};

protected:
	SpriteButton* single;
	SpriteButton* multi;
	bool singlePressed;
	bool multiPressed;

	SelectPlate* p1Plate;
	SelectPlate* p2Plate;
	int p1SpriteIndex;
	int p2SpriteIndex;
	bool p1Selected;
	bool p2Selected;
	std::string characterTexId[3] ={"graphics/player1.png", "graphics/player2.png", "graphics/player3.png"	};

	Status prevStatus = Status::None;
	Status currentStatus = Status::SelectMode;

public:
	SceneSelect();
	~SceneSelect() = default;

	void Init() override;
	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void UpdateSelectMode();
	void UpdateSelectCharacter();
	void Draw(sf::RenderWindow& window) override;
};

