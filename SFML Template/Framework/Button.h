#pragma once
class Button: public GameObject
{
private:
	std::string fontId;
	
	sf::Color ColorPressed = sf::Color(80, 80, 80, 255);
	sf::Color ColorIdle = sf::Color(200, 200, 200, 255);
	sf::Color ColorHover = sf::Color(255, 255, 255, 255);

	sf::RectangleShape rect;
	sf::Text text;


public:

	SortingLayers sortingLayer = SortingLayers::Default;
	int sortingOrder = 0;
	Button(const std::string& fontId = "", const std::string& name = "");
	virtual ~Button() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetScale(const sf::Vector2f& scale)override;
	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;


	void SetText(const sf::String& str);
	void SetFontSize(int size);

	bool IsCursorOn();



};

