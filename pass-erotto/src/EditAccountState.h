#pragma once
#include "State.h"

#include "Data.h"

#include <unordered_map>
#include "TextButton.h"
#include "TextBox.h"
#include "AccountInfo.h"
#include "Notify.h"

class EditAccountState : public State
{
public:
	EditAccountState(const AccountInfo& account);

	void init();

	void pollEvent();
	void update();
	void render();
private:
	AccountInfo m_OriginalAccountInfo;

	std::unordered_map<uint8_t, sf::Text> m_Texts;
	std::unordered_map<uint8_t, TextBox> m_TextBoxes;
	enum Box : uint8_t
	{
		NOME,
		NOMEUTENTE,
		PASSWORD,
	};
	std::unordered_map<uint8_t, TextButton> m_Buttons;
	enum Button : uint8_t
	{
		CONFERMA,
		ANNULLA,
	};

	class Notify_BadName : public Notify
	{
	public:
		inline Notify_BadName()
			: Notify(*Data::WINDOW_FONT, { 300.f, 125.f }, "Nome non usabile")
		{
			m_TextHeader.setCharacterSize(25u);
			m_TextHeader.setStyle(sf::Text::Bold);

			m_TextContents.setCharacterSize(15u);
			setContents("Non è possibile usare quel nome!");

			m_Buttons[Button::OK] = TextButton(*Data::WINDOW_FONT, "Ok", 20u);

			setPosition({ Data::WINDOW_WIDTH / 2.f - 300.f / 2.f, Data::WINDOW_HEIGTH / 2.f - 125.f / 2.f });
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
	Notify_BadName m_NotifyBadName;

	void onMouseMovement();
	void onMouseButtonPressed();

	void onConfirmButton();
};