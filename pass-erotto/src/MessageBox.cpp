#include "MessageBox.h"

void MessageBox::showMessage(Type type, const sf::Vector2f& size, const std::string& title, const std::string& message)
{
	m_Background = sf::RectangleShape(size);
	m_Background.setOutlineThickness(2.f);
	m_Background.setOutlineColor(sf::Color(128, 128, 128));

	m_TextTitle = sf::Text(title, *Data::WINDOW_FONT, 20u);
	m_TextTitle.setStyle(sf::Text::Style::Bold);
	m_TextTitle.setFillColor(sf::Color::Black);

	m_TextMessage = sf::Text(message, *Data::WINDOW_FONT, 18u);
	m_TextMessage.setFillColor(sf::Color::Black);

	m_Active = true;

	m_Buttons.clear();
	switch (type)
	{
	case Type::OK:
	{
		m_Buttons[Buttons::OK] = TextButton(*Data::WINDOW_FONT, "Ok", 25u);
	}
	break;
	case Type::YESNO:
	{
		m_Buttons[Buttons::SI] = TextButton(*Data::WINDOW_FONT, "Si", 25u);
		m_Buttons[Buttons::NO] = TextButton(*Data::WINDOW_FONT, "No", 25u);
	}
	break;
	}

	setPosition();
}

std::unordered_map<uint8_t, TextButton>& MessageBox::getButtons()
{
	return m_Buttons;
}

void MessageBox::setPosition(sf::Vector2f position)
{
	if (position == sf::Vector2f())
	{
		position = sf::Vector2f(Data::WINDOW_WIDTH / 2.f - m_Background.getSize().x / 2.f, Data::WINDOW_HEIGTH / 2.f - m_Background.getSize().y / 2.f);
	}

	m_Background.setPosition(position);

	m_TextTitle.setPosition(position.x + 10.f, position.y + 10.f);
	m_TextMessage.setPosition(position.x + 10.f, position.y + m_TextTitle.getCharacterSize() + 25.f);

	int i = 0;
	for (auto& it : m_Buttons)
	{
		TextButton* button = &it.second;

		button->setPosition
		({
			position.x + (!i ? m_Background.getSize().x - button->getBackground().getSize().x - 25.f : 25.f),
			position.y + m_Background.getSize().y - button->getBackground().getSize().y - 10.f
			});
		i++;
	}
}

void MessageBox::stop()
{
	m_Active = false;
}

const bool& MessageBox::isActive()
{
	return m_Active;
}

void MessageBox::render(sf::RenderTarget* target)
{
	target->draw(m_Background);

	target->draw(m_TextTitle);
	target->draw(m_TextMessage);

	for (uint8_t i = 0; i < m_Buttons.size(); i++)
	{
		m_Buttons[i].render(target);
	}
}