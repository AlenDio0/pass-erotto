#pragma once
#include "State.h"

#include "Data.h"

#include <unordered_map>
#include "TextButton.h"
#include "TextBox.h"

class AddAccountState : public State
{
public:
	AddAccountState();

	void init();

	void pollEvent();
	void update();
	void render();
private:
	std::unordered_map<uint8_t, TextBox> m_TextBoxes;
	enum Box : uint8_t
	{
		NOME,
		NOMEUTENTE,
		PASSWORD,
	};
	std::unordered_map<uint8_t, TextButton> m_Buttons;
	enum Button : uint8_t
	{
		CONFERMA,
		ANNULLA,
	};

};

