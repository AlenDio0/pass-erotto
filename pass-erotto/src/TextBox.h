#pragma once
#include <SFML\Graphics.hpp>
#include <sstream>

class TextBox
{
public:
	TextBox() = default;
	TextBox(sf::Font& font, const uint16_t& charSize, const sf::Color& color, const uint16_t& limit);

	void setPosition(const sf::Vector2f& position);
	void setLimit(const uint16_t& limit);
	void setSelected(const bool& selected);

	void typedOn(sf::Event input);

	void update();

	void render(sf::RenderWindow* target) const;
private:
	sf::Text m_Text;
	sf::RectangleShape m_Background;
	std::ostringstream m_Buff;
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

	void inputLogic(const int& typedChar);
};