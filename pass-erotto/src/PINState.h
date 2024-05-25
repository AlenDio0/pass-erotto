#pragma once
#include "State.h"

#include <fstream>
#include "Data.h"

#include "TextBox.h"
#include "TextButton.h"
#include "MessageBox.h"

class PINState : public State
{
public:
	PINState();

	void init();

	void pollEvent();
	void update();
	void render();
private:
	std::string m_PIN;

	sf::Text m_TextInsertPIN;
	TextBox m_TextBoxPIN;

	TextButton m_ButtonConfirm;

	void onMouseMovement();
	void onMouseButtonPressed();

	bool loadPIN();
};