#include "stdafx.h"
#include "Button.h"

Button::Button(const std::string& fontId, const std::string& name)
	:GameObject(name), fontId(fontId), pressed(false)
{
	text.setFont(FONT_MGR.Get(fontId));
	rect.setSize({ 370.f, 180.f });
}

void Button::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	rect.setPosition(position);
	text.setPosition(position + sf::Vector2f(0.f, -10.f));
}

void Button::SetScale(const sf::Vector2f& scale)
{
	this->scale = scale;
	rect.setScale(scale);
	text.setScale(scale);
}

void Button::Reset()
{
	rect.setFillColor(sf::Color::Transparent);
	text.setFillColor(ColorIdle);
}

void Button::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(rect, originPreset);
	}
}

void Button::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	rect.setOrigin(origin);
}

void Button::Update(float dt)
{
	sf::Vector2f mousePos =
	{ (float)InputMgr::GetMousePosition().x, (float)InputMgr::GetMousePosition().y };
	if (rect.getGlobalBounds().contains(mousePos)) {
		if (InputMgr::GetMouseButtonDown(sf::Mouse::Left) || InputMgr::GetMouseButton(sf::Mouse::Left)) {
			pressed = true;
			text.setFillColor(ColorPressed);
		}
		else if (InputMgr::GetMouseButtonUp(sf::Mouse::Left)) {
			pressed = false;
			text.setFillColor(ColorHover);
		}
		else {
			text.setFillColor(ColorHover);
		}
	}
	else {
		pressed = false;
		text.setFillColor(ColorIdle);
	}

}

void Button::SetText(const sf::String& str)
{
	text.setString(str);
	Utils::SetOrigin(text, Origins::MC);
	SetPosition(position);
}

void Button::SetFontSize(int size)
{
	text.setCharacterSize(size);

}



void Button::Draw(sf::RenderWindow& window)
{
	window.draw(rect);
	window.draw(text);
}
