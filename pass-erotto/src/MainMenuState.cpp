#include "MainMenuState.h"

using namespace Data;

MainMenuState::MainMenuState()
{
	rWindow->setTitle(WINDOW_TITLE + ": MainMenu");

	const uint16_t CHAR_SIZE = 30u;
	const float X_AXISPOS = WINDOW_WIDTH / 2.f;
	const float Y_POS = 175.f, Y_SPACING = 100.f;

	m_TextTitle = sf::Text("pass-erotto", *WINDOW_FONT, 50u);
	m_TextTitle.setPosition(floor(X_AXISPOS - m_TextTitle.getGlobalBounds().getSize().x / 2.f), 50.f);
	m_TextTitle.setOutlineThickness(2.f);
	m_TextTitle.setOutlineColor(sf::Color::Black);

	m_Buttons[Button::ACCOUNTS] = TextButton(*WINDOW_FONT, "Accounts", CHAR_SIZE, sf::Color::Black);
	m_Buttons[Button::IMPOSTAZIONI] = TextButton(*WINDOW_FONT, "Impostazioni", CHAR_SIZE, sf::Color::Black);
	m_Buttons[Button::AIUTO] = TextButton(*WINDOW_FONT, "Aiuto", CHAR_SIZE, sf::Color::Black);
	m_Buttons[Button::ESCI] = TextButton(*WINDOW_FONT, "Esci", CHAR_SIZE, sf::Color::Black);


	for (uint8_t i = 0; i < m_Buttons.size(); i++)
	{
		m_Buttons[i].setPosition({ floor(X_AXISPOS - m_Buttons[i].getBackground().getSize().x / 2.f), floor(Y_POS + Y_SPACING * i) });
	}
}
void MainMenuState::pollEvent()
{
	for (sf::Event event; rWindow->pollEvent(event);)
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			rWindow->close();
			break;
		case sf::Event::MouseMoved:
			for (uint8_t i = 0; i < m_Buttons.size(); i++)
			{
				if (m_Buttons[i].isCursorOn(*rWindow))
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
			for (uint8_t i = 0; i < m_Buttons.size(); i++)
			{
				if (m_Buttons[i].isCursorOn(*rWindow))
				{
					switch (i)
					{
					case Button::ACCOUNTS:
						s_Machine.add(StateRef(), false);
						break;
					case Button::IMPOSTAZIONI:
						s_Machine.add(StateRef(), false);
						break;
					case Button::AIUTO:
						s_Machine.add(StateRef(), false);
						break;
					case Button::ESCI:
						rWindow->close();
						break;
					}
				}
			}
			break;
		}
	}
}

void MainMenuState::update()
{
}

void MainMenuState::render()
{
	rWindow->clear(WINDOW_BACKGROUND);

	rWindow->draw(m_TextTitle);

	for (uint8_t i = 0; i < m_Buttons.size(); i++)
	{
		m_Buttons[i].render(rWindow);
	}

	rWindow->display();
}
