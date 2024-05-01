#pragma once
#include <SFML/Graphics.hpp>

#include <unordered_map>
#include "TextButton.h"

class Notify
{
public:
	Notify() = default;
	Notify(sf::Font& font, const sf::Vector2f& size, const std::string& header);

	std::unordered_map<uint8_t, TextButton>& getButtons();

	virtual void setPosition(const sf::Vector2f& position) = 0;
	void setContents(const std::string& contents);

	void setActive(const bool& active);

	const bool& isActive() const;

	void render(sf::RenderTarget* target);
protected:
	sf::RectangleShape m_Background;

	sf::Text m_TextHeader;
	sf::Text m_TextContents;

	std::unordered_map<uint8_t, TextButton> m_Buttons;

	bool m_Active;

	void setInPosition(const sf::Vector2f& position);
};

