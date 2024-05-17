#pragma once
#include "State.h"

#include "Data.h"

#include <unordered_map>
#include "TextButton.h"
#include "Notify.h"

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

	class Notify_Reset : public Notify
	{
	public:
		Notify_Reset()
			: Notify(*Data::WINDOW_FONT, { 350.f, 200.f }, "Sei sicuro?")
		{
			m_TextHeader.setCharacterSize(25u);
			m_TextHeader.setStyle(sf::Text::Bold);

			m_TextContents.setCharacterSize(15u);
			setContents("\nStai per eliminare tutti i dati.\n\n(!) Questa operazione è irreversibile.");

			m_Buttons[Button::CONFERMA] = TextButton(*Data::WINDOW_FONT, "Conferma", 20u);
			m_Buttons[Button::ANNULLA] = TextButton(*Data::WINDOW_FONT, "Annulla", 20u);

			setPosition({ Data::WINDOW_WIDTH / 2.f - 350.f / 2.f, Data::WINDOW_HEIGTH / 2.f - 200.f / 2.f });
		}

		enum Button : uint8_t
		{
			CONFERMA,
			ANNULLA,
		};

		inline void setPosition(const sf::Vector2f& position) override
		{
			setInPosition(position);

			m_Buttons[Button::CONFERMA].setPosition
			({ position.x + m_Background.getSize().x - m_Buttons[Button::CONFERMA].getBackground().getSize().x - 10.f,
				position.y + m_Background.getSize().y - m_Buttons[Button::CONFERMA].getBackground().getSize().y - 10.f
				});

			m_Buttons[Button::ANNULLA].setPosition
			({ position.x + 10.f,
				position.y + m_Background.getSize().y - m_Buttons[Button::ANNULLA].getBackground().getSize().y - 10.f
				});
		}
	private:

	};
	Notify_Reset m_NotifyReset;

	class Notify_Close : public Notify
	{
	public:
		inline Notify_Close()
			: Notify(*Data::WINDOW_FONT, { 350.f, 200.f }, "Chiusura programma")
		{
			m_TextHeader.setCharacterSize(25u);
			m_TextHeader.setStyle(sf::Text::Bold);

			m_TextContents.setCharacterSize(15u);
			setContents("\nRESET eseguito:\n\nRichiesto riavvio, premendo Ok\nsi chiuderà il programma.");

			m_Buttons[Button::OK] = TextButton(*Data::WINDOW_FONT, "Ok", 20u);

			setPosition({ Data::WINDOW_WIDTH / 2.f - 350.f / 2.f, Data::WINDOW_HEIGTH / 2.f - 200.f / 2.f });
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
	Notify_Close m_NotifyClose;

	void onMouseMovement();
	void onMouseButtonPressed();
};

