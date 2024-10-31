#pragma once
#include "SpriteGo.h"
class SelectPlate : public SpriteGo
{
private:
	int playerNum;
	sf::Text text;
	sf::Text Key[3]; // 0 = Left, 1 = Right, 2 = Middle
	std::string p1Key[3] = {"A", "D", "Z"};
	std::string p2Key[3] = { "LEFT", "RIGHT", "Enter" };
	std::string fontId;

	int fontSize = 60;
public:
	SelectPlate(const std::string& texId = "", const std::string& fontId = "", int player = 0);
	~SelectPlate() = default;


	void Reset() override;
	void SetPosition(const sf::Vector2f& pos) override;
	void SetScale(const sf::Vector2f& scale) override;
	void Draw(sf::RenderWindow& window) override;
};

