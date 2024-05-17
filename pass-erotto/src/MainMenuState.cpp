#include "MainMenuState.h"

#include "AccountsPageState.h"
#include "SettingsState.h"

using namespace Data;

MainMenuState::MainMenuState()
{
	const uint8_t CHAR_SIZE1 = 50u, CHAR_SIZE2 = 30u;
	const float X_AXISPOS = WINDOW_WIDTH / 2.f;
	const float Y_POS = 175.f, Y_SPACING = 100.f;

	m_TextTitle = sf::Text("pass-erotto", *WINDOW_FONT, CHAR_SIZE1);
	m_TextTitle.setPosition(floor(X_AXISPOS - m_TextTitle.getGlobalBounds().getSize().x / 2.f), 50.f);
	m_TextTitle.setOutlineThickness(2.f);
	m_TextTitle.setOutlineColor(sf::Color::Black);

	m_Buttons[Button::ACCOUNTS] = TextButton(*WINDOW_FONT, "Accounts", CHAR_SIZE2, sf::Color::Black);
	m_Buttons[Button::IMPOSTAZIONI] = TextButton(*WINDOW_FONT, "Impostazioni", CHAR_SIZE2, sf::Color::Black);
	//m_Buttons[Button::AIUTO] = TextButton(*WINDOW_FONT, "Aiuto", CHAR_SIZE2, sf::Color::Black);
	m_Buttons[Button::ESCI] = TextButton(*WINDOW_FONT, "Esci", CHAR_SIZE2, sf::Color::Black);

	for (uint8_t i = 0; i < m_Buttons.size(); i++)
	{
		m_Buttons[i].setPosition({ floor(X_AXISPOS - m_Buttons[i].getBackground().getSize().x / 2.f), floor(Y_POS + Y_SPACING * i) });
	}
}

void MainMenuState::init()
{
	g_Window->setTitle(WINDOW_TITLE + ": MainMenu");
}

void MainMenuState::pollEvent()
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

void MainMenuState::update()
{
}

void MainMenuState::render()
{
	g_Window->clear(WINDOW_BACKGROUND);

	g_Window->draw(m_TextTitle);

	for (uint8_t i = 0; i < m_Buttons.size(); i++)
	{
		m_Buttons[i].render(g_Window);
	}

	g_Window->display();
}

void MainMenuState::onMouseMovement()
{
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

void MainMenuState::onMouseButtonPressed()
{
	for (uint8_t i = 0; i < m_Buttons.size(); i++)
	{
		if (m_Buttons[i].isCursorOn(*g_Window))
		{
			switch (i)
			{
			case Button::ACCOUNTS:
				g_Machine.add(StateRef(new AccountsPageState()), false);
				break;
			case Button::IMPOSTAZIONI:
				g_Machine.add(StateRef(new SettingsState), false);
				break;
			case Button::AIUTO:
				g_Machine.add(StateRef(), false);
				break;
			case Button::ESCI:
				g_Window->close();
				break;
			}
		}
	}
}
