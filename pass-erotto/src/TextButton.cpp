#include "TextButton.h"

TextButton::TextButton(sf::Font& font, const std::string& title, const uint16_t& charSize, const sf::Color& color)
	: m_TextColor(color)
{
	m_Text.setFont(font);
	m_Text.setString(title);
	m_Text.setCharacterSize(charSize);
	m_Text.setFillColor(m_TextColor);

	m_Background.setSize({ m_Text.getGlobalBounds().getSize().x + 10.f, (float)(charSize * 1.5f) });

	m_Background.setOutlineThickness(2.f);
	m_Background.setOutlineColor(sf::Color(100, 100, 100));
	m_Background.setFillColor(sf::Color::White);

	m_HighlightShape.setSize(m_Background.getSize());
	m_HighlightShape.setOutlineThickness(2.f);
	m_HighlightShape.setOutlineColor(sf::Color::White);
	m_HighlightShape.setFillColor(sf::Color(128, 128, 128, 96));

	setPosition({ 0.f, 0.f });
}

sf::Text& TextButton::getText()
{
	return m_Text;
}

sf::RectangleShape& TextButton::getBackground()
{
	return m_Background;
}

void TextButton::setPosition(const sf::Vector2f& position)
{
	m_Background.setPosition(position);
	m_HighlightShape.setPosition(position);
	m_Text.setPosition(position.x + 5.f, position.y);
}

void TextButton::setHighlight(const bool& highlight)
{
	m_Highlight = highlight;
}

const bool& TextButton::isCursorOn(const sf::WindowBase& window)
{
	return m_Background.getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(window));
}

void TextButton::render(sf::RenderTarget* target) const
{
	target->draw(m_Background);
	target->draw(m_Text);

	if (m_Highlight)
	{
		target->draw(m_HighlightShape);
	}
}
