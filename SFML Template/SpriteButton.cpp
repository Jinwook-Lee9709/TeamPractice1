#include "stdafx.h"
#include "SpriteButton.h"

SpriteButton::SpriteButton(const std::string& texId, const std::string& name)
	:SpriteGo(texId)
{
}

void SpriteButton::Reset()
{
	SpriteGo::Reset();
}

void SpriteButton::Update(float dt)
{
	sf::Vector2f mousePos =
	{ (float)InputMgr::GetMousePosition().x, (float)InputMgr::GetMousePosition().y };
	if (sprite.getGlobalBounds().contains(mousePos)) {
		if (InputMgr::GetMouseButtonDown(sf::Mouse::Left) || InputMgr::GetMouseButton(sf::Mouse::Left)) {
			sprite.setColor(ColorPressed);
		}
		else if (InputMgr::GetMouseButtonUp(sf::Mouse::Left)) {
			sprite.setColor(ColorHover);
		}
		else {
			sprite.setColor(ColorHover);
		}
	}
	else {
		sprite.setColor(ColorIdle);
	}
}

void SpriteButton::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}

bool SpriteButton::IsCursorOn()
{
	return sprite.getGlobalBounds().contains(sf::Vector2f{(float) InputMgr::GetMousePosition().x, (float)InputMgr::GetMousePosition().y });
}
