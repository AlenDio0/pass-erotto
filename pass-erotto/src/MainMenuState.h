#pragma once
#include "State.h"

#include "Data.h"

#include <unordered_map>
#include "TextButton.h"

class MainMenuState : public State
{
public:
	MainMenuState();

	void init();

	void pollEvent();
	void update();
	void render();
private:
	sf::Text m_TextTitle;

	std::unordered_map<uint8_t, TextButton> m_Buttons;
	enum Button : uint8_t
	{
		ACCOUNTS,
		IMPOSTAZIONI,
		AIUTO,
		ESCI,
	};
};

