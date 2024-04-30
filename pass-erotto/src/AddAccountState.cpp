#include "AddAccountState.h"

using namespace Data;

AddAccountState::AddAccountState()
{
	const uint8_t CHAR_SIZE = 20u;
	const float X_POS = 10.f, Y_POS = 75.f, Y_SPACING = 100.f;

	m_TextBoxes[Box::NOME] = TextBox(*WINDOW_FONT, CHAR_SIZE, sf::Color::Black, 16u);
	m_TextBoxes[Box::NOME].setPlaceHolder("Nome (Gmail Lavoro, ...)");

	m_TextBoxes[Box::NOMEUTENTE] = TextBox(*WINDOW_FONT, CHAR_SIZE, sf::Color::Black, 16u);
	m_TextBoxes[Box::NOMEUTENTE].setPlaceHolder("Nome utente (nome@gmail, ...)");

	m_TextBoxes[Box::PASSWORD] = TextBox(*WINDOW_FONT, CHAR_SIZE, sf::Color::Black, 16u);
	m_TextBoxes[Box::PASSWORD].setPlaceHolder("Password");

	for (uint8_t i = 0; i < m_TextBoxes.size(); i++)
	{
		m_TextBoxes[i].setPosition({ X_POS, Y_POS + Y_SPACING * i });
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

						//TODO: Save data
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
		m_TextBoxes[i].render(g_Window);
	}

	for (uint8_t i = 0; i < m_Buttons.size(); i++)
	{
		m_Buttons[i].render(g_Window);
	}

	g_Window->display();
}
