#pragma once
#include "State.h"

#include "Data.h"

#include <vector>
#include <unordered_map>
#include "AccountInfo.h"
#include "TextButton.h"
#include "TextBox.h"
#include "Notify.h"

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
			m_TextName = sf::Text("", *Data::WINDOW_FONT, 18u);
			m_TextName.setFillColor(sf::Color::Black);
			m_Background = sf::RectangleShape({ Data::WINDOW_WIDTH - 100.f, 100.f });
			m_Background.setOutlineThickness(3.f);
			m_Background.setOutlineColor(sf::Color(128, 128, 128));

			m_ButtonView = TextButton(*Data::WINDOW_FONT, "Mostra", 19u, sf::Color::Black);
			m_ButtonEdit = TextButton(*Data::WINDOW_FONT, "Modifica", 19u, sf::Color::Black);
			m_ButtonDelete = TextButton(*Data::WINDOW_FONT, "Elimina", 19u, sf::Color::Red);

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
			m_Background.setPosition(position);
			m_TextName.setPosition(position.x + 10.f, position.y + 10.f);

			m_ButtonDelete.setPosition
			({
				m_Background.getSize().x - m_ButtonDelete.getBackground().getSize().x,
				position.y + m_Background.getSize().y - m_ButtonDelete.getBackground().getSize().y - 10.f
				});

			m_ButtonEdit.setPosition
			({
				m_ButtonDelete.getBackground().getPosition().x - m_ButtonEdit.getBackground().getSize().x - 25.f,
				position.y + m_Background.getSize().y - m_ButtonEdit.getBackground().getSize().y - 10.f
				});

			m_ButtonView.setPosition
			({
				m_ButtonEdit.getBackground().getPosition().x - m_ButtonView.getBackground().getSize().x - 25.f,
				position.y + m_Background.getSize().y - m_ButtonView.getBackground().getSize().y - 10.f
				});
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

	std::unordered_map<uint8_t, TextButton> m_Buttons;
	enum Button : uint8_t
	{
		AGGIUNGI,
		INDIETRO,
	};

	class Notify_ViewAccount : public Notify
	{
	public:
		Notify_ViewAccount() = default;
		inline Notify_ViewAccount(const std::string& header)
			: Notify(*Data::WINDOW_FONT, { 350.f, 200.f }, header)
		{
			m_TextHeader.setCharacterSize(25u);
			m_TextHeader.setStyle(sf::Text::Bold);

			m_TextContents.setCharacterSize(15u);

			m_Buttons[Button::OK] = TextButton(*Data::WINDOW_FONT, "Ok", 20u);

			setPosition({ Data::WINDOW_WIDTH / 2.f - 350.f / 2.f, Data::WINDOW_HEIGTH / 2.f - 200.f / 2.f });
		}

		enum Button : uint8_t
		{
			OK,
		};

		inline void setPosition(const sf::Vector2f& position) override
		{
			setInPosition(position);

			m_Buttons[Button::OK].setPosition
			({ position.x + m_Background.getSize().x - m_Buttons[Button::OK].getBackground().getSize().x - 10.f,
				position.y + m_Background.getSize().y - m_Buttons[Button::OK].getBackground().getSize().y - 10.f
				});
		}
	private:

	};
	Notify_ViewAccount m_NotifyViewAccount;

	class Notify_DeleteAccount : public Notify
	{
	public:
		Notify_DeleteAccount() = default;
		inline Notify_DeleteAccount(const std::string& accname)
			: Notify(*Data::WINDOW_FONT, { 350.f, 200.f }, "Sei sicuro?"), m_AccountName(accname)
		{
			m_TextHeader.setCharacterSize(25u);
			m_TextHeader.setStyle(sf::Text::Bold);

			m_TextContents.setCharacterSize(15u);

			m_Buttons[Button::CONFERMA] = TextButton(*Data::WINDOW_FONT, "Conferma", 20u);
			m_Buttons[Button::ANNULLA] = TextButton(*Data::WINDOW_FONT, "Annulla", 20u);

			setPosition({ Data::WINDOW_WIDTH / 2.f - 350.f / 2.f, Data::WINDOW_HEIGTH / 2.f - 200.f / 2.f });
		}

		enum Button : uint8_t
		{
			CONFERMA,
			ANNULLA,
		};

		const std::string& getName() const
		{
			return m_AccountName;
		}

		inline void setPosition(const sf::Vector2f& position) override
		{
			setInPosition(position);

			m_Buttons[Button::CONFERMA].setPosition
			({ position.x + m_Background.getSize().x - m_Buttons[Button::CONFERMA].getBackground().getSize().x - 10.f,
				position.y + m_Background.getSize().y - m_Buttons[Button::CONFERMA].getBackground().getSize().y - 10.f
				});

			m_Buttons[Button::ANNULLA].setPosition
			({ position.x + m_Buttons[Button::ANNULLA].getBackground().getSize().x + 10.f,
				position.y + m_Background.getSize().y - m_Buttons[Button::ANNULLA].getBackground().getSize().y - 10.f
				});
		}
	private:
		std::string m_AccountName;
	};
	Notify_DeleteAccount m_NotifyDeleteAccount;

	void loadAccounts();
};

