#include "AccountsPageState.h"

#include "AddAccountState.h"

using namespace Data;

AccountsPageState::AccountsPageState()
{
	m_TextTitle = sf::Text("pass-erotto", *WINDOW_FONT, 50u);
	m_TextTitle.setPosition(WINDOW_WIDTH / 2.f - m_TextTitle.getGlobalBounds().getSize().x / 2.f, 0.f);
	m_TextTitle.setOutlineThickness(2.f);
	m_TextTitle.setOutlineColor(sf::Color::Black);

	m_Background = sf::RectangleShape({ WINDOW_WIDTH, 60.f });
	m_Background.setFillColor(sf::Color::Blue);
	m_Background.setOutlineThickness(4.f);
	m_Background.setOutlineColor(sf::Color::Black);

	m_Buttons[Button::AGGIUNGI] = TextButton(*WINDOW_FONT, " + ", 30u, sf::Color::Black);
	m_Buttons[Button::AGGIUNGI].setPosition({ WINDOW_WIDTH - m_Buttons[Button::AGGIUNGI].getBackground().getSize().x - 10.f, 10.f });

	m_Buttons[Button::RITORNA] = TextButton(*WINDOW_FONT, " < ", 30u, sf::Color::Black);
	m_Buttons[Button::RITORNA].setPosition({ 10.f, 10.f });
}

void AccountsPageState::init()
{
	g_Window->setTitle(WINDOW_TITLE + ": Accounts");

	m_Accounts.clear();

	mINI::INIStructure ini;
	DATAFILE.read(ini);

	for (auto const& it : ini)
	{
		auto const& section = it.first;
		auto const& collection = it.second;

		m_Accounts.push_back(Account(section));

		/*for (auto const& it2 : collection)
		{
			auto const& key = it2.first;
			auto const& value = it2.second;

		}*/
	}

	for (uint16_t i = 0; i < m_Accounts.size(); i++)
	{
		m_Accounts[i].setPosition({ 10.f, m_Background.getSize().y + 10.f + 110.f * i });
	}
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
						g_Machine.add(StateRef(new AddAccountState()), false);
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

	g_Window->draw(m_TextTitle);

	for (Account& acc : m_Accounts)
	{
		acc.render(g_Window);
	}
	for (uint8_t i = 0; i < m_Buttons.size(); i++)
	{
		m_Buttons[i].render(g_Window);
	}

	g_Window->display();
}
