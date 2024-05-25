#pragma once
#include <SFML/Graphics.hpp>

#include "Data.h"

#include <unordered_map>
#include "TextButton.h"

class MessageBox
{
public:
	MessageBox() = delete;

	enum class Type
	{
		OK,
		YESNO,
	};

	static void showMessage(Type type, const sf::Vector2f& size, const std::string& title, const std::string& message);

	static std::unordered_map<uint8_t, TextButton>& getButtons();
	enum Buttons
	{
		OK,
		SI,
		NO,
	};

	static void setPosition(sf::Vector2f position = {});

	static void stop();
	static const bool& isActive();

	static void render(sf::RenderTarget* target);
private:
	static sf::RectangleShape m_Background;

	static sf::Text m_TextTitle;
	static sf::Text m_TextMessage;

	static std::unordered_map<uint8_t, TextButton> m_Buttons;

	static bool m_Active;
};

inline sf::RectangleShape MessageBox::m_Background;
inline sf::Text MessageBox::m_TextTitle;
inline sf::Text MessageBox::m_TextMessage;
inline std::unordered_map<uint8_t, TextButton> MessageBox::m_Buttons;
inline bool MessageBox::m_Active;