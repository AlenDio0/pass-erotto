#include "TextBox.h"

TextBox::TextBox(sf::Font& font, const uint16_t& charSize, const sf::Color& color, const uint16_t& size)
	: m_Size(size != 0 ? size : 16u), m_TextColor(color), m_IsSelected(false)
{
	m_Text.setFont(font);
	m_Text.setCharacterSize(charSize);
	m_Text.setFillColor(m_TextColor);

	m_Background.setSize({ (float)(charSize * m_Size) + 10.f, (float)(charSize * 1.5f) });

	m_Background.setOutlineThickness(2.f);
	m_Background.setOutlineColor(sf::Color(100, 100, 100));
	m_Background.setFillColor(sf::Color::White);

	setPosition({ 0.f, 0.f });
}

sf::Text& TextBox::getText()
{
	return m_Text;
}

sf::RectangleShape& TextBox::getBackground()
{
	return m_Background;
}

const std::string TextBox::getBuff() const
{
	return m_Buff.str();
}

void TextBox::setPosition(const sf::Vector2f& position)
{
	m_Background.setPosition(position);
	m_Text.setPosition(position.x + 5.f, position.y);
}

void TextBox::setPlaceHolder(const std::string& placeholder)
{
	m_PlaceHolderStr = placeholder;

	togglePlaceHolder(true);
}

void TextBox::setSelected(const bool& selected)
{
	m_IsSelected = selected;

	m_Text.setString(m_Buff.str());

	if (!m_IsSelected)
	{
		togglePlaceHolder(true);
	}
	else if (m_Text.getFillColor() != m_TextColor)
	{
		togglePlaceHolder(false);
	}
}

bool TextBox::isCursorOn(const sf::WindowBase& window)
{
	return m_Background.getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(window));
}

void TextBox::onType(sf::Event input)
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
	if (!m_IsSelected || isOverLimit())
	{
		return;
	}

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

void TextBox::render(sf::RenderTarget* target) const
{
	target->draw(m_Background);
	target->draw(m_Text);
}

bool TextBox::isOverLimit() const
{
	if (m_Text.findCharacterPos(m_Buff.str().length()).x < m_Background.getPosition().x + m_Background.getSize().x - 10.f)
	{
		return false;
	}

	return true;
}

void TextBox::togglePlaceHolder(const bool& hide)
{
	if (hide && m_Buff.str().empty())
	{
		m_Text.setStyle(sf::Text::Style::Italic);
		m_Text.setFillColor(sf::Color(128, 128, 128, 200));
		m_Text.setString(m_PlaceHolderStr);
	}
	else if (!hide)
	{
		m_Text.setStyle(sf::Text::Style::Regular);
		m_Text.setFillColor(m_TextColor);
	}
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

			t.erase(t.end() - 1, t.end());
			m_Buff.str("");
			m_Buff << t;
		}

		togglePlaceHolder(true);
		break;
	case ENTER_KEY:
	case ESCAPE_KEY:
		setSelected(false);
		return;
	default:
		m_Buff << (char)typedChar;
		break;
	}

	if (m_Text.getFillColor() != m_TextColor)
	{
		togglePlaceHolder(false);
	}

	m_Text.setString(m_Buff.str());

	m_Blink.restart();
}
