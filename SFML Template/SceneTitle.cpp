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

	auto* obj = AddGo(new SpriteGo("graphics/titlebackground.png"));
	title = AddGo(new SpriteGo("graphics/title.png"));
	startBtn = AddGo(new Button("fonts/KOMIKAP_.ttf"));
	quitBtn = AddGo(new Button("fonts/KOMIKAP_.ttf"));

	Scene::Init();

	obj->sortingLayer = SortingLayers::Background;
	obj->sortingOrder = -1;
	obj->SetOrigin(Origins::MC);
	obj->SetPosition({ 1920 / 2, 1080 / 2 });

	title->sortingLayer = SortingLayers::UI;
	title->sortingOrder = 0;
	title->SetOrigin(Origins::MC);
	title->SetScale(titleScale);
	title->SetPosition({ 1920 / 2, 500 / 2 });

	startBtn->sortingLayer = SortingLayers::UI;
	startBtn->sortingOrder = 1;
	startBtn->SetPosition({ 1920.f * 0.5f, 1080.f * 0.5f });
	startBtn->SetFontSize(100);
	startBtn->SetOrigin(Origins::MC);
	startBtn->SetText("START");

	quitBtn->sortingLayer = SortingLayers::UI;
	quitBtn->sortingOrder = 1;
	quitBtn->SetPosition({ 1920.f * 0.5f, 1080.f * 0.5f + 200.f });
	quitBtn->SetFontSize(100);
	quitBtn->SetOrigin(Origins::MC);
	quitBtn->SetText("QUIT");




	
}

void SceneTitle::Enter()
{
	titleScale = { 0.5f, 0.5f };
	TEXTURE_MGR.Load("graphics/title.png");
	TEXTURE_MGR.Load("graphics/titlebackground.png");
	FONT_MGR.Load("fonts/KOMIKAP_.ttf");

	Scene::Enter();
}

void SceneTitle::Exit()
{

	Scene::Exit();

	TEXTURE_MGR.Unload("graphics/title.png");
	FONT_MGR.Unload("fonts/KOMIKAP_.ttf");
}

void SceneTitle::Update(float dt)
{
	Scene::Update(dt);
	TitleMove(dt);
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

void SceneTitle::TitleMove(float dt)
{
	if (titleScale.x > 0.52f) {
		scaleMultiply = -0.02f;
	}
	else if(titleScale.x < 0.5){
		scaleMultiply = 0.02f;
	}
	titleScale.x += scaleMultiply * dt;
	titleScale.y += scaleMultiply * dt;

	title->SetScale(titleScale);
}
