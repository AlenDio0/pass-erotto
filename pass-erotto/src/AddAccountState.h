#pragma once
#include "State.h"

#include "Data.h"

#include <time.h>
#include <unordered_map>
#include "TextButton.h"
#include "TextBox.h"
#include "MessageBox.h"

class AddAccountState : public State
{
public:
	AddAccountState();

	virtual void init();

	void pollEvent();
	void update();
	void render();
protected:
	std::unordered_map<uint8_t, sf::Text> m_Texts;
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
		GENERA,
		CONFERMA,
		ANNULLA,
	};

	void onMouseMovement();
	void onMouseButtonPressed();

	void onGenerateButton();
	virtual void onConfirmButton();
};

