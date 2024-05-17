#pragma once
#include "State.h"

#include <fstream>
#include "Data.h"

#include "TextBox.h"
#include "TextButton.h"
#include "Notify.h"

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

	class Notify_WrongPIN : public Notify
	{
	public:
		inline Notify_WrongPIN()
			: Notify(*Data::WINDOW_FONT, { 200.f, 100.f }, "PIN Sbagliato")
		{
			m_TextHeader.setCharacterSize(20u);
			m_TextHeader.setStyle(sf::Text::Bold);

			setContents("");

			m_Buttons[Button::OK] = TextButton(*Data::WINDOW_FONT, "Ok", 20u);

			setPosition({ Data::WINDOW_WIDTH / 2.f - 200.f / 2.f, Data::WINDOW_HEIGTH / 2.f - 100.f / 2.f });
		}

		enum Button : uint8_t
		{
			OK,
		};

		inline void setPosition(const sf::Vector2f& position) override
		{
			setInPosition(position);

			m_Buttons[Button::OK].setPosition
			({ position.x + m_Background.getSize().x - m_Buttons[Button::OK].getBackground().getSize().x - 10.f,
				position.y + m_Background.getSize().y - m_Buttons[Button::OK].getBackground().getSize().y - 10.f
				});
		}
	private:

	};
	Notify_WrongPIN m_NotifyWrongPIN;

	void onMouseMovement();
	void onMouseButtonPressed();

	bool loadPIN();
};