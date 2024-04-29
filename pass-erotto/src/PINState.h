#pragma once
#include "State.h"

#include <fstream>
#include "Data.h"

#include "TextBox.h"

class PINState : public State
{
public:
	PINState();

	void pollEvent();
	void update();
	void render();
private:
	std::string m_EncryptedPIN;
	std::string m_GuessPIN;

	TextBox m_TextBoxPIN;

	bool loadPIN();
};