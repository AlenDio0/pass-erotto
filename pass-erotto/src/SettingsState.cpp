#include "SettingsState.h"

#include "CreatePINState.h"


using namespace Data;

SettingsState::SettingsState()
{
	const uint8_t CHAR_SIZE = 50u;
	const float X_POS = 25.f, Y_POS = 50.f;
	const float Y_SPACING = 50.f;

	m_Buttons[Button::CAMBIAPIN] = TextButton(*WINDOW_FONT, "Cambia PIN ", CHAR_SIZE);
	m_Buttons[Button::CAMBIAPIN].setPosition
	({
		X_POS,
		Y_POS
		});

	m_Buttons[Button::RESET] = TextButton(*WINDOW_FONT, "RESET ", CHAR_SIZE);
	m_Buttons[Button::RESET].setPosition
	({
		X_POS,
		Y_POS + m_Buttons[Button::RESET].getBackground().getSize().y + Y_SPACING
		});

	m_Buttons[Button::RITORNA] = TextButton(*WINDOW_FONT, "Ritorna ", CHAR_SIZE);
	m_Buttons[Button::RITORNA].setPosition
	({
		WINDOW_WIDTH / 2.f - m_Buttons[Button::RITORNA].getBackground().getSize().x / 2.f,
		WINDOW_HEIGTH - m_Buttons[Button::RITORNA].getBackground().getSize().y - 10.f
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

				break;
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

				break;
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
			break;
		case sf::Event::MouseButtonPressed:
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
							SETTINGSDATAFILE.generate(ini);

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

				break;
			}

			if (m_NotifyClose.isActive())
			{
				if (m_NotifyClose.getButtons()[Notify_Close::OK].isCursorOn(*g_Window))
				{
					g_Window->close();
				}

				break;
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
					case Button::RITORNA:
						g_Machine.remove();
						break;
					}
				}
			}
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
