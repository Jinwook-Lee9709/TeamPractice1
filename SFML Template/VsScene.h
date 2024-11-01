#pragma once
#include "Scene.h"

class Tree;
class Player;
class TextGo;
class UiScore;
class UiTimebar;

class VsScene : public Scene
{
public:
	enum class Status
	{
		Awake,
		Game,
		GameOver,
		Pause,
	};

protected:
	Status currentStatus = Status::Awake;

	Tree* tree;
	Player* player;

	Tree* tree2;
	Player* player2;

	TextGo* centerMsg;
	UiScore* uiScore;
	UiScore* uiScore2;
	UiTimebar* uiTimer;

	GameObject* spriteHeartP1[3];
	GameObject* spriteHeartP2[3];

	int score = 0;
	int score2 = 0;
	float timer = 0.f;
	float gameTime = 10.f;

	sf::Sound sfxDeath;
	sf::Sound sfxTimeOut;

	std::string sbIdDeath = "sound/death.wav";
	std::string sbIdTimeOut = "sound/out_of_time.wav";

public:
	VsScene();
	~VsScene() = default;

	void Init() override;
	void Enter() override;
	void Exit() override;

	void Update(float dt) override;

	void Draw(sf::RenderWindow& window) override;

	void SetCenterMessage(const std::string& msg);
	void SetVisibleCenterMessage(bool visible);

	void SetScore(int score);
	void SetScore2P(int score);

	void SetStatus(Status newStatus);
	void UpdateAwake(float dt);
	void UpdateGame(float dt);
	void UpdateGameOver(float dt);
	void UpdatePause(float dt);

	void CheckWinner();

	void OnChop(Sides side, ChkPlayer chk) override;

};

