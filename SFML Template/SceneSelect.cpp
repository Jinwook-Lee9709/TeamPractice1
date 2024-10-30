#include "stdafx.h"
#include "SceneSelect.h"
#include "SpriteGo.h"
#include "Button.h"

SceneSelect::SceneSelect() : Scene(SceneIds::Select)
{

}

void SceneSelect::Init()
{
	FONT_MGR.Load("fonts/KOMIKAP_.ttf");

	auto* obj = AddGo(new SpriteGo("graphics/selectbackground.png"));
	singleBtn = AddGo(new Button("fonts/KOMIKAP_.ttf"));
	multiBtn = AddGo(new Button("fonts/KOMIKAP_.ttf"));

	Scene::Init();

	obj->sortingLayer = SortingLayers::Background;
	obj->sortingOrder = -1;
	obj->SetOrigin(Origins::MC);
	obj->SetPosition({ 1920 / 2, 1080 / 2 });

	singleBtn->sortingLayer = SortingLayers::UI;
	singleBtn->sortingOrder = 0;
	singleBtn->SetPosition({ 1920.f * 0.5f, 1080.f * 0.5f });
	singleBtn->SetFontSize(100);
	singleBtn->SetOrigin(Origins::MC);
	singleBtn->SetText("START");

	multiBtn->sortingLayer = SortingLayers::UI;
	multiBtn->sortingOrder = 0;
	multiBtn->SetPosition({ 1920.f * 0.5f, 1080.f * 0.5f + 200.f });
	multiBtn->SetFontSize(100);
	multiBtn->SetOrigin(Origins::MC);
	multiBtn->SetText("QUIT");

}

void SceneSelect::Enter()
{
	TEXTURE_MGR.Load("graphics/selectbackground.png");
	FONT_MGR.Load("fonts/KOMIKAP_.ttf");

	Scene::Enter();


}

void SceneSelect::Exit()
{
	Scene::Exit();

	TEXTURE_MGR.Unload("graphics/selectbackground.png");
	FONT_MGR.Unload("fonts/KOMIKAP_.ttf");
}

void SceneSelect::Update(float dt)
{
	Scene::Update(dt);
}

void SceneSelect::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
