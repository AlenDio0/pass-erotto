#include "PINState.h"

#include "MainMenuState.h"
#include "CreatePINState.h"

using namespace Data;

PINState::PINState()
{
	m_TextInsertPIN = sf::Text("Inserisci il PIN:", *WINDOW_FONT, 40u);
	m_TextInsertPIN.setPosition({ 25.f, WINDOW_HEIGTH / 6.f });
	m_TextInsertPIN.setStyle(sf::Text::Bold);
	m_TextInsertPIN.setOutlineThickness(2.f);

	m_TextBoxPIN = TextBox(*WINDOW_FONT, 20u, sf::Color::Black, 16u);
	m_TextBoxPIN.setPosition({ 25.f, WINDOW_HEIGTH / 3.f });
	m_TextBoxPIN.setPlaceHolder("PIN");

	m_ButtonConfirm = TextButton(*WINDOW_FONT, "Conferma", 20u, sf::Color::Black);
	m_ButtonConfirm.setPosition({ WINDOW_WIDTH - 150.f, WINDOW_HEIGTH / 1.25f });
}

void PINState::init()
{
	g_Window->setTitle(WINDOW_TITLE + ": Inserire il PIN");
}

void PINState::pollEvent()
{
	for (sf::Event event; g_Window->pollEvent(event);)
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			g_Window->close();
			break;
		case sf::Event::MouseMoved:
			if (m_ButtonConfirm.isCursorOn(*g_Window))
			{
				m_ButtonConfirm.setHighlight(true);
			}
			else
			{
				m_ButtonConfirm.setHighlight(false);
			}
			break;
		case sf::Event::MouseButtonPressed:
			if (m_TextBoxPIN.isCursorOn(*g_Window))
			{
				m_TextBoxPIN.setSelected(true);
			}
			else
			{
				m_TextBoxPIN.setSelected(false);
			}

			if (m_ButtonConfirm.isCursorOn(*g_Window))
			{
				if (m_PIN == m_TextBoxPIN.getBuff())
				{
					g_Machine.add(StateRef(new MainMenuState()), true);
				}
				else
				{
					//TODO: comparsa errore
				}
			}
			break;
		case sf::Event::TextEntered:
			m_TextBoxPIN.onType(event);
			break;
		}
	}
}

void PINState::update()
{
	static bool loadedPIN = false;

	if (!loadedPIN)
	{
		if (!loadPIN())
		{
			g_Machine.add(StateRef(new CreatePINState()), false);
		}
		else
		{
			loadedPIN = true;
		}
	}

	m_TextBoxPIN.update();
}

void PINState::render()
{
	g_Window->clear(WINDOW_BACKGROUND);

	g_Window->draw(m_TextInsertPIN);

	m_TextBoxPIN.render(g_Window);

	m_ButtonConfirm.render(g_Window);

	g_Window->display();
}

bool PINState::loadPIN()
{
	mINI::INIStructure ini;
	SETTINGSDATAFILE.read(ini);

	if (ini["settings"]["pin"].empty())
	{
		return false;
	}

	m_PIN = ini["settings"]["pin"];
	return true;
}
