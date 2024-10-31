#include "stdafx.h"
#include "SceneSelect.h"
#include "SpriteGo.h"
#include "SpriteButton.h"
#include "Button.h"
#include "SelectPlate.h"

SceneSelect::SceneSelect() : Scene(SceneIds::Select)
{

}

void SceneSelect::Init()
{
	FONT_MGR.Load("fonts/KOMIKAP_.ttf");

	auto* obj = AddGo(new SpriteGo("graphics/selectbackground.png"));
	single = AddGo(new SpriteButton("graphics/selectsingle.png"));
	multi = AddGo(new SpriteButton("graphics/selectmulti.png"));
	p1Plate = AddGo(new SelectPlate(characterTexId[0], "fonts/KOMIKAP_.ttf", 1));
	p2Plate = AddGo(new SelectPlate(characterTexId[0], "fonts/KOMIKAP_.ttf", 2));
	


	Scene::Init();

	obj->sortingLayer = SortingLayers::Background;
	obj->sortingOrder = -1;
	obj->SetOrigin(Origins::MC);
	obj->SetPosition({ 1920 / 2, 1080 / 2 });
	obj->SetBrightness(70);

	single->sortingLayer = SortingLayers::UI;
	single->sortingOrder = -1;
	single->SetOrigin(Origins::MC);
	single->SetScale({ 0.5f, 0.5f });
	single->SetPosition({ 1920 * 0.25f + 100.f, 1080 * 0.5f });

	multi->sortingLayer = SortingLayers::UI;
	multi->sortingOrder = -1;
	multi->SetOrigin(Origins::MC);
	multi->SetScale({ 0.5f, 0.5f });
	multi->SetPosition({ 1920 * 0.75f - 100.f, 1080 * 0.5f });

	p1Plate->sortingLayer = SortingLayers::UI;
	p1Plate->sortingOrder = -1;
	p1Plate->SetOrigin(Origins::MC);
	p1Plate->SetPosition({ 1920 * 0.25f + 100.f, 1080 * 0.5f });
	p1Plate->SetScale({ 1.5f, 1.5f });

	p1Plate->SetActive(false);

	p2Plate->sortingLayer = SortingLayers::UI;
	p2Plate->sortingOrder = -1;
	p2Plate->SetOrigin(Origins::MC);
	p2Plate->SetPosition({ 1920 * 0.75f - 100.f, 1080 * 0.5f });
	p2Plate->SetScale({ 1.5f, 1.5f });
	p2Plate->SetActive(false);

}

void SceneSelect::Enter()
{
	currentStatus = Status::SelectMode;
	p1SpriteIndex = p2SpriteIndex = 0;
	single->SetActive(true);
	multi->SetActive(true);

	TEXTURE_MGR.Load("graphics/selectbackground.png");
	TEXTURE_MGR.Load("graphics/selectsingle.png");
	TEXTURE_MGR.Load("graphics/selectmulti.png");
	TEXTURE_MGR.Load("graphics/player1.png");
	TEXTURE_MGR.Load("graphics/player2.png");
	TEXTURE_MGR.Load("graphics/player3.png");
	FONT_MGR.Load("fonts/KOMIKAP_.ttf");

	Scene::Enter();


}

void SceneSelect::Exit()
{
	Scene::Exit();

	TEXTURE_MGR.Unload("graphics/selectbackground.png");
	TEXTURE_MGR.Unload("graphics/selectsingle.png");
	TEXTURE_MGR.Unload("graphics/selectmulti.png");
	TEXTURE_MGR.Unload("graphics/player1.png");
	TEXTURE_MGR.Unload("graphics/player2.png");
	TEXTURE_MGR.Unload("graphics/player3.png");
	FONT_MGR.Unload("fonts/KOMIKAP_.ttf");
}

void SceneSelect::Update(float dt)
{
	if (prevStatus != Status::None) {
		switch (prevStatus)
		{
		case SceneSelect::Status::SelectMode:
			if (currentStatus == Status::SelectCharacter)
			{
				if (VAR.SelectedPlayMode == PlayMode::Single) {
					p1Plate->SetActive(true);
					p1Plate->SetPosition({1920.f * 0.5f, 1080.f * 0.5f});
				}
				else {
					p1Plate->SetActive(true);
					p2Plate->SetActive(true);
				}
			
			}
			break;
		default:
			break;
		}
		prevStatus = Status::None;
	}
	switch (currentStatus) {
	case Status::SelectMode:
	{
		UpdateSelectMode();
		break;
	}
	case Status::SelectCharacter:
	{
		UpdateSelectCharacter();
		break;
	}
	}


	Scene::Update(dt);
}

void SceneSelect::UpdateSelectMode()
{
	if (InputMgr::GetMouseButtonDown(sf::Mouse::Left)) {
		if (single->IsCursorOn()) {
			singlePressed = true;
		}
		if (multi->IsCursorOn()) {
			multiPressed = true;
		}
	}
	if (InputMgr::GetMouseButtonUp(sf::Mouse::Left)) {
		if (single->IsCursorOn()) {
			singlePressed = false;
			single->SetActive(false);
			multi->SetActive(false);
			VAR.SelectedPlayMode = PlayMode::Single;
			prevStatus = Status::SelectMode;
			currentStatus = Status::SelectCharacter;
		}
		else if (multi->IsCursorOn()) {
			multiPressed = false;
			single->SetActive(false);
			multi->SetActive(false);
			VAR.SelectedPlayMode = PlayMode::Multi;
			prevStatus = Status::SelectMode;
			currentStatus = Status::SelectCharacter;
		}
		else {
			singlePressed = false;
			multiPressed = false;
		}
	}
}

void SceneSelect::UpdateSelectCharacter()
{
	if (p1Selected && p2Selected) {
		VAR.Player1TexId = characterTexId[p1SpriteIndex];
		VAR.Player2TexId = characterTexId[p2SpriteIndex];
		SCENE_MGR.ChangeScene(SceneIds::SelectStage);
	}
	
	if (!p1Selected) {
		if (InputMgr::GetKeyDown(sf::Keyboard::A)) {
			if (p1SpriteIndex == 0) {
				p1SpriteIndex = 2;
			}
			else {
				p1SpriteIndex--;
			}
			p1Plate->ChangeTexture(characterTexId[p1SpriteIndex]);
		}
		if (InputMgr::GetKeyDown(sf::Keyboard::D)) {
			if (p1SpriteIndex == 2) {
				p1SpriteIndex = 0;
			}
			else {
				++p1SpriteIndex;
			}
			p1Plate->ChangeTexture(characterTexId[p1SpriteIndex]);
		}
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Z)) {
		p1Selected = !p1Selected;
	}
	if (!p2Selected) {
		if (InputMgr::GetKeyDown(sf::Keyboard::Left)) {
			if (p2SpriteIndex == 2) {
				p2SpriteIndex = 0;
			}
			else {
				++p2SpriteIndex;
			}
			p2Plate->ChangeTexture(characterTexId[p2SpriteIndex]);
		}
		if (InputMgr::GetKeyDown(sf::Keyboard::Right)) {
			if (p2SpriteIndex == 0) {
				p2SpriteIndex = 2;
			}
			else {
				p2SpriteIndex--;
			}
			p2Plate->ChangeTexture(characterTexId[p2SpriteIndex]);
		}
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Enter)) {
		p2Selected = !p2Selected;
	}
}

void SceneSelect::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
