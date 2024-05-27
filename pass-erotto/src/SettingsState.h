#pragma once
#include "State.h"

#include "Data.h"
#include "Style.h"

#include <unordered_map>
#include "TextButton.h"
#include "MessageBox.h"

class SettingsState : public State
{
public:
	SettingsState();

	void init();

	void pollEvent();
	void update();
	void render();
private:
	std::unordered_map<uint8_t, TextButton> m_Buttons;
	enum Button : uint8_t
	{
		CAMBIAPIN,
		RESET,
		INDIETRO,
	};

	void onMouseMovement();
	void onMouseButtonPressed();
};

