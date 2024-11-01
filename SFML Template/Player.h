#pragma once
#include "GameObject.h"

class SceneDev1;
class VsScene;

class Player : public GameObject
{
protected:
	sf::Sound sfxChop;


	sf::Sprite spritePlayer;
	sf::Sprite spriteAxe;
	sf::Sprite spriteRip;

	std::string sbIdChop = "sound/chop.wav";
	std::string texIdPlayer = "graphics/player.png";
	std::string texIdAxe = "graphics/axe.png";
	std::string texIdRip = "graphics/rip.png";

	Sides side = Sides::Right;

	sf::Vector2f localPosPlayer[3] = { { -300.f, 0.f },  { 300.f, 0.f },  { 0.f, 0.f } };
	sf::Vector2f localPosAxe = { 0.f, -70.f };
	sf::Vector2f localRipAxe = { 0.f, 0.f };

	sf::Vector2f originAxe = { -65.f, 0.f };

	bool isAlive = true;
	bool isChppoing = false;

	int HP = 3;

	int P1HP = 3;
	int P2HP = 3;

	ChkPlayer chkP = ChkPlayer::FirstP;

	Scene* sceneGame = nullptr;

public:
	Player(const std::string& name = "");
	virtual ~Player() = default;

	Sides GetSide() const { return side; }
	void SetSide(Sides s);
	void OnDie();
	bool GetIsAlive() const { return isAlive; };

	void SetPosition(const sf::Vector2f& pos) override;
	void SetScale(const sf::Vector2f& scale) override;
	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;
	void SetPlayerTextId(const std::string& texId);

	void Init() override;
	void Release() override;
	void Reset()  override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window)  override;

	void SetChkP(ChkPlayer chk);
	void PlayFirstP(float dt);
	void PlaySecondP(float dt);

	void SetSceneGame(Scene* scene);

	int GetHp() { return HP; }
	int GetP1HP() { return P1HP; }
	int GetP2HP() { return P2HP; }

	void Hit() { HP--; }
	void HitP1() { P1HP--; }
	void HitP2() { P2HP--; }

	void Recovery() { HP++; }
	void RecoveryP1();
	void RecoveryP2();
};

