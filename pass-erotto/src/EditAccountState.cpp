#include "EditAccountState.h"

using namespace Data;

EditAccountState::EditAccountState(const AccountInfo& account)
{
	m_OriginalAccountInfo = account;

	const uint8_t CHAR_SIZE1 = 30u, CHAR_SIZE2 = 25u, CHAR_SIZE3 = 20u, CHAR_SIZE4 = 18u;
	const float X_AXISPOS = WINDOW_WIDTH / 2.f, Y_POS = 125.f;
	const float Y_SPACING = 100.f;

	m_Texts[Box::NOME] = sf::Text("Nome:", *WINDOW_FONT, CHAR_SIZE2);
	m_TextBoxes[Box::NOME] = TextBox(*WINDOW_FONT, CHAR_SIZE3, sf::Color::Black, 16u);
	m_TextBoxes[Box::NOME].setPlaceHolder(m_OriginalAccountInfo.name);

	m_Texts[Box::NOMEUTENTE] = sf::Text("Nome utente:", *WINDOW_FONT, CHAR_SIZE2);
	m_TextBoxes[Box::NOMEUTENTE] = TextBox(*WINDOW_FONT, CHAR_SIZE4, sf::Color::Black, 20u);
	m_TextBoxes[Box::NOMEUTENTE].setPlaceHolder(m_OriginalAccountInfo.username);

	m_Texts[Box::PASSWORD] = sf::Text("Password:", *WINDOW_FONT, CHAR_SIZE2);
	m_TextBoxes[Box::PASSWORD] = TextBox(*WINDOW_FONT, CHAR_SIZE3, sf::Color::Black, 16u);
	m_TextBoxes[Box::PASSWORD].setPlaceHolder("********");

	for (uint8_t i = 0; i < m_TextBoxes.size(); i++)
	{
		m_TextBoxes[i].setPosition({ X_AXISPOS - m_TextBoxes[i].getBackground().getSize().x / 2.f, Y_POS + Y_SPACING * i });
		m_Texts[i].setPosition({ X_AXISPOS - m_Texts[i].getGlobalBounds().getSize().x / 2.f, Y_POS + Y_SPACING * i - m_TextBoxes[i].getBackground().getGlobalBounds().getSize().y });
		m_Texts[i].setOutlineThickness(2.f);
	}

	m_Buttons[Button::CONFERMA] = TextButton(*WINDOW_FONT, "Conferma", CHAR_SIZE1);
	m_Buttons[Button::CONFERMA].setPosition
	({
		X_AXISPOS * 1.5f - m_Buttons[Button::CONFERMA].getBackground().getGlobalBounds().getSize().x / 2.f,
		WINDOW_HEIGTH - m_Buttons[Button::CONFERMA].getBackground().getGlobalBounds().getSize().y - 50.f
		});
	m_Buttons[Button::ANNULLA] = TextButton(*WINDOW_FONT, "Annulla", CHAR_SIZE1);
	m_Buttons[Button::ANNULLA].setPosition
	({
		X_AXISPOS / 2.f - m_Buttons[Button::ANNULLA].getBackground().getGlobalBounds().getSize().x / 2.f,
		WINDOW_HEIGTH - m_Buttons[Button::ANNULLA].getBackground().getGlobalBounds().getSize().y - 50.f
		});
}

void EditAccountState::init()
{
	g_Window->setTitle(WINDOW_TITLE + ": Modifica account");
}

void EditAccountState::onConfirmButton()
{
	AccountInfo info;

	info.name = m_TextBoxes[Box::NOME].getBuff().empty() ? m_OriginalAccountInfo.name : m_TextBoxes[Box::NOME].getBuff();

	info.username = m_TextBoxes[Box::NOMEUTENTE].getBuff().empty() ? m_OriginalAccountInfo.username : m_TextBoxes[Box::NOMEUTENTE].getBuff();

	info.password = m_TextBoxes[Box::PASSWORD].getBuff().empty() ? m_OriginalAccountInfo.password : m_TextBoxes[Box::PASSWORD].getBuff();

	for (char& c : info.name)
	{
		if (c >= 'A' && c <= 'Z')
		{
			c += 32;
		}
	}
	if (info.name == "settings")
	{
		m_NotifyBadName = Notify_BadName();
		m_NotifyBadName.setActive(true);

		return;
	}

	mINI::INIStructure ini;
	DATAFILE.read(ini);

	if (info.name != m_OriginalAccountInfo.name)
	{
		ini.remove(m_OriginalAccountInfo.name);
	}

	ini[info.name].set
	({
		{ "nome", info.username },
		{ "pass", info.password }
		});
	DATAFILE.write(ini);

	g_Machine.remove();
}
