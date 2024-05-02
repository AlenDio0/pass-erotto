#include "Notify.h"

Notify::Notify(sf::Font& font, const sf::Vector2f& size, const std::string& header)
	: m_Background(size), m_TextHeader(header, font, 20u), m_TextContents("Contents", font, 20u), m_Active(false)
{
	m_Background.setOutlineThickness(2.f);
	m_Background.setOutlineColor(sf::Color(128, 128, 128));

	m_TextHeader.setFillColor(sf::Color::Black);

	m_TextContents.setFillColor(sf::Color::Black);
}

std::unordered_map<uint8_t, TextButton>& Notify::getButtons()
{
	return m_Buttons;
}


void Notify::setContents(const std::string& contents)
{
	m_TextContents.setString(contents);
}

void Notify::setActive(const bool& active)
{
	m_Active = active;
}

const bool& Notify::isActive() const
{
	return m_Active;
}

void Notify::render(sf::RenderTarget* target)
{
	target->draw(m_Background);

	target->draw(m_TextHeader);
	target->draw(m_TextContents);

	for (uint8_t i = 0; i < m_Buttons.size(); i++)
	{
		m_Buttons[i].render(target);
	}
}

void Notify::setInPosition(const sf::Vector2f& position)
{
	m_Background.setPosition(position);

	m_TextHeader.setPosition(position.x + 10.f, position.y + 10.f);
	m_TextContents.setPosition(position.x + 10.f, position.y + m_TextHeader.getCharacterSize() + 15.f);
}
