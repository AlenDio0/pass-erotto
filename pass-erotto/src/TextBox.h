#pragma once
#include <SFML\Graphics.hpp>
#include <sstream>

class TextBox
{
public:
	TextBox() = default;
	TextBox(sf::Font& font, const uint16_t& charSize, const sf::Color& color, const uint16_t& limit);

	sf::Text& getText();
	sf::RectangleShape& getBackground();
	const std::string& getBuff() const;

	void setPosition(const sf::Vector2f& position);
	void setLimit(const uint16_t& limit);
	void setPlaceHolder(const std::string& placeholder);
	void setSelected(const bool& selected);

	bool isCursorOn(const sf::WindowBase& window);

	void typedOn(sf::Event input);

	void update();

	void render(sf::RenderWindow* target) const;
private:
	sf::Text m_Text;
	sf::Color m_TextColor;

	sf::RectangleShape m_Background;

	std::ostringstream m_Buff;

	std::string m_PlaceHolderStr;

	bool m_IsSelected;
	unsigned int m_Limit;

	sf::Clock m_Blink;

	enum
	{
		DELETE_KEY = 8,
		ENTER_KEY = 13,
		ESCAPE_KEY = 27
	};

	bool isOverLimit() const;

	void togglePlaceHolder(const bool& hide);

	void inputLogic(const int& typedChar);
};