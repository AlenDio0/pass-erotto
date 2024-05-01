#include "Notify.h"

Notify::Notify(sf::Font& font, const sf::Vector2f& size, const std::string& header)
	: m_Background(size), m_TextHeader(header, font), m_TextContents("Contents", font), m_ButtonOk(font, "Ok", 20u)
{
	init();
	setPosition({ 0, 0 });
}

const bool& Notify::isCursorOnButtonOk(const sf::WindowBase& window)
{
	return m_ButtonOk.isCursorOn(window);
}

void Notify::setContents(const std::string& contents)
{
	m_TextContents.setString(contents);
}

void Notify::setInPosition(const sf::Vector2f& position)
{
	m_Background.setPosition(position);

	m_TextHeader.setPosition(position);
	m_TextContents.setPosition(position.x, position.y + m_TextHeader.getCharacterSize() + 5.f);

	m_ButtonOk.setPosition
	({ position.x + m_Background.getSize().x - m_ButtonOk.getBackground().getSize().x - 10.f,
		position.y + m_Background.getSize().y - m_ButtonOk.getBackground().getSize().y - 10.f
		});
}
