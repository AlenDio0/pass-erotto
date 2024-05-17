#include "SettingsState.h"

#include "CreatePINState.h"


using namespace Data;

SettingsState::SettingsState()
{
	const uint8_t CHAR_SIZE1 = 40u, CHAR_SIZE2 = 25u;
	const float X_AXIS = WINDOW_WIDTH / 2.f, Y_POS = 150.f;
	const float Y_SPACING = 50.f;

	m_Buttons[Button::CAMBIAPIN] = TextButton(*WINDOW_FONT, "Cambia PIN", CHAR_SIZE1);
	m_Buttons[Button::CAMBIAPIN].setPosition
	({
		X_AXIS - m_Buttons[Button::CAMBIAPIN].getBackground().getSize().x / 2.f,
		Y_POS
		});

	m_Buttons[Button::RESET] = TextButton(*WINDOW_FONT, "RESET", CHAR_SIZE1);
	m_Buttons[Button::RESET].setPosition
	({
		X_AXIS - m_Buttons[Button::RESET].getBackground().getSize().x / 2.f,
		Y_POS + m_Buttons[Button::RESET].getBackground().getSize().y + Y_SPACING
		});

	m_Buttons[Button::INDIETRO] = TextButton(*WINDOW_FONT, "< Indietro", CHAR_SIZE2);
	m_Buttons[Button::INDIETRO].setPosition
	({
		25.f,
		25.f
		});
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

	if (m_NotifyReset.isActive())
	{
		m_NotifyReset.render(g_Window);
	}

	if (m_NotifyClose.isActive())
	{
		m_NotifyClose.render(g_Window);
	}

	g_Window->display();
}

void SettingsState::onMouseMovement()
{
	if (m_NotifyReset.isActive())
	{
		auto& buttons = m_NotifyReset.getButtons();

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

	if (m_NotifyClose.isActive())
	{
		TextButton& button = m_NotifyClose.getButtons()[Notify_Close::OK];

		if (button.isCursorOn(*g_Window))
		{
			button.setHighlight(true);
		}
		else
		{
			button.setHighlight(false);
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
	if (m_NotifyReset.isActive())
	{
		auto& buttons = m_NotifyReset.getButtons();

		for (uint8_t i = 0; i < buttons.size(); i++)
		{
			if (buttons[i].isCursorOn(*g_Window))
			{
				switch (i)
				{
				case Notify_Reset::CONFERMA:
				{
					mINI::INIStructure ini;

					DATAFILE.generate(ini);

					m_NotifyClose = Notify_Close();
					m_NotifyClose.setActive(true);
				}
				break;
				case Notify_Reset::ANNULLA:
					break;
				}

				m_NotifyReset.setActive(false);
			}
		}

		return;
	}

	if (m_NotifyClose.isActive())
	{
		if (m_NotifyClose.getButtons()[Notify_Close::OK].isCursorOn(*g_Window))
		{
			g_Window->close();
		}

		return;
	}

	for (uint8_t i = 0; i < m_Buttons.size(); i++)
	{
		if (m_Buttons[i].isCursorOn(*g_Window))
		{
			switch (i)
			{
			case Button::CAMBIAPIN:
				g_Machine.add(StateRef(new CreatePINState()), false);
				break;
			case Button::RESET:
				m_NotifyReset = Notify_Reset();
				m_NotifyReset.setActive(true);
				break;
			case Button::INDIETRO:
				g_Machine.remove();
				break;
			}
		}
	}
}
