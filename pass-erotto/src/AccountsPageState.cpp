#include "AccountsPageState.h"

#include "AddAccountState.h"
#include "EditAccountState.h"

using namespace Data;

#define ACCOUNT_XPOS(size) (WINDOW_WIDTH / 2.f - size / 2.f)

AccountsPageState::AccountsPageState()
	: m_AccountDeleteName(NULL)
{
	m_TextTitle = sf::Text("pass-erotto", *WINDOW_FONT, Style::CharSize::Large);

	m_TextTitle.setPosition(Style::WINDOW_AXIS - m_TextTitle.getGlobalBounds().getSize().x / 2.f, Style::WINDOW_OFFSET / 2.f);
	m_TextTitle.setOutlineThickness(2.f);
	m_TextTitle.setOutlineColor(sf::Color::Black);

	m_Background = sf::RectangleShape({ WINDOW_WIDTH, 110.f });

	m_Background.setFillColor(sf::Color::Blue);
	m_Background.setOutlineThickness(4.f);
	m_Background.setOutlineColor(sf::Color::Black);

	m_TextBoxSearch = TextBox(*WINDOW_FONT, Style::CharSize::Small, sf::Color::Black, 14u);

	m_TextBoxSearch.setPosition
	({
		Style::WINDOW_AXIS - m_TextBoxSearch.getSize().x / 2.f,
		m_Background.getSize().y - m_TextBoxSearch.getSize().y - Style::WINDOW_OFFSET
		});
	m_TextBoxSearch.setPlaceHolder("Cerca...");

	m_Buttons[AGGIUNGI] = TextButton(*WINDOW_FONT, " + ", Style::CharSize::Medium, sf::Color::Black);
	m_Buttons[INDIETRO] = TextButton(*WINDOW_FONT, " < ", Style::CharSize::Medium, sf::Color::Black);

	m_Buttons[AGGIUNGI].setPosition({ WINDOW_WIDTH - m_Buttons[AGGIUNGI].getSize().x - Style::WINDOW_OFFSET, Style::WINDOW_OFFSET });
	m_Buttons[INDIETRO].setPosition({ Style::WINDOW_OFFSET, Style::WINDOW_OFFSET });
}

void AccountsPageState::init()
{
	g_Window->setTitle(WINDOW_TITLE + ": Accounts");

	loadAccounts();

	onSearch(m_TextBoxSearch.getBuff());

	setAccountsInPosition();
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
			onMouseMovement();
			break;
		case sf::Event::MouseButtonPressed:
			onMouseButtonPressed();
			break;
		case sf::Event::TextEntered:
			m_TextBoxSearch.onType(event);
			break;
		case sf::Event::MouseWheelScrolled:
			onScrollPage(event);
			break;
		}
	}
}

void AccountsPageState::update()
{
	m_TextBoxSearch.update();

	updateSearch();
}

void AccountsPageState::render()
{
	g_Window->clear(WINDOW_BACKGROUND);

	for (Account* acc : m_VisibleAccounts)
	{
		acc->render(g_Window);
	}

	g_Window->draw(m_Background);

	g_Window->draw(m_TextTitle);

	m_TextBoxSearch.render(g_Window);

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

void AccountsPageState::onMouseMovement()
{
	if (MessageBox::isActive())
	{
		auto& buttons = MessageBox::getButtons();

		for (uint8_t i = 0; i < buttons.size(); i++)
		{
			if (buttons[i].isCursorOn(*g_Window))
			{
				buttons[i].setHighlight(true);
			}
			else
			{
				buttons[i].setHighlight(false);
			}
		}

		return;
	}

	std::vector<TextButton*> buttons;

	buttons.push_back(&m_Buttons[AGGIUNGI]);
	buttons.push_back(&m_Buttons[INDIETRO]);

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

void AccountsPageState::onMouseButtonPressed()
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
				case MessageBox::Buttons::OK:
					if (buttons[i].isCursorOn(*g_Window))
					{
						MessageBox::stop();
					}
					break;
				case MessageBox::Buttons::SI:
				{
					mINI::INIStructure ini;
					DATAFILE.read(ini);

					ini.remove(*m_AccountDeleteName);
					m_AccountDeleteName = NULL;

					DATAFILE.write(ini);

					init();

					MessageBox::stop();
				}
				break;
				case MessageBox::Buttons::NO:
					MessageBox::stop();
					break;
				}
			}
		}

		return;
	}

	if (m_TextBoxSearch.isCursorOn(*g_Window))
	{
		m_TextBoxSearch.setSelected(true);
	}
	else
	{
		m_TextBoxSearch.setSelected(false);
	}

	for (Account* acc : m_VisibleAccounts)
	{
		enum : uint8_t
		{
			MOSTRA,
			MODIFICA,
			ELIMINA,
		};
		std::unordered_map<uint8_t, TextButton*> buttons;

		buttons[MOSTRA] = &acc->getButtonView();
		buttons[MODIFICA] = &acc->getButtonEdit();
		buttons[ELIMINA] = &acc->getButtonDelete();

		for (uint8_t i = 0; i < buttons.size(); i++)
		{
			if (buttons[i]->isCursorOn(*g_Window))
			{
				switch (i)
				{
				case MOSTRA:
				{
					std::stringstream message;
					message << "Nome utente:\n" << acc->getAccountInfo().username << "\n\nPassword:\n" << acc->getAccountInfo().password;

					MessageBox::showMessage
					(
						MessageBox::Type::OK,
						{ 350.f , 225.f },
						"Account: " + acc->getAccountInfo().name,
						message.str()
					);
				}
				break;
				case MODIFICA:
					g_Machine.add(StateRef(new EditAccountState(acc->getAccountInfo())), false);
					break;
				case ELIMINA:
				{
					m_AccountDeleteName = &acc->getAccountInfo().name;

					std::stringstream message;
					message << "Stai per eliminare:\n" << acc->getAccountInfo().name << "\n\n(!) Questa operazione è\nirreversibile.";
					MessageBox::showMessage
					(
						MessageBox::Type::YESNO,
						{ 350.f , 225.f },
						"Account: " + acc->getAccountInfo().name,
						message.str()
					);
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
			case AGGIUNGI:
				g_Machine.add(StateRef(new AddAccountState()), false);
				break;
			case INDIETRO:
				g_Machine.remove();
				break;
			}
		}
	}
}

void AccountsPageState::onScrollPage(const sf::Event& event)
{
	if (m_VisibleAccounts.empty())
	{
		return;
	}

	const float DELTA = event.mouseWheelScroll.delta;

	const int MOVE = 55;

	auto DEFAULT = [&](const uint16_t& i) -> float
		{
			return m_Background.getSize().y + Style::WINDOW_OFFSET + m_VisibleAccounts[i]->getSize().y * i;
		};

	if (DELTA > 0.f)
	{
		for (uint16_t i = 0; i < m_VisibleAccounts.size(); i++)
		{
			if (m_VisibleAccounts[i]->getPosition().y != DEFAULT(i))
			{
				m_VisibleAccounts[i]->setPosition
				({
					ACCOUNT_XPOS(m_Accounts[i].getSize().x),
					m_VisibleAccounts[i]->getPosition().y + MOVE
					});
			}
		}
	}
	else if (DELTA < 0.f)
	{
		for (uint16_t i = 0; i < m_VisibleAccounts.size(); i++)
		{
			if (m_VisibleAccounts[i]->getPosition().y <= DEFAULT(i))
			{
				m_VisibleAccounts[i]->setPosition
				({
					ACCOUNT_XPOS(m_Accounts[i].getSize().x),
					m_VisibleAccounts[i]->getPosition().y - MOVE
					});
			}
		}
	}
}

void AccountsPageState::updateSearch()
{
	static std::string search;
	if (!m_TextBoxSearch.getBuff().empty())
	{
		if (search != m_TextBoxSearch.getBuff())
		{
			search = m_TextBoxSearch.getBuff();
			for (char& c : search)
			{
				c += c < 'A' || c > 'Z' ? 0 : 32;
			}

			onSearch(search);
		}
	}
	else if (m_VisibleAccounts.size() != m_Accounts.size())
	{
		search = "";

		m_VisibleAccounts.clear();
		for (Account& acc : m_Accounts)
		{
			m_VisibleAccounts.push_back(&acc);
		}

		setAccountsInPosition();
	}
}

void AccountsPageState::onSearch(const std::string& search)
{
	m_VisibleAccounts.clear();

	for (Account& acc : m_Accounts)
	{
		std::string name = acc.getAccountInfo().name;

		if (search.length() > name.length())
		{
			continue;
		}

		bool found = true;
		for (int i = 0; i < search.length(); i++)
		{
			if (search[i] != name[i])
			{
				found = false;
				break;
			}
		}

		if (found)
		{
			m_VisibleAccounts.push_back(&acc);
		}
	}

	setAccountsInPosition();
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

		if (section == "settings")
		{
			continue;
		}

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

void AccountsPageState::setAccountsInPosition()
{
	for (uint16_t i = 0; i < m_VisibleAccounts.size(); i++)
	{
		m_VisibleAccounts[i]->setPosition
		({
			ACCOUNT_XPOS(m_VisibleAccounts[i]->getSize().x),
			m_Background.getSize().y + Style::WINDOW_OFFSET + m_VisibleAccounts[i]->getSize().y * i
			});
	}
}
