#pragma once
#include "SpriteGo.h"
class SpriteButton :
    public SpriteGo
{
private:
	sf::Color ColorPressed = sf::Color(80, 80, 80, 255);
	sf::Color ColorIdle = sf::Color(200, 200, 200, 255);
	sf::Color ColorHover = sf::Color(255, 255, 255, 255);
public:
	SortingLayers sortingLayer = SortingLayers::Default;
	int sortingOrder = 0;
	SpriteButton(const std::string& texId = "", const std::string& name = "");
	virtual ~SpriteButton() = default;

	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;


	bool IsCursorOn();
};

	