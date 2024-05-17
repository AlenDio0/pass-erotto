#include "CreatePINState.h"

using namespace Data;

CreatePINState::CreatePINState()
{
	const uint8_t CHAR_SIZE = 40u;
	const float X_AXISPOS = WINDOW_WIDTH / 2.f, Y_POS = WINDOW_HEIGTH / 6.f;

	m_TextBoxPIN = TextBox(*WINDOW_FONT, 20u, sf::Color::Black, 16u);
	m_TextBoxPIN.setPosition
	({
		X_AXISPOS - m_TextBoxPIN.getBackground().getSize().x / 2.f,
		Y_POS + m_TextBoxPIN.getBackground().getSize().y * 2.f
		});
	m_TextBoxPIN.setPlaceHolder("Nuovo PIN");

	m_TextInsertPIN = sf::Text("Crea il nuovo PIN:", *WINDOW_FONT, 30u);
	m_TextInsertPIN.setPosition({ m_TextBoxPIN.getBackground().getPosition().x, Y_POS });
	m_TextInsertPIN.setStyle(sf::Text::Bold);
	m_TextInsertPIN.setOutlineThickness(2.f);

	m_Buttons[Button::ANNULLA] = TextButton(*WINDOW_FONT, "< Annulla", 25u);
	m_Buttons[Button::ANNULLA].setPosition({ 25.f, 25.f });

	m_Buttons[Button::CONFERMA] = TextButton(*WINDOW_FONT, "Conferma", CHAR_SIZE);
	m_Buttons[Button::CONFERMA].setPosition
	({ X_AXISPOS - m_Buttons[Button::CONFERMA].getBackground().getGlobalBounds().getSize().x / 2.f, WINDOW_HEIGTH / 1.5f });
}

void CreatePINState::init()
{
	g_Window->setTitle(WINDOW_TITLE + ": Crea nuovo PIN");
}

void CreatePINState::pollEvent()
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
			m_TextBoxPIN.onType(event);
			break;
		}
	}
}

void CreatePINState::update()
{
	m_TextBoxPIN.update();
}

void CreatePINState::render()
{
	g_Window->clear(WINDOW_BACKGROUND);

	g_Window->draw(m_TextInsertPIN);

	m_TextBoxPIN.render(g_Window);

	for (uint8_t i = 0; i < m_Buttons.size(); i++)
	{
		m_Buttons[i].render(g_Window);
	}

	g_Window->display();
}

void CreatePINState::onMouseMovement()
{
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

void CreatePINState::onMouseButtonPressed()
{
	for (uint8_t i = 0; i < m_Buttons.size(); i++)
	{
		if (m_Buttons[i].isCursorOn(*g_Window))
		{
			switch (i)
			{
			case Button::CONFERMA:
				if (m_TextBoxPIN.getBuff().empty())
				{
					m_TextBoxPIN.getBackground().setOutlineColor(sf::Color::Red);
					break;
				}

				{
					mINI::INIStructure ini;
					DATAFILE.read(ini);

					ini["settings"]["pin"] = m_TextBoxPIN.getBuff();

					DATAFILE.write(ini);

					g_Machine.remove();
				}
				break;
			case Button::ANNULLA:
				g_Machine.remove();
				break;
			}
		}
	}

	if (m_TextBoxPIN.isCursorOn(*g_Window))
	{
		m_TextBoxPIN.setSelected(true);
	}
	else
	{
		m_TextBoxPIN.setSelected(false);
	}
}
