#pragma once
#include "Scene.h"

class TextGo;
class Button;

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

	std::string BackGroundtexId;

	TextGo* centerMsg;

	Button* stage1Btn;
	Button* stage2Btn;
	bool stage1BtnPressed;
	bool stage2BtnPressed;

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

	void GetBackgroundTexId(const std::string& texId);
};

