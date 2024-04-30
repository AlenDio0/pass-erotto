#pragma once
#include "State.h"

#include "Data.h"

#include <vector>
#include <unordered_map>
#include "TextButton.h"

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
	sf::RectangleShape m_Background;

	class Account
	{
	public:
		Account() = default;
		inline Account(const std::string& name)
		{
			m_TextName = sf::Text(name, *Data::WINDOW_FONT, 18u);
			m_TextName.setFillColor(sf::Color::Black);
			m_Background = sf::RectangleShape({ Data::WINDOW_WIDTH - 100.f, 100.f });
			m_Background.setOutlineThickness(3.f);
			m_Background.setOutlineColor(sf::Color(128, 128, 128));

			m_ButtonView = TextButton(*Data::WINDOW_FONT, "Vedi", 19u, sf::Color::Black);
			m_ButtonModify = TextButton(*Data::WINDOW_FONT, "Modifica", 19u, sf::Color::Black);
			m_ButtonDelete = TextButton(*Data::WINDOW_FONT, "Elimina", 19u, sf::Color::Red);

			setPosition({ 0.f, 0.f });
		}

		inline TextButton& getButtonView()
		{
			return m_ButtonView;
		}
		inline TextButton& getButtonModify()
		{
			return m_ButtonModify;
		}
		inline TextButton& getButtonDelete()
		{
			return m_ButtonDelete;
		}

		inline const std::string& getUsername() const
		{
			return m_Username;
		}
		inline const std::string& getPassword() const
		{
			return m_Password;
		}

		inline void setUsername(const std::string& username)
		{
			m_Username = username;
		}
		inline void setPassword(const std::string& password)
		{
			m_Password = password;
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

			m_ButtonModify.setPosition
			({
				m_ButtonDelete.getBackground().getPosition().x - m_ButtonModify.getBackground().getSize().x - 25.f,
				position.y + m_Background.getSize().y - m_ButtonModify.getBackground().getSize().y - 10.f
				});

			m_ButtonView.setPosition
			({
				m_ButtonModify.getBackground().getPosition().x - m_ButtonView.getBackground().getSize().x - 25.f,
				position.y + m_Background.getSize().y - m_ButtonView.getBackground().getSize().y - 10.f
				});
		}

		inline void render(sf::RenderTarget* target)
		{
			target->draw(m_Background);
			target->draw(m_TextName);
			m_ButtonView.render(target);
			m_ButtonModify.render(target);
			m_ButtonDelete.render(target);
		}
	private:
		sf::Text m_TextName;
		sf::RectangleShape m_Background;

		TextButton m_ButtonView;
		TextButton m_ButtonModify;
		TextButton m_ButtonDelete;

		std::string m_Username;
		std::string m_Password;
	};
	std::vector<Account> m_Accounts;

	std::unordered_map<uint8_t, TextButton> m_Buttons;
	enum Button : uint8_t
	{
		AGGIUNGI,
		RITORNA,
	};

	void loadAccounts();
};

