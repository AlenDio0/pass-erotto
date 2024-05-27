#pragma once
#include "State.h"

#include "Data.h"
#include "Style.h"

#include <vector>
#include <unordered_map>
#include "AccountInfo.h"
#include "TextButton.h"
#include "TextBox.h"
#include "MessageBox.h"

class AccountsPageState : public State
{
public:
	AccountsPageState();

	void init();

	void pollEvent();
	void update();
	void render();
private:
	sf::Text m_TextTitle;
	TextBox m_TextBoxSearch;
	sf::RectangleShape m_Background;

	class Account
	{
	public:
		inline Account()
		{
			const uint8_t CHAR_SIZE1 = 18u, CHAR_SIZE2 = 16u;

			m_TextName = sf::Text("", *Data::WINDOW_FONT, CHAR_SIZE1);
			m_TextName.setFillColor(sf::Color::Black);
			m_Background = sf::RectangleShape({ Data::WINDOW_WIDTH - 100.f, 100.f });
			m_Background.setOutlineThickness(3.f);
			m_Background.setOutlineColor(sf::Color(128, 128, 128));

			m_ButtonView = TextButton(*Data::WINDOW_FONT, "Mostra", CHAR_SIZE2, sf::Color::Black);
			m_ButtonEdit = TextButton(*Data::WINDOW_FONT, "Modifica", CHAR_SIZE2, sf::Color::Black);
			m_ButtonDelete = TextButton(*Data::WINDOW_FONT, "Elimina", CHAR_SIZE2, sf::Color::Red);

			setPosition({ 0.f, 0.f });
		}

		inline TextButton& getButtonView()
		{
			return m_ButtonView;
		}
		inline TextButton& getButtonEdit()
		{
			return m_ButtonEdit;
		}
		inline TextButton& getButtonDelete()
		{
			return m_ButtonDelete;
		}

		inline const AccountInfo& getAccountInfo()
		{
			return m_AccountInfo;
		}

		inline const sf::Vector2f& getSize()
		{
			return m_Background.getSize();
		}

		inline const sf::Vector2f& getPosition()
		{
			return m_Background.getPosition();
		}

		inline void setName(const std::string& name)
		{
			m_AccountInfo.name = name;
			m_TextName.setString(name);
		}
		inline void setUsername(const std::string& username)
		{
			m_AccountInfo.username = username;
		}
		inline void setPassword(const std::string& password)
		{
			m_AccountInfo.password = password;
		}

		inline void setPosition(const sf::Vector2f& position)
		{
			const float OFFSET = 10.f;
			const float X_SPACING = 25.f;
			const float Y_POS = position.y + m_Background.getSize().y - m_ButtonDelete.getBackground().getSize().y - OFFSET;

			m_Background.setPosition(position);
			m_TextName.setPosition(position.x + 10.f, position.y + 10.f);

			m_ButtonDelete.setPosition({ position.x + m_Background.getSize().x - m_ButtonDelete.getBackground().getSize().x - OFFSET, Y_POS });

			m_ButtonEdit.setPosition({ m_ButtonDelete.getBackground().getPosition().x - m_ButtonEdit.getBackground().getSize().x - X_SPACING, Y_POS });

			m_ButtonView.setPosition({ m_ButtonEdit.getBackground().getPosition().x - m_ButtonView.getBackground().getSize().x - X_SPACING, Y_POS });
		}

		inline void render(sf::RenderTarget* target)
		{
			target->draw(m_Background);
			target->draw(m_TextName);
			m_ButtonView.render(target);
			m_ButtonEdit.render(target);
			m_ButtonDelete.render(target);
		}
	private:
		AccountInfo m_AccountInfo;

		sf::Text m_TextName;
		sf::RectangleShape m_Background;

		TextButton m_ButtonView;
		TextButton m_ButtonEdit;
		TextButton m_ButtonDelete;
	};
	std::vector<Account> m_Accounts;
	std::vector<Account*> m_VisibleAccounts;

	const std::string* m_AccountDeleteName;

	std::unordered_map<uint8_t, TextButton> m_Buttons;
	enum Button : uint8_t
	{
		AGGIUNGI,
		INDIETRO,
	};

	void onMouseMovement();
	void onMouseButtonPressed();

	void onScrollPage(const sf::Event& event);

	void updateSearch();
	void onSearch(const std::string& search);

	void loadAccounts();
	void setAccountsInPosition();
};

