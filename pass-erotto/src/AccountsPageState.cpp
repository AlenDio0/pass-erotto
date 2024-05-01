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

	loadAccounts();

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
			if (m_NotifyViewAccount.isActive())
			{
				TextButton& button = m_NotifyViewAccount.getButtonOk();

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

			std::vector<TextButton*> buttons;

			buttons.push_back(&m_Buttons[Button::AGGIUNGI]);
			buttons.push_back(&m_Buttons[Button::RITORNA]);

			for (Account& acc : m_Accounts)
			{
				buttons.push_back(&acc.getButtonView());
				buttons.push_back(&acc.getButtonEdit());
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
			if (m_NotifyViewAccount.isActive())
			{
				if (m_NotifyViewAccount.getButtonOk().isCursorOn(*g_Window))
				{
					m_NotifyViewAccount.setActive(false);
				}

				break;
			}

			for (Account& acc : m_Accounts)
			{
				enum : uint8_t
				{
					MOSTRA,
					MODIFICA,
					ELIMINA,
				};
				std::unordered_map<uint8_t, TextButton*> buttons;

				buttons[MOSTRA] = &acc.getButtonView();
				buttons[MODIFICA] = &acc.getButtonEdit();
				buttons[ELIMINA] = &acc.getButtonDelete();

				for (uint8_t i = 0; i < buttons.size(); i++)
				{
					if (buttons[i]->isCursorOn(*g_Window))
					{
						switch (i)
						{
						case MOSTRA:
						{
							m_NotifyViewAccount = Notify_ViewAccount(*WINDOW_FONT, { 350.f, 200.f }, "Account: " + acc.getName());
							m_NotifyViewAccount.setPosition({ WINDOW_WIDTH / 2.f - 350.f / 2.f, WINDOW_HEIGTH / 2.f - 200.f / 2.f });

							std::stringstream contents;
							contents << "Username:\n" << acc.getUsername() << "\n\nPassword:\n" << acc.getPassword();
							m_NotifyViewAccount.setContents(contents.str());

							m_NotifyViewAccount.setActive(true);
						}
						break;
						case MODIFICA:
							break;
						case ELIMINA:
							break;
						}
					}
				}
			}

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

	if (m_NotifyViewAccount.isActive())
	{
		m_NotifyViewAccount.render(g_Window);
	}

	g_Window->display();
}

void AccountsPageState::loadAccounts()
{
	m_Accounts.clear();

	mINI::INIStructure ini;
	DATAFILE.read(ini);

	for (auto const& it : ini)
	{
		const std::string& section = it.first;
		const auto& collection = it.second;

		Account account(section);

		for (const auto& it2 : collection)
		{
			const std::string& key = it2.first;
			const std::string& value = it2.second;

			if (key == "nome")
			{
				account.setUsername(value);
			}
			else if (key == "pass")
			{
				account.setPassword(value);
			}
		}
		m_Accounts.push_back(account);
	}
}
