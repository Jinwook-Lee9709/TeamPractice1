#include "stdafx.h"
#include "SceneTitle.h"
#include "SpriteGo.h"
#include "TextGo.h"
#include "Button.h"

SceneTitle::SceneTitle() : Scene(SceneIds::Title)
{

}

void SceneTitle::Init()
{
	FONT_MGR.Load("fonts/KOMIKAP_.ttf");
	std::cout << "SceneDev2::Init()" << std::endl;

	auto* obj = AddGo(new SpriteGo("graphics/titlebackground.png"));
	startBtn = AddGo(new Button("fonts/KOMIKAP_.ttf"));
	quitBtn = AddGo(new Button("fonts/KOMIKAP_.ttf"));
	Scene::Init();


	obj->sortingLayer = SortingLayers::Background;
	obj->sortingOrder = -1;
	obj->SetOrigin(Origins::MC);
	obj->SetPosition({ 1920 / 2, 1080 / 2 });

	startBtn->sortingLayer = SortingLayers::UI;
	startBtn->sortingOrder = 0;
	startBtn->SetPosition({ 1920.f * 0.5f, 1080.f * 0.5f });
	startBtn->SetFontSize(100);
	startBtn->SetOrigin(Origins::MC);
	startBtn->SetText("START");

	quitBtn->sortingLayer = SortingLayers::UI;
	quitBtn->sortingOrder = 0;
	quitBtn->SetPosition({ 1920.f * 0.5f, 1080.f * 0.5f + 200.f });
	quitBtn->SetFontSize(100);
	quitBtn->SetOrigin(Origins::MC);
	quitBtn->SetText("QUIT");




	
}

void SceneTitle::Enter()
{
	std::cout << "SceneDev2::Enter()" << std::endl;

	TEXTURE_MGR.Load("graphics/titlebackground.png");
	FONT_MGR.Load("fonts/KOMIKAP_.ttf");

	Scene::Enter();
}

void SceneTitle::Exit()
{
	std::cout << "SceneDev2::Exit()" << std::endl;

	Scene::Exit();

	TEXTURE_MGR.Unload("graphics/Background.png");
	FONT_MGR.Unload("fonts/KOMIKAP_.ttf");
}

void SceneTitle::Update(float dt)
{
	Scene::Update(dt);

	//if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	//{
	//	SCENE_MGR.ChangeScene(SceneIds::Dev1);
	//}
	if (InputMgr::GetMouseButtonDown(sf::Mouse::Left)) {
		if (startBtn->IsCursorOn()) {
			startBtnPressed = true;
		}
		if (quitBtn->IsCursorOn()) {
			quitBtnPressed = true;
		}
	}
	if (InputMgr::GetMouseButtonUp(sf::Mouse::Left)) {
		if (startBtn->IsCursorOn()) {
			startBtnPressed = false;
			SCENE_MGR.ChangeScene(SceneIds::Select);
		}
		else if (quitBtn->IsCursorOn()) {
			quitBtnPressed = false;
			FRAMEWORK.GetWindow().close();
		}
		else {
			startBtnPressed = false;
			quitBtnPressed = false;
		}
	}
}

void SceneTitle::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
