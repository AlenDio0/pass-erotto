#pragma once
#include <SFML\Graphics.hpp>

class TextButton
{
public:
	TextButton() = default;
	TextButton(sf::Font& font, const std::string& title, const uint16_t& charSize, const sf::Color& color = sf::Color::Black);

	sf::Text& getText();
	sf::RectangleShape& getBackground();

	void setPosition(const sf::Vector2f& position);
	void setHighlight(const bool& highlight);

	const bool& isCursorOn(const sf::WindowBase& window) const;

	void render(sf::RenderTarget* target) const;
private:
	sf::Text m_Text;
	sf::Color m_TextColor;

	sf::RectangleShape m_Background;

	sf::RectangleShape m_HighlightShape;
	bool m_Highlight = false;
};

