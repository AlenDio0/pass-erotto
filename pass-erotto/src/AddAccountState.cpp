#include "AddAccountState.h"

using namespace Data;

AddAccountState::AddAccountState()
{
	const uint8_t CHAR_SIZE1 = 25u, CHAR_SIZE2 = 20u;
	const float X_POS = 25.f, Y_POS = 125.f;
	const float Y_SPACING = 100.f;

	m_Texts[Box::NOME] = sf::Text("Nome:", *WINDOW_FONT, CHAR_SIZE1);
	m_TextBoxes[Box::NOME] = TextBox(*WINDOW_FONT, CHAR_SIZE2, sf::Color::Black, 16u);
	m_TextBoxes[Box::NOME].setPlaceHolder("Nome (Gmail Lavoro, ...)");

	m_Texts[Box::NOMEUTENTE] = sf::Text("Nome utente:", *WINDOW_FONT, CHAR_SIZE1);
	m_TextBoxes[Box::NOMEUTENTE] = TextBox(*WINDOW_FONT, CHAR_SIZE2, sf::Color::Black, 16u);
	m_TextBoxes[Box::NOMEUTENTE].setPlaceHolder("Nome utente (nome@gmail, ...)");

	m_Texts[Box::PASSWORD] = sf::Text("Password:", *WINDOW_FONT, CHAR_SIZE1);
	m_TextBoxes[Box::PASSWORD] = TextBox(*WINDOW_FONT, CHAR_SIZE2, sf::Color::Black, 16u);
	m_TextBoxes[Box::PASSWORD].setPlaceHolder("Password");

	for (uint8_t i = 0; i < m_TextBoxes.size(); i++)
	{
		m_TextBoxes[i].setPosition({ X_POS, Y_POS + Y_SPACING * i });
		m_Texts[i].setPosition({ X_POS, Y_POS + Y_SPACING * i - m_TextBoxes[i].getBackground().getGlobalBounds().getSize().y });
		m_Texts[i].setOutlineThickness(2.f);
	}

	m_Buttons[Button::CONFERMA] = TextButton(*WINDOW_FONT, "Conferma", 30u);
	m_Buttons[Button::CONFERMA].setPosition
	({
		WINDOW_WIDTH - m_Buttons[Button::CONFERMA].getBackground().getGlobalBounds().getSize().x - 50.f,
		WINDOW_HEIGTH - m_Buttons[Button::CONFERMA].getBackground().getGlobalBounds().getSize().y - 50.f
		});
	m_Buttons[Button::ANNULLA] = TextButton(*WINDOW_FONT, "Annulla", 30u);
	m_Buttons[Button::ANNULLA].setPosition
	({
		50.f,
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
					case Button::CONFERMA:
					{
						const std::string& nome = m_TextBoxes[Box::NOME].getBuff();
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
							break;
						}

						mINI::INIStructure ini;
						DATAFILE.read(ini);

						ini[nome].set
						({
							{ "nome", nomeutente },
							{ "pass", password }
							});
						DATAFILE.write(ini);
					}
					g_Machine.remove();
					break;
					case Button::ANNULLA:
						g_Machine.remove();
						break;
					}
				}
			}
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

	g_Window->display();
}
