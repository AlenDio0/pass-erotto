#include "SettingsState.h"

#include "CreatePINState.h"


using namespace Data;

SettingsState::SettingsState()
{
	const float POS_Y = 150.f;
	const float SPACING = 50.f;

	m_Buttons[CAMBIAPIN] = TextButton(*WINDOW_FONT, "Cambia PIN", Style::CharSize::Large);
	m_Buttons[RESET] = TextButton(*WINDOW_FONT, "RESET", Style::CharSize::Large);
	m_Buttons[INDIETRO] = TextButton(*WINDOW_FONT, "< Indietro", Style::CharSize::Medium);

	m_Buttons[CAMBIAPIN].setPosition
	({
		Style::WINDOW_AXIS - (m_Buttons[CAMBIAPIN].getSize().x / 2.f),
		POS_Y
		});
	m_Buttons[RESET].setPosition
	({
		Style::WINDOW_AXIS - (m_Buttons[RESET].getSize().x / 2.f),
		POS_Y + m_Buttons[RESET].getSize().y + SPACING
		});
	m_Buttons[INDIETRO].setPosition({ Style::WINDOW_OFFSET,Style::WINDOW_OFFSET });
}

void SettingsState::init()
{
	g_Window->setTitle(WINDOW_TITLE + ": Impostazioni");
}

void SettingsState::pollEvent()
{
	for (sf::Event event; g_Window->pollEvent(event);)
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			g_Window->close();
			break;
		case sf::Event::MouseMoved:
			onMouseMovement();
			break;
		case sf::Event::MouseButtonPressed:
			onMouseButtonPressed();
			break;
		}
	}
}

void SettingsState::update()
{
}

void SettingsState::render()
{
	g_Window->clear(WINDOW_BACKGROUND);

	for (uint8_t i = 0; i < m_Buttons.size(); i++)
	{
		m_Buttons[i].render(g_Window);
	}

	if (MessageBox::isActive())
	{
		MessageBox::render(g_Window);
	}

	g_Window->display();
}

void SettingsState::onMouseMovement()
{
	if (MessageBox::isActive())
	{
		auto& buttons = MessageBox::getButtons();

		for (uint8_t i = 0; i < buttons.size(); i++)
		{
			TextButton& button = buttons[i];
			if (button.isCursorOn(*g_Window))
			{
				button.setHighlight(true);
			}
			else
			{
				button.setHighlight(false);
			}
		}

		return;
	}

	for (uint8_t i = 0; i < m_Buttons.size(); i++)
	{
		if (m_Buttons[i].isCursorOn(*g_Window))
		{
			m_Buttons[i].setHighlight(true);
		}
		else
		{
			m_Buttons[i].setHighlight(false);
		}
	}
}

void SettingsState::onMouseButtonPressed()
{
	if (MessageBox::isActive())
	{
		auto& buttons = MessageBox::getButtons();

		for (uint8_t i = 0; i < buttons.size(); i++)
		{
			if (buttons[i].isCursorOn(*g_Window))
			{
				switch (i)
				{
				case MessageBox::Buttons::SI:
				{
					mINI::INIStructure ini;

					DATAFILE.generate(ini);

					MessageBox::stop();
					MessageBox::showMessage
					(
						MessageBox::Type::OK,
						{ 350.f, 200.f },
						"RESET - Chiusura programma",
						"Il RESET è stato terminato:\n\nRichiesto riavvio, premendo Ok\nsi chiuderà il programma."
					);
				}
				break;
				case MessageBox::Buttons::NO:
					MessageBox::stop();
					break;
				case MessageBox::Buttons::OK:
					g_Machine.remove();
					break;
				}
			}
		}

		return;
	}

	for (uint8_t i = 0; i < m_Buttons.size(); i++)
	{
		if (m_Buttons[i].isCursorOn(*g_Window))
		{
			switch (i)
			{
			case CAMBIAPIN:
				g_Machine.add(StateRef(new CreatePINState()), false);
				break;
			case RESET:
				MessageBox::showMessage
				(
					MessageBox::Type::YESNO,
					{ 350.f, 200.f },
					"RESET - Sei sicuro?",
					"Stai per eliminare tutti i dati.\n\n(!) Questa operazione è\nirreversibile."
				);
				break;
			case INDIETRO:
				g_Machine.remove();
				break;
			}
		}
	}
}
