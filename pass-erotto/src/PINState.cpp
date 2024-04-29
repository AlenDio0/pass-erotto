#include "PINState.h"

using namespace Data;

PINState::PINState()
{
	rWindow->setTitle(WINDOW_TITLE + ": Inserire il PIN");

	if (!loadPIN())
	{
		//CREATE PIN
		m_EncryptedPIN = "0000";
	}

	m_TextInsertPIN = sf::Text("Inserisci il PIN:", *WINDOW_FONT, 40u);
	m_TextInsertPIN.setPosition({ 25.f, WINDOW_HEIGTH / 6.f });
	m_TextInsertPIN.setStyle(sf::Text::Bold);
	m_TextInsertPIN.setOutlineThickness(2.f);

	m_TextBoxPIN = TextBox(*WINDOW_FONT, 20u, sf::Color::Black, 16u);
	m_TextBoxPIN.setPosition({ 25.f, WINDOW_HEIGTH / 3.f });
	m_TextBoxPIN.setPlaceHolder("PIN");
}

void PINState::pollEvent()
{
	for (sf::Event event; rWindow->pollEvent(event);)
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			rWindow->close();
			break;
		case sf::Event::TextEntered:
			m_TextBoxPIN.onType(event);
			break;
		case sf::Event::MouseButtonPressed:
			if (m_TextBoxPIN.isCursorOn(*rWindow))
			{
				m_TextBoxPIN.setSelected(true);
			}
			else
			{
				m_TextBoxPIN.setSelected(false);
			}
			break;
		}
	}
}

void PINState::update()
{
	m_TextBoxPIN.update();
}

void PINState::render()
{
	rWindow->clear(WINDOW_BACKGROUND);

	rWindow->draw(m_TextInsertPIN);

	m_TextBoxPIN.render(rWindow);

	rWindow->display();
}

bool PINState::loadPIN()
{
	std::ifstream file("data");

	if (!file.is_open())
	{
		return false;
	}

	std::string buff;
	while (!file.eof())
	{
		file >> buff;

		if (buff == "pin")
		{
			file >> m_EncryptedPIN;
			return true;
		}
	}

	return false;
}
