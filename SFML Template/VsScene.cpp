#include "stdafx.h"
#include "VsScene.h"
#include "SpriteGo.h"
#include "CloudGo.h"
#include "Tree.h"
#include "Player.h"
#include "TextGo.h"
#include "UiScore.h"
#include "UiTimebar.h"

VsScene::VsScene() : Scene(SceneIds::VsScene)
{
}

void VsScene::Init()
{
	std::cout << "VsScene::Init()" << std::endl;

	GameObject* obj = AddGo(new SpriteGo("graphics/background.png","background"));
	obj->sortingLayer = SortingLayers::Background;
	obj->sortingOrder = -1;
	obj->SetOrigin(Origins::MC);
	obj->SetPosition({ 1920 / 2, 1080 / 2 });

	for (int i = 0; i < 3; ++i)
	{
		CloudGo* cloud = AddGo(new CloudGo("graphics/cloud.png"));
		cloud->sortingLayer = SortingLayers::Background;
		cloud->sortingOrder = 0;
	}

	TEXTURE_MGR.Load("graphics/tree.png");
	TEXTURE_MGR.Load("graphics/branch.png");
	TEXTURE_MGR.Load("graphics/player.png");
	TEXTURE_MGR.Load("graphics/rip.png");
	TEXTURE_MGR.Load("graphics/axe.png");
	TEXTURE_MGR.Load("graphics/heart.png");

	tree = AddGo(new Tree("Tree"));
	player = AddGo(new Player("Player"));
	
	tree2 = AddGo(new Tree("Tree2"));
	player2 = AddGo(new Player("Player2"));
	

	for (int i = 0; i < 3; i++)
	{
		spriteHeartP1[i] = AddGo(new SpriteGo("graphics/heart.png"));
		spriteHeartP2[i] = AddGo(new SpriteGo("graphics/heart.png"));

		spriteHeartP1[i]->sortingLayer = SortingLayers::Foreground;
		spriteHeartP2[i]->sortingLayer = SortingLayers::Foreground;
	}

	centerMsg = AddGo(new TextGo("fonts/KOMIKAP_.ttf", "Center Message"));
	centerMsg->sortingLayer = SortingLayers::UI;

	uiScore = AddGo(new UiScore("fonts/KOMIKAP_.ttf", "Ui Score"));
	
	uiScore2 = AddGo(new UiScore("fonts/KOMIKAP_.ttf", "Ui Score2"));
	
	uiTimer = AddGo(new UiTimebar("Ui Timer"));

	Scene::Init();

	tree->SetPosition({ 1920.f / 3.5, 1080.f - 200.f });
	tree->SetScale({ 0.7f, 1.f });
	tree->SetModSize({ 0.5f, 0.5f });
	player->SetPosition({ 1920.f / 3.5, 1080.f - 200.f });
	player->SetChkP(ChkPlayer::FirstP);
	player->SetPlayerTextId(VAR.Player1TexId);

	tree2->SetPosition({ 1920.f / 1.5, 1080.f - 200.f });
	tree2->SetScale({ 0.7f, 1.f });
	tree2->SetModSize({ 0.5f, 0.5f });
	player2->SetPosition({ 1920.f / 1.5, 1080.f - 200.f });
	player2->SetChkP(ChkPlayer::SecondP);
	player2->SetPlayerTextId(VAR.Player2TexId);

	sf::Vector2f newHeartP1Pos = sf::Vector2f({50.f, 1080.f / 2 + 100.f});

	for (int i = 0; i < 3; i++)
	{
		spriteHeartP1[i]->SetOrigin(Origins::MC);
		spriteHeartP1[i]->SetScale({ 0.1f, 0.1f });
		spriteHeartP1[i]->SetPosition({ newHeartP1Pos.x, newHeartP1Pos.y });
		
		spriteHeartP2[i]->SetOrigin(Origins::MC);
		spriteHeartP2[i]->SetScale({ 0.1f, 0.1f });
		spriteHeartP2[i]->SetPosition({ newHeartP1Pos.x + 1800.f, newHeartP1Pos.y });

		newHeartP1Pos.y += 100.f;
	}

	centerMsg->text.setCharacterSize(100);
	centerMsg->text.setFillColor(sf::Color::White);
	centerMsg->SetPosition({ 1920.f / 2.f, 1080.f / 2.f });

	uiScore->text.setCharacterSize(75);
	uiScore->text.setFillColor(sf::Color::White);
	uiScore->SetPosition({ 30.f, 30.f });
	uiScore->SetString("1P Score: ");

	uiScore2->text.setCharacterSize(75);
	uiScore2->text.setFillColor(sf::Color::White);
	uiScore2->SetOrigin(Origins::TR);
	uiScore2->SetPosition({ 1890.f, 30.f });
	uiScore2->SetString("2P Score: ");

	uiTimer->Set({ 500.f, 100.f }, sf::Color::Red);
	//uiTimer->Set({ 600.f, 80.f }, sf::Color::Red);
	uiTimer->SetOrigin(Origins::ML);
	uiTimer->SetPosition({ 1920.f / 2.f - 350.f, 1080.f - 125.f });
}

void VsScene::Enter()
{
	TEXTURE_MGR.Load(VAR.BackGroundTexId);
	TEXTURE_MGR.Load("graphics/cloud.png");
	TEXTURE_MGR.Load("graphics/tree.png");
	TEXTURE_MGR.Load("graphics/branch.png");
	TEXTURE_MGR.Load("graphics/log.png");
	TEXTURE_MGR.Load(VAR.Player1TexId);
	TEXTURE_MGR.Load(VAR.Player2TexId);
	TEXTURE_MGR.Load("graphics/rip.png");
	TEXTURE_MGR.Load("graphics/axe.png");
	TEXTURE_MGR.Load("graphics/heart.png");
	FONT_MGR.Load("fonts/KOMIKAP_.ttf");
	SOUNDBUFFER_MGR.Load("sound/chop.wav");
	SOUNDBUFFER_MGR.Load(sbIdDeath);
	SOUNDBUFFER_MGR.Load(sbIdTimeOut);

	auto it = dynamic_cast<SpriteGo*>(FindGo("background"));
	it->ChangeTexture(VAR.BackGroundTexId);

	sfxDeath.setBuffer(SOUNDBUFFER_MGR.Get(sbIdDeath));
	sfxTimeOut.setBuffer(SOUNDBUFFER_MGR.Get(sbIdTimeOut));

	player->SetPlayerTextId(VAR.Player1TexId);
	player2->SetPlayerTextId(VAR.Player2TexId);


	player->SetSceneGame(this);
	player2->SetSceneGame(this);

	Scene::Enter();

	SetStatus(Status::Awake);
}

void VsScene::Exit()
{
	std::cout << "VsScene::Exit()" << std::endl;

	player->SetSceneGame(nullptr);
	tree->ClearEffectLog();

	player2->SetSceneGame(nullptr);
	tree2->ClearEffectLog();

	Scene::Exit();

	TEXTURE_MGR.Unload("graphics/cloud.png");
	TEXTURE_MGR.Unload(VAR.BackGroundTexId);
	TEXTURE_MGR.Unload("graphics/tree.png");
	TEXTURE_MGR.Unload("graphics/branch.png");
	TEXTURE_MGR.Unload("graphics/log.png");
	TEXTURE_MGR.Unload("graphics/player.png");
	TEXTURE_MGR.Unload("graphics/rip.png");
	TEXTURE_MGR.Unload("graphics/axe.png");
	TEXTURE_MGR.Unload("graphics/heart.png");
	FONT_MGR.Unload("fonts/KOMIKAP_.ttf");
	SOUNDBUFFER_MGR.Unload("sound/chop.wav");
	SOUNDBUFFER_MGR.Unload("sound/death.wav");
	SOUNDBUFFER_MGR.Unload("sound/out_of_time.wav");

}

void VsScene::Update(float dt)
{
	Scene::Update(dt);


	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		SCENE_MGR.ChangeScene(SceneIds::Dev1);
	}

	switch (currentStatus)
	{
	case VsScene::Status::Awake:
		UpdateAwake(dt);
		break;
	case VsScene::Status::Game:
		UpdateGame(dt);
		break;
	case VsScene::Status::GameOver:
		UpdateGameOver(dt);
		break;
	case VsScene::Status::Pause:
		UpdatePause(dt);
		break;
	}
}

void VsScene::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void VsScene::SetCenterMessage(const std::string& msg)
{
	centerMsg->text.setString(msg);
	centerMsg->SetOrigin(Origins::MC);
}

void VsScene::SetVisibleCenterMessage(bool visible)
{
	centerMsg->SetActive(visible);
}

void VsScene::SetScore(int score)
{
	this->score = score;
	uiScore->SetScore(this->score);
}

void VsScene::SetScore2P(int score)
{
	this->score2 = score;
	uiScore2->SetScore(this->score2);
}

void VsScene::SetStatus(Status newStatus)
{
	Status prevStatus = currentStatus;
	currentStatus = newStatus;

	switch (currentStatus)
	{
	case VsScene::Status::Awake:
		FRAMEWORK.SetTimeScale(0.f);
		SetVisibleCenterMessage(true);
		SetCenterMessage("Press Enter To Start!!");
		score = 0;
		score2 = 0;
		timer = gameTime;
		SetScore(score);
		SetScore2P(score2);
		uiTimer->SetValue(1.f);
		break;
	case VsScene::Status::Game:
		if (prevStatus == Status::GameOver)
		{
			score = 0;
			score2 = 0;
			timer = gameTime;

			SetScore(score);
			SetScore2P(score2);
			uiTimer->SetValue(1.f);

			player->Reset();
			tree->Reset();
			player2->Reset();
			tree2->Reset();
		}
		FRAMEWORK.SetTimeScale(1.f);
		SetVisibleCenterMessage(false);
		break;
	case VsScene::Status::GameOver:
		FRAMEWORK.SetTimeScale(0.f);
		SetVisibleCenterMessage(true);
		break;
	case VsScene::Status::Pause:
		FRAMEWORK.SetTimeScale(0.f);
		SetVisibleCenterMessage(true);
		SetCenterMessage("PAUSE! ESC TO RESUME!");
		break;
	}
}

void VsScene::UpdateAwake(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		SetStatus(Status::Game);
	}
}

void VsScene::UpdateGame(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
	{
		SetStatus(Status::Pause);
		return;
	}

	timer = Utils::Clamp(timer - dt, 0.f, gameTime);
	uiTimer->SetValue(timer / gameTime);
	if (timer <= 0.f)
	{
		sfxTimeOut.play();

		//player->OnDie();
		CheckWinner();
		SetStatus(Status::GameOver);
		return;
	}
}

void VsScene::UpdateGameOver(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		SetStatus(Status::Game);
	}
}

void VsScene::UpdatePause(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
	{
		SetStatus(Status::Game);
	}
}

void VsScene::CheckWinner()
{
	if (player2->GetIsAlive() && player->GetIsAlive())
	{
		if (score > score2)
			SetCenterMessage("1Player Win!!!");
		else if (score < score2)
			SetCenterMessage("2Player Win!!!");
		else
			SetCenterMessage("Draw!!!");
	} 
	else
	{
		player->GetIsAlive() ? SetCenterMessage("1Player Win!!!") : SetCenterMessage("2Player Win!!!");
	}
}	

void VsScene::OnChop(Sides side, ChkPlayer chk)
{
	if (chk == ChkPlayer::FirstP)
	{
		Sides branchSide = Sides::None;
		if (timer > 0 && player->GetIsAlive() && player2->GetIsAlive())
		{
			branchSide = tree->Chop(side);
		}
		if (player->GetSide() == branchSide)
		{
			player->HitP1();
			spriteHeartP1[player->GetP1HP()]->SetActive(false);
			if(player->GetP1HP() == 0)
			{
				sfxDeath.play();

				player->OnDie();
				CheckWinner();
				SetStatus(Status::GameOver);
			}
		}
		else
		{
			if (timer > 0 && player->GetIsAlive() && player2->GetIsAlive())
			{
				SetScore(score + 100);
			}
			//timer += 1.f;
		}
	}
	else if (chk == ChkPlayer::SecondP)
	{
		Sides branchSide = Sides::None;
		if (timer > 0 && player->GetIsAlive() && player2->GetIsAlive())
		{
			branchSide = tree2->Chop(side);
		}
		if (player2->GetSide() == branchSide)
		{
			player2->HitP2();
			spriteHeartP2[player2->GetP2HP()]->SetActive(false);
			if(player2->GetP2HP() == 0)
			{
				sfxDeath.play();

				player2->OnDie();
				CheckWinner();
				SetStatus(Status::GameOver);
			}
		}
		else
		{
			if (timer > 0 && player->GetIsAlive() && player2->GetIsAlive())
			{
				SetScore2P(score2 + 100);
			}
			
			//timer += 1.f;
		}
	}
}
