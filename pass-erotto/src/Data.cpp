#include "Data.h"

namespace Data
{
	void INIT()
	{
		WINDOW_FONT = new sf::Font();
		WINDOW_FONT->loadFromFile("C:/Windows/Fonts/arial.ttf");

		rWindow = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGTH), WINDOW_TITLE, WINDOW_STYLE);

		rWindow->setFramerateLimit(WINDOW_FPSLIMIT);
		rWindow->setVerticalSyncEnabled(WINDOW_VSYNC);
	}
};