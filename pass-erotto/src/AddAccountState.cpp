#include "AddAccountState.h"

using namespace Data;

AddAccountState::AddAccountState()
{
	srand((unsigned)time(NULL));

	const uint8_t CHAR_SIZE1 = 25u, CHAR_SIZE2 = 20u;
	const float X_AXISPOS = WINDOW_WIDTH / 2.f, Y_POS = 125.f;
	const float Y_SPACING = 100.f;

	m_Texts[Box::NOME] = sf::Text("Nome:", *WINDOW_FONT, CHAR_SIZE1);
	m_TextBoxes[Box::NOME] = TextBox(*WINDOW_FONT, CHAR_SIZE2, sf::Color::Black, 16u);
	m_TextBoxes[Box::NOME].setPlaceHolder("Nome (Gmail Lavoro, ...)");

	m_Texts[Box::NOMEUTENTE] = sf::Text("Nome utente:", *WINDOW_FONT, CHAR_SIZE1);
	m_TextBoxes[Box::NOMEUTENTE] = TextBox(*WINDOW_FONT, CHAR_SIZE2 - 2u, sf::Color::Black, 20u);
	m_TextBoxes[Box::NOMEUTENTE].setPlaceHolder("Nome utente (nome@gmail.com, ...)");

	m_Texts[Box::PASSWORD] = sf::Text("Password:", *WINDOW_FONT, CHAR_SIZE1);
	m_TextBoxes[Box::PASSWORD] = TextBox(*WINDOW_FONT, CHAR_SIZE2, sf::Color::Black, 16u);
	m_TextBoxes[Box::PASSWORD].setPlaceHolder("Password");

	for (uint8_t i = 0; i < m_TextBoxes.size(); i++)
	{
		m_TextBoxes[i].setPosition({ X_AXISPOS - m_TextBoxes[i].getBackground().getSize().x / 2.f, Y_POS + Y_SPACING * i });
		m_Texts[i].setPosition({ X_AXISPOS - m_Texts[i].getGlobalBounds().getSize().x / 2.f, Y_POS + Y_SPACING * i - m_TextBoxes[i].getBackground().getGlobalBounds().getSize().y });
		m_Texts[i].setOutlineThickness(2.f);
	}

	m_Buttons[Button::GENERA] = TextButton(*WINDOW_FONT, "Genera Password", 20u);
	m_Buttons[Button::GENERA].setPosition
	({
		X_AXISPOS - m_Buttons[Button::GENERA].getBackground().getSize().x / 2.f,
		m_TextBoxes[Box::PASSWORD].getBackground().getPosition().y + m_TextBoxes[Box::PASSWORD].getBackground().getSize().y + 20.f
		});
	m_Buttons[Button::CONFERMA] = TextButton(*WINDOW_FONT, "Conferma", 30u);
	m_Buttons[Button::CONFERMA].setPosition
	({
		X_AXISPOS * 1.5f - m_Buttons[Button::CONFERMA].getBackground().getGlobalBounds().getSize().x / 2.f,
		WINDOW_HEIGTH - m_Buttons[Button::CONFERMA].getBackground().getGlobalBounds().getSize().y - 50.f
		});
	m_Buttons[Button::ANNULLA] = TextButton(*WINDOW_FONT, "Annulla", 30u);
	m_Buttons[Button::ANNULLA].setPosition
	({
		X_AXISPOS / 2.f - m_Buttons[Button::ANNULLA].getBackground().getGlobalBounds().getSize().x / 2.f,
		WINDOW_HEIGTH - m_Buttons[Button::ANNULLA].getBackground().getGlobalBounds().getSize().y - 50.f
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

	if (m_NotifyBadName.isActive())
	{
		m_NotifyBadName.render(g_Window);
	}

	g_Window->display();
}

void AddAccountState::onMouseMovement()
{
	if (m_NotifyBadName.isActive())
	{
		TextButton& button = m_NotifyBadName.getButtons()[Notify_BadName::OK];

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
	if (m_NotifyBadName.isActive())
	{
		if (m_NotifyBadName.getButtons()[Notify_BadName::OK].isCursorOn(*g_Window))
		{
			m_NotifyBadName.setActive(false);
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
			case Button::GENERA:
				onGenerateButton();
				break;
			case Button::CONFERMA:
				onConfirmButton();
				break;
			case Button::ANNULLA:
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

	m_TextBoxes[Box::PASSWORD].setString(new_password);
	m_TextBoxes[Box::PASSWORD].setSelected(true);
}

void AddAccountState::onConfirmButton()
{
	std::string nome = m_TextBoxes[Box::NOME].getBuff();
	const std::string& nomeutente = m_TextBoxes[Box::NOMEUTENTE].getBuff();
	const std::string& password = m_TextBoxes[Box::PASSWORD].getBuff();

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

	for (char& c : nome)
	{
		if (c >= 'A' && c <= 'Z')
		{
			c += 32;
		}
	}
	if (nome == "settings")
	{
		m_NotifyBadName = Notify_BadName();
		m_NotifyBadName.setActive(true);

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
