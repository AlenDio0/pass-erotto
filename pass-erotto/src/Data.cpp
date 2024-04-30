#include "Data.h"

namespace Data
{
	void INIT()
	{
		WINDOW_FONT = new sf::Font();
		WINDOW_FONT->loadFromFile("C:/Windows/Fonts/arial.ttf");

		g_Window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGTH), WINDOW_TITLE, WINDOW_STYLE);

		g_Window->setFramerateLimit(WINDOW_FPSLIMIT);
		g_Window->setVerticalSyncEnabled(WINDOW_VSYNC);
	}
};