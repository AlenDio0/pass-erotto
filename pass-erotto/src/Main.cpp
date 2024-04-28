#include <SFML\Graphics.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(600, 600), "Title");

	sf::CircleShape circle(100.f);
	circle.setFillColor(sf::Color::Red);

	while (window.isOpen())
	{
		for (sf::Event e; window.pollEvent(e);)
		{
			switch (e.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			}
		}

		window.clear();

		window.draw(circle);

		window.display();
	}

	return 0;
}