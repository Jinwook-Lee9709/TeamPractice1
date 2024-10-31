#include "stdafx.h"
#include "SelectPlate.h"

SelectPlate::SelectPlate(const std::string& texId, const std::string& fontId, int player)
	:SpriteGo(texId), fontId(fontId), playerNum(player)
{
}



void SelectPlate::Reset()
{
	SpriteGo::Reset();
	Selected = false;
	text.setFont(FONT_MGR.Get(fontId));
	spriteSelect.setTexture(TEXTURE_MGR.Get("graphics/selected.png"));
	spriteSelect.setScale(0.2f, 0.2f);
	if(playerNum == 1){
		for (int i = 0; i < 3; i++) {
			Key[i].setString(p1Key[i]);
			Key[i].setFont(FONT_MGR.Get(fontId));
			Key[i].setCharacterSize(fontSize);
			Utils::SetOrigin(Key[i], Origins::MC);
		}
		text.setString("P1");
		text.setFont(FONT_MGR.Get(fontId));
		text.setCharacterSize(fontSize);
		Utils::SetOrigin(text, Origins::MC);
	}
	else if (playerNum == 2) {
		for (int i = 0; i < 3; i++) {
			Key[i].setString(p2Key[i]);
			Key[i].setFont(FONT_MGR.Get(fontId));
			Key[i].setCharacterSize(fontSize);
			Utils::SetOrigin(Key[i], Origins::MC);
		}
		text.setString("P2");
		text.setFont(FONT_MGR.Get(fontId));
		text.setCharacterSize(fontSize);
		Utils::SetOrigin(text, Origins::MC);
	}
	SetPosition(sprite.getPosition());

}

void SelectPlate::SetPosition(const sf::Vector2f& pos)
{
	SpriteGo::SetPosition(pos);
	sf::Vector2f spritePos = sprite.getPosition();
	sf::Vector2f horizontalGap = { sprite.getLocalBounds().width + 100.f, 0.f };
	sf::Vector2f verticalGap = { 0.f ,sprite.getLocalBounds().height + 50.f };
	Key[0].setPosition(spritePos - horizontalGap);
	Key[1].setPosition(spritePos + horizontalGap);
	Key[2].setPosition(spritePos + verticalGap);
	spriteSelect.setPosition(spritePos + sf::Vector2f(50.f, 50.f));
	text.setPosition(spritePos - verticalGap);
}

void SelectPlate::SetScale(const sf::Vector2f& scale)
{
	SpriteGo::SetScale(scale);
	SetPosition(sprite.getPosition());
}

void SelectPlate::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
	window.draw(text);
	for (auto it : Key) {
		window.draw(it);
	}
	if (Selected) {
		window.draw(spriteSelect);
	}
}

void SelectPlate::SetSelect(bool selected)
{
	Selected = selected;
}
