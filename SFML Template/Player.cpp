#include "stdafx.h"
#include "Player.h"
#include "SceneDev1.h"	
#include "VsScene.h"

Player::Player(const std::string& name) : GameObject(name)
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;
}

void Player::SetSide(Sides s)
{
	side = s;

	if (side == Sides::Left)
	{
		SetScale({ -1.f, 1.f });
	}
	else if (side == Sides::Right)
	{
		SetScale({ 1.f, 1.f });
	}

	sf::Vector2f newPos = position + localPosPlayer[(int)s];
	spritePlayer.setPosition(newPos);
	spriteAxe.setPosition(newPos + localPosAxe);
	spriteRip.setPosition(newPos + localRipAxe);
}

void Player::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	SetSide(side);
}

void Player::OnDie()
{
	isAlive = false;
	isChppoing = false;


}

void Player::SetScale(const sf::Vector2f& scale)
{
	this->scale = scale;
	spritePlayer.setScale(this->scale);

	sf::Vector2f axeScale = this->scale;
	axeScale.x *= -1.f;
	spriteAxe.setScale(axeScale);

	sf::Vector2f axeRip = this->scale;
	axeRip.x = abs(axeScale.x);
	spriteRip.setScale(axeRip);
}

void Player::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (preset != Origins::Custom)
	{
		origin = Utils::SetOrigin(spritePlayer, preset);
	}
}

void Player::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	spritePlayer.setOrigin(origin);
}

void Player::SetPlayerTextId(const std::string& texId)
{
	texIdPlayer = texId;
}

void Player::Init()
{
	spritePlayer.setTexture(TEXTURE_MGR.Get(texIdPlayer));
	SetOrigin(Origins::BC);

	spriteAxe.setTexture(TEXTURE_MGR.Get(texIdAxe));
	spriteAxe.setOrigin(originAxe);

	spriteRip.setTexture(TEXTURE_MGR.Get(texIdRip));
	Utils::SetOrigin(spriteRip, Origins::BC);
}

void Player::Reset()
{
	sfxChop.setBuffer(SOUNDBUFFER_MGR.Get(sbIdChop));

	spritePlayer.setTexture(TEXTURE_MGR.Get(texIdPlayer));
	spriteAxe.setTexture(TEXTURE_MGR.Get(texIdAxe));
	spriteRip.setTexture(TEXTURE_MGR.Get(texIdRip));

	isAlive = true;
	isChppoing = false;
	SetPosition(position);
	SetScale({ 1.f, 1.f });
	SetSide(Sides::Right);

	HP = 3;
	P1HP = 3;
	P2HP = 3;
}


void Player::Release()
{
}


void Player::Update(float dt)
{
	if (!isAlive)
		return;
	if (chkP == ChkPlayer::FirstP)
		PlayFirstP(dt);
	else if (chkP == ChkPlayer::SecondP)
		PlaySecondP(dt);
}

void Player::Draw(sf::RenderWindow& window)
{
	if (isAlive)
	{
		window.draw(spritePlayer);
		if (isChppoing)
		{
			window.draw(spriteAxe);
		}
	}
	else
	{
		window.draw(spriteRip);
	}
}

void Player::SetChkP(ChkPlayer chk)
{
	chkP = chk;
}

void Player::PlayFirstP(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::A))
	{
		isChppoing = true;
		SetSide(Sides::Left);
		sceneGame->OnChop(Sides::Left, chkP);
		sfxChop.play();
	}

	if (InputMgr::GetKeyUp(sf::Keyboard::A))
	{
		isChppoing = false;
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::D))
	{
		isChppoing = true;
		SetSide(Sides::Right);
		sceneGame->OnChop(Sides::Right, chkP);
	}

	if (InputMgr::GetKeyUp(sf::Keyboard::D))
	{
		isChppoing = false;
	}
}

void Player::PlaySecondP(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Left))
	{
		isChppoing = true;
		SetSide(Sides::Left);
		sceneGame->OnChop(Sides::Left, chkP);
		sfxChop.play();
	}

	if (InputMgr::GetKeyUp(sf::Keyboard::Left))
	{
		isChppoing = false;
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Right))
	{
		isChppoing = true;
		SetSide(Sides::Right);
		sceneGame->OnChop(Sides::Right, chkP);
	}

	if (InputMgr::GetKeyUp(sf::Keyboard::Right))
	{
		isChppoing = false;
	}
}

void Player::SetSceneGame(Scene* scene)
{
	sceneGame = scene;
}

void Player::RecoveryP1()
{
	if(P1HP < 3)
	{
		P1HP++;
	}
}

void Player::RecoveryP2()
{
	if (P2HP < 3)
	{
		P2HP++;
	}
}
