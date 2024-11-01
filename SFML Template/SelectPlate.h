#pragma once
#include "SpriteGo.h"
class SelectPlate : public SpriteGo
{
private:
	int playerNum;
	sf::Sprite spriteSelect;
	sf::Text text;
	sf::Sprite Key[3]; // 0 = Left, 1 = Right, 2 = Middle
	std::string p1Key[3] = {"graphics/keyA.png", "graphics/keyD.png", "graphics/keyZ.png"};
	std::string p2Key[3] = { "graphics/keyLeft.png", "graphics/keyRight.png", "graphics/keyEnter.png" };
	std::string fontId;

	int fontSize = 60;
	bool Selected;
public:
	SelectPlate(const std::string& texId = "", const std::string& fontId = "", int player = 0);
	~SelectPlate() = default;


	void Reset() override;
	void SetPosition(const sf::Vector2f& pos) override;
	void SetScale(const sf::Vector2f& scale) override;
	void Draw(sf::RenderWindow& window) override;
	void SetSelect(bool selected);
};

