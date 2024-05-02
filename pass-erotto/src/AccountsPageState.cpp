#include "AccountsPageState.h"

#include "AddAccountState.h"
#include "EditAccountState.h"

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
				TextButton& button = m_NotifyViewAccount.getButtons()[Notify_ViewAccount::OK];

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

			if (m_NotifyDeleteAccount.isActive())
			{
				auto& buttons = m_NotifyDeleteAccount.getButtons();

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
				if (m_NotifyViewAccount.getButtons()[Notify_ViewAccount::OK].isCursorOn(*g_Window))
				{
					m_NotifyViewAccount.setActive(false);
				}

				break;
			}

			if (m_NotifyDeleteAccount.isActive())
			{
				auto& buttons = m_NotifyDeleteAccount.getButtons();

				for (uint8_t i = 0; i < buttons.size(); i++)
				{
					if (buttons[i].isCursorOn(*g_Window))
					{
						switch (i)
						{
						case Notify_DeleteAccount::CONFERMA:
						{
							mINI::INIStructure ini;
							DATAFILE.read(ini);

							ini.remove(m_NotifyDeleteAccount.getName());

							DATAFILE.write(ini);

							init();
						}
						break;
						case Notify_DeleteAccount::ANNULLA:
							break;
						}

						m_NotifyDeleteAccount.setActive(false);
					}
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
							m_NotifyViewAccount = Notify_ViewAccount("Account: " + acc.getAccountInfo().name);

							std::stringstream contents;
							contents << "\nNome utente:\n" << acc.getAccountInfo().username << "\n\nPassword:\n" << acc.getAccountInfo().password;
							m_NotifyViewAccount.setContents(contents.str());

							m_NotifyViewAccount.setActive(true);
						}
						break;
						case MODIFICA:
							g_Machine.add(StateRef(new EditAccountState(acc.getAccountInfo())), false);
							break;
						case ELIMINA:
						{
							m_NotifyDeleteAccount = Notify_DeleteAccount(acc.getAccountInfo().name);

							std::stringstream contents;
							contents << "\nStai per eliminare:\n" << acc.getAccountInfo().name
								<< "\n\n\n(!) Questa operazione � irreversibile.";
							m_NotifyDeleteAccount.setContents(contents.str());

							m_NotifyDeleteAccount.setActive(true);
						}
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
		case sf::Event::MouseWheelScrolled:
			if (m_Accounts.empty())
			{
				break;
			}

			{
				const float DELTA = event.mouseWheelScroll.delta;
				const float X_DEFAULT = 10.f;

				const int Y_MOVE = 55;

				if (DELTA > 0.f)
				{
					for (uint16_t i = 0; i < m_Accounts.size(); i++)
					{
						const float Y_DEFAULT = m_Background.getSize().y + 10.f + 110.f * i;

						if (m_Accounts[i].getPosition().y != Y_DEFAULT)
						{
							m_Accounts[i].setPosition({ X_DEFAULT, m_Accounts[i].getPosition().y + Y_MOVE });
						}
					}
				}
				else if (DELTA < 0.f)
				{
					for (uint16_t i = 0; i < m_Accounts.size(); i++)
					{
						const float Y_DEFAULT = m_Background.getSize().y + 10.f + 110.f * i;

						if (m_Accounts[i].getPosition().y <= Y_DEFAULT)
						{
							m_Accounts[i].setPosition({ X_DEFAULT, m_Accounts[i].getPosition().y - Y_MOVE });
						}
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

	for (Account& acc : m_Accounts)
	{
		acc.render(g_Window);
	}

	g_Window->draw(m_Background);

	g_Window->draw(m_TextTitle);

	for (uint8_t i = 0; i < m_Buttons.size(); i++)
	{
		m_Buttons[i].render(g_Window);
	}

	if (m_NotifyViewAccount.isActive())
	{
		m_NotifyViewAccount.render(g_Window);
	}

	if (m_NotifyDeleteAccount.isActive())
	{
		m_NotifyDeleteAccount.render(g_Window);
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

		Account account;
		account.setName(section);

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
