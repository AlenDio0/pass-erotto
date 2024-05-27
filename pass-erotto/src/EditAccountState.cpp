#include "EditAccountState.h"

using namespace Data;

EditAccountState::EditAccountState(const AccountInfo& account)
	: AddAccountState()
{
	srand((unsigned)time(NULL));

	m_OriginalAccountInfo = account;

	m_TextBoxes[NOME].setPlaceHolder(m_OriginalAccountInfo.name);
	m_TextBoxes[NOMEUTENTE].setPlaceHolder(m_OriginalAccountInfo.username);
	m_TextBoxes[PASSWORD].setPlaceHolder("********");
}

void EditAccountState::init()
{
	g_Window->setTitle(WINDOW_TITLE + ": Modifica account");
}

void EditAccountState::onConfirmButton()
{
	AccountInfo info;

	info.name = m_TextBoxes[NOME].getBuff().empty() ? m_OriginalAccountInfo.name : m_TextBoxes[NOME].getBuff();

	info.username = m_TextBoxes[NOMEUTENTE].getBuff().empty() ? m_OriginalAccountInfo.username : m_TextBoxes[NOMEUTENTE].getBuff();

	info.password = m_TextBoxes[PASSWORD].getBuff().empty() ? m_OriginalAccountInfo.password : m_TextBoxes[PASSWORD].getBuff();

	for (char& c : info.name)
	{
		if (c >= 'A' && c <= 'Z')
		{
			c += 32;
		}
	}
	if (info.name == "settings")
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
