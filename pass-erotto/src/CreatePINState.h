#pragma once
#include "State.h"

#include "Data.h"
#include "Style.h"

#include <unordered_map>
#include "TextBox.h"
#include "TextButton.h"

class CreatePINState : public State
{
public:
	CreatePINState();

	void init();

	void pollEvent();
	void update();
	void render();
private:
	sf::Text m_TextInsertPIN;
	TextBox m_TextBoxPIN;

	std::unordered_map<uint8_t, TextButton> m_Buttons;
	enum Button : uint8_t
	{
		CONFERMA,
		ANNULLA,
	};

	void onMouseMovement();
	void onMouseButtonPressed();
};

