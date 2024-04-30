#include "AccountsPageState.h"

using namespace Data;

AccountsPageState::AccountsPageState()
{
	m_Background = sf::RectangleShape({ WINDOW_WIDTH, 60.f });
	m_Background.setFillColor(sf::Color::Blue);
	m_Background.setOutlineThickness(4.f);
	m_Background.setOutlineColor(sf::Color::Black);

	m_Buttons[Button::AGGIUNGI] = TextButton(*WINDOW_FONT, " + ", 30u, sf::Color::Black);
	m_Buttons[Button::AGGIUNGI].setPosition({ WINDOW_WIDTH - m_Buttons[Button::AGGIUNGI].getBackground().getSize().x - 10.f, 10.f });

	m_Buttons[Button::RITORNA] = TextButton(*WINDOW_FONT, " < ", 30u, sf::Color::Black);
	m_Buttons[Button::RITORNA].setPosition({ 10.f, 10.f });

	m_Accounts.push_back(Account("WWWWWWWWWWWWWWWW"));
	m_Accounts[0].setPosition({ 10.f, m_Background.getSize().y + 10.f });
}

void AccountsPageState::init()
{
	g_Window->setTitle(WINDOW_TITLE + ": Accounts");
}

void AccountsPageState::pollEvent()
{
	for (sf::Event event; g_Window->pollEvent(event);)
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			g_Window->close();
			break;
		case sf::Event::MouseMoved:
		{
			std::vector<TextButton*> buttons;

			buttons.push_back(&m_Buttons[Button::AGGIUNGI]);
			buttons.push_back(&m_Buttons[Button::RITORNA]);

			for (Account& acc : m_Accounts)
			{
				buttons.push_back(&acc.getButtonModify());
				buttons.push_back(&acc.getButtonDelete());
			}

			for (TextButton* button : buttons)
			{
				if (button->isCursorOn(*g_Window))
				{
					button->setHighlight(true);
				}
				else
				{
					button->setHighlight(false);
				}
			}
		}
		break;
		case sf::Event::MouseButtonPressed:
			for (uint8_t i = 0; i < m_Buttons.size(); i++)
			{
				if (m_Buttons[i].isCursorOn(*g_Window))
				{
					switch (i)
					{
					case Button::AGGIUNGI:
						g_Machine.add(StateRef(), false);
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

void AccountsPageState::update()
{
}

void AccountsPageState::render()
{
	g_Window->clear(WINDOW_BACKGROUND);

	g_Window->draw(m_Background);

	for (Account& acc : m_Accounts)
	{
		acc.render(g_Window);
	}

	m_Buttons[Button::AGGIUNGI].render(g_Window);
	m_Buttons[Button::RITORNA].render(g_Window);

	g_Window->display();
}
