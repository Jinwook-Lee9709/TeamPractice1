#pragma once
#include "Scene.h"

class TextGo;

class SelectStage : public Scene
{
public:
	enum class Status
	{
		Awake,
		Select1,
		Select2,
		Pause,
	};

protected:
	Status currentStatus = Status::Awake;

	TextGo* centerMsg;

public:
	SelectStage();
	~SelectStage() = default;

	void Init() override;
	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetStatus(Status newStatus);

	void SetCenterMessage(const std::string& msg);
	void SetVisibleCenterMessage(bool visible);
};

