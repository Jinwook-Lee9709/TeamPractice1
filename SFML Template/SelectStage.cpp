#include "stdafx.h"
#include "SelectStage.h"
#include "SpriteGo.h"
#include "TextGo.h"

SelectStage::SelectStage() : Scene(SceneIds::SelectStage)
{

}

void SelectStage::Init()
{
	std::cout << "SelectStage::Init()" << std::endl;

	GameObject* obj = AddGo(new SpriteGo("graphics/background.png"));
	obj->sortingLayer = SortingLayers::Background;
	obj->sortingOrder = -1;
	obj->SetOrigin(Origins::MC);
	obj->SetPosition({ 1920 / 2, 1080 / 2 });

	centerMsg = AddGo(new TextGo("fonts/KOMIKAP_.ttf", "Center Maessage"));
	centerMsg->sortingLayer = SortingLayers::UI;

	Scene::Init();

	centerMsg->text.setCharacterSize(100);
	centerMsg->text.setFillColor(sf::Color::White);
	centerMsg->SetPosition({ 1920.f / 2.f, 1080.f / 2.f - 400.f });
}

void SelectStage::Enter()
{
	std::cout << "SelectStage::Enter()" << std::endl;

	TEXTURE_MGR.Load("graphics/background.png");
	FONT_MGR.Load("fonts/KOMIKAP_.ttf");


	Scene::Enter();

	SetStatus(Status::Awake);
}

void SelectStage::Exit()
{
	std::cout << "SelectStage::Exit()" << std::endl;

	Scene::Exit();

	TEXTURE_MGR.Unload("graphics/background.png");
	TEXTURE_MGR.Unload("graphics/player.png");
}

void SelectStage::Update(float dt)
{
	Scene::Update(dt);

	if (InputMgr::GetKeyDown(sf::Keyboard::Num1))
	{
		SCENE_MGR.ChangeScene(SceneIds::Dev1);
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Num2))
	{
		SCENE_MGR.ChangeScene(SceneIds::Dev2);
	}
}

void SelectStage::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void SelectStage::SetStatus(Status newStatus)
{
	Status prevStatus = currentStatus;
	currentStatus = newStatus;

	switch (currentStatus)
	{
	case SelectStage::Status::Awake:
		FRAMEWORK.SetTimeScale(0.f);
		SetVisibleCenterMessage(true);
		SetCenterMessage("SELECT STAGE!!");
		break;

	case SelectStage::Status::Select1:
		FRAMEWORK.SetTimeScale(1.f);
		SetVisibleCenterMessage(false);
		break;

	case SelectStage::Status::Select2:
		FRAMEWORK.SetTimeScale(0.f);
		SetVisibleCenterMessage(true);
		break;
	}
}

void SelectStage::SetCenterMessage(const std::string& msg)
{
	centerMsg->text.setString(msg);
	centerMsg->SetOrigin(Origins::MC);
}

void SelectStage::SetVisibleCenterMessage(bool visible)
{
	centerMsg->SetActive(visible);
}
