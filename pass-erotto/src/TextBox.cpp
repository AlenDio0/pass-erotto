#include "TextBox.h"

TextBox::TextBox(sf::Font& font, const uint16_t& charSize, const sf::Color& color, const uint16_t& limit)
	: m_Limit(limit != 0 ? limit : 16u), m_IsSelected(false)
{
	m_Text.setFont(font);
	m_Text.setCharacterSize(charSize);
	m_Text.setFillColor(color);

	m_Background.setSize({ (float)(charSize * m_Limit) + 10.f, (float)(charSize * 1.5f) });

	m_Background.setOutlineThickness(2.f);
	m_Background.setOutlineColor(sf::Color(100, 100, 100));
	m_Background.setFillColor(sf::Color::White);

	setPosition({ 0.f, 0.f });
}

void TextBox::setPosition(const sf::Vector2f& position)
{
	m_Background.setPosition(position);
	m_Text.setPosition(position.x + 5.f, position.y);
}

void TextBox::setLimit(const uint16_t& limit)
{
	m_Limit = limit;
}

void TextBox::setSelected(const bool& selected)
{
	m_IsSelected = selected;

	m_Text.setString(m_Buff.str());
}

void TextBox::typedOn(sf::Event input)
{
	if (!m_IsSelected)
	{
		return;
	}

	int typedChar = input.text.unicode;

	if (typedChar >= 128)
	{
		return;
	}

	while (isOverLimit())
	{
		if (typedChar == DELETE_KEY)
		{
			break;
		}

		return;
	}

	inputLogic(typedChar);
}

void TextBox::update()
{
	if (m_Blink.getElapsedTime().asMilliseconds() >= 500)
	{
		static bool blink = false;
		blink = !blink;

		if (blink)
		{
			m_Text.setString(m_Buff.str() + "|");
		}
		else
		{
			m_Text.setString(m_Buff.str());
		}

		m_Blink.restart();
	}
}

void TextBox::render(sf::RenderWindow* target) const
{
	target->draw(m_Background);
	target->draw(m_Text);
}

bool TextBox::isOverLimit() const
{
	return m_Limit != 0 && m_Buff.str().length() >= m_Limit;
}

void TextBox::inputLogic(const int& typedChar)
{
	switch (typedChar)
	{
	case DELETE_KEY:
		if (m_Buff.str().empty())
		{
			return;
		}

		{
			std::string t = m_Buff.str();
			std::string n;
			for (int i = 0; i < t.length() - 1; i++)
			{
				n += t[i];
			}

			m_Buff.str("");
			m_Buff << n;
		}
		break;
	case ENTER_KEY:
		setSelected(false);
		return;
	case ESCAPE_KEY:
		return;
	default:
		m_Buff << (char)typedChar;
		break;
	}

	m_Text.setString(m_Buff.str());

	m_Blink.restart();
}
