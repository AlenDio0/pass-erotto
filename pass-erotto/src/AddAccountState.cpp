#include "AddAccountState.h"

using namespace Data;

AddAccountState::AddAccountState()
{
	srand((unsigned)time(NULL));

	const uint16_t TEXT_SIZE = Style::CharSize::Medium - 5;
	const float POS_Y = 125.f;
	const float SPACING = 100.f;

	m_Texts[NOME] = sf::Text("Nome:", *WINDOW_FONT, TEXT_SIZE);
	m_Texts[NOMEUTENTE] = sf::Text("Nome utente:", *WINDOW_FONT, TEXT_SIZE);
	m_Texts[PASSWORD] = sf::Text("Password:", *WINDOW_FONT, TEXT_SIZE);

	m_TextBoxes[NOME] = TextBox(*WINDOW_FONT, Style::CharSize::Small, sf::Color::Black, 16u);
	m_TextBoxes[NOMEUTENTE] = TextBox(*WINDOW_FONT, Style::CharSize::Small - 2, sf::Color::Black, 20u);
	m_TextBoxes[PASSWORD] = TextBox(*WINDOW_FONT, Style::CharSize::Small, sf::Color::Black, 16u);

	m_TextBoxes[NOME].setPlaceHolder("Nome (Gmail Lavoro, ...)");
	m_TextBoxes[NOMEUTENTE].setPlaceHolder("Nome utente (nome@gmail.com, ...)");
	m_TextBoxes[PASSWORD].setPlaceHolder("Password");

	for (uint8_t i = 0; i < m_TextBoxes.size(); i++)
	{
		m_TextBoxes[i].setPosition({ Style::WINDOW_AXIS - (m_TextBoxes[i].getSize().x / 2.f), POS_Y + (SPACING * i) });

		m_Texts[i].setPosition
		({
			Style::WINDOW_AXIS - (m_Texts[i].getGlobalBounds().getSize().x / 2.f),
			POS_Y + (SPACING * i) - m_TextBoxes[i].getSize().y - 5.f
			});
		m_Texts[i].setOutlineThickness(2.f);
	}

	m_Buttons[GENERA] = TextButton(*WINDOW_FONT, "Genera Password", Style::CharSize::Small);
	m_Buttons[CONFERMA] = TextButton(*WINDOW_FONT, "Conferma", Style::CharSize::Medium);
	m_Buttons[ANNULLA] = TextButton(*WINDOW_FONT, "Annulla", Style::CharSize::Medium);

	m_Buttons[GENERA].setPosition
	({
		Style::WINDOW_AXIS - (m_Buttons[GENERA].getSize().x / 2.f),
		m_TextBoxes[PASSWORD].getBackground().getPosition().y + m_TextBoxes[PASSWORD].getSize().y + Style::WINDOW_OFFSET
		});
	m_Buttons[CONFERMA].setPosition
	({
		(Style::WINDOW_AXIS * 1.5f) - (m_Buttons[CONFERMA].getSize().x / 2.f),
		WINDOW_HEIGTH - m_Buttons[CONFERMA].getSize().y - 50.f
		});
	m_Buttons[ANNULLA].setPosition
	({
		(Style::WINDOW_AXIS / 2.f) - (m_Buttons[ANNULLA].getSize().x / 2.f),
		WINDOW_HEIGTH - m_Buttons[ANNULLA].getSize().y - 50.f
		});
}

void AddAccountState::init()
{
	g_Window->setTitle(WINDOW_TITLE + ": Aggiungi account");
}

void AddAccountState::pollEvent()
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
			for (uint8_t i = 0; i < m_TextBoxes.size(); i++)
			{
				m_TextBoxes[i].onType(event);
			}
			break;
		}
	}
}

void AddAccountState::update()
{
	for (uint8_t i = 0; i < m_TextBoxes.size(); i++)
	{
		m_TextBoxes[i].update();
	}
}

void AddAccountState::render()
{
	g_Window->clear(WINDOW_BACKGROUND);

	for (uint8_t i = 0; i < m_TextBoxes.size(); i++)
	{
		g_Window->draw(m_Texts[i]);
		m_TextBoxes[i].render(g_Window);
	}

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

void AddAccountState::onMouseMovement()
{
	if (MessageBox::isActive())
	{
		TextButton& button = MessageBox::getButtons()[MessageBox::Buttons::OK];

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

void AddAccountState::onMouseButtonPressed()
{
	if (MessageBox::isActive())
	{
		if (MessageBox::getButtons()[MessageBox::Buttons::OK].isCursorOn(*g_Window))
		{
			MessageBox::stop();
		}

		return;
	}

	for (uint8_t i = 0; i < m_TextBoxes.size(); i++)
	{
		if (m_TextBoxes[i].isCursorOn(*g_Window))
		{
			m_TextBoxes[i].setSelected(true);
		}
		else
		{
			m_TextBoxes[i].setSelected(false);
		}
	}

	for (uint8_t i = 0; i < m_Buttons.size(); i++)
	{
		if (m_Buttons[i].isCursorOn(*g_Window))
		{
			switch (i)
			{
			case GENERA:
				onGenerateButton();
				break;
			case CONFERMA:
				onConfirmButton();
				break;
			case ANNULLA:
				g_Machine.remove();
				break;
			}
		}
	}
}

void AddAccountState::onGenerateButton()
{
	std::string new_password;

	for (int i = 0; i < 12; i++)
	{
		static const std::string usableChars = "0123456789!£$%&/()=?^[]QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm";
		char c = usableChars[rand() % usableChars.length()];

		new_password.push_back(c);
	}

	m_TextBoxes[PASSWORD].setString(new_password);
	m_TextBoxes[PASSWORD].setSelected(true);
}

void AddAccountState::onConfirmButton()
{
	std::string nome = m_TextBoxes[NOME].getBuff();
	const std::string& nomeutente = m_TextBoxes[NOMEUTENTE].getBuff();
	const std::string& password = m_TextBoxes[PASSWORD].getBuff();

	if (nome.empty() || nomeutente.empty() || password.empty())
	{
		for (uint8_t i = 0; i < m_TextBoxes.size(); i++)
		{
			if (m_TextBoxes[i].getBuff().empty())
			{
				m_TextBoxes[i].getBackground().setOutlineColor(sf::Color::Red);
			}
			else
			{
				m_TextBoxes[i].getBackground().setOutlineColor(sf::Color(128, 128, 128));
			}
		}
		return;
	}

	for (uint8_t i = 0; i < m_TextBoxes.size(); i++)
	{
		m_TextBoxes[i].getBackground().setOutlineColor(sf::Color(128, 128, 128));
	}

	for (char& c : nome)
	{
		if (c >= 'A' && c <= 'Z')
		{
			c += 32;
		}
	}
	if (nome == "settings")
	{
		MessageBox::showMessage
		(
			MessageBox::Type::OK,
			{ 300.f, 125.f },
			"Nome non usabile",
			"Non è possibile usare quel\nnome!"
		);

		return;
	}

	mINI::INIStructure ini;
	DATAFILE.read(ini);

	ini[nome].set
	({
		{ "nome", nomeutente },
		{ "pass", password }
		});
	DATAFILE.write(ini);

	g_Machine.remove();
}
