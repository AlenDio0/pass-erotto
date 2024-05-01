#pragma once
#include <SFML/Graphics.hpp>

#include "TextButton.h"

class Notify
{
public:
	Notify() = default;
	Notify(sf::Font& font, const sf::Vector2f& size, const std::string& header);

	virtual void init() = 0;

	const bool& isCursorOnButtonOk(const sf::WindowBase& window);

	virtual void setPosition(const sf::Vector2f& position) = 0;
	void setContents(const std::string& contents);
protected:
	sf::RectangleShape m_Background;

	sf::Text m_TextHeader;
	sf::Text m_TextContents;

	TextButton m_ButtonOk;

	void setInPosition(const sf::Vector2f& position);
};

