#include "PINState.h"

using namespace Data;

PINState::PINState()
{
	if (!loadPIN())
	{
		//CREATE PIN
		m_EncryptedPIN = "0000";
	}

	m_TextPIN.setFont(*WINDOW_FONT);
	m_TextPIN.setPosition(50.f, 100.f);
	m_TextPIN.setFillColor(sf::Color(100, 100, 100));
	m_TextPIN.setCharacterSize(30u);
}

void PINState::pollEvent()
{
	if (!s_Window)
	{
		return;
	}

	sf::Event event;
	while (s_Window->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			s_Window->close();
			break;
		case sf::Event::KeyPressed:
			if (sf::Keyboard::isKeyPressed(event.key.code))
			{
				m_TextPIN.setString(m_TextPIN.getString() + (char)event.key.code);
			}
			break;
		}
	}
}

void PINState::update()
{
}

void PINState::render()
{
	s_Window->clear(WINDOW_BACKGROUND);

	s_Window->draw(m_TextPIN);

	s_Window->display();
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
