#include "Data.h"

namespace Data
{
	void INIT()
	{
		s_Window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGTH), WINDOW_TITLE, WINDOW_STYLE);

		s_Window->setFramerateLimit(WINDOW_FPSLIMIT);
		s_Window->setVerticalSyncEnabled(WINDOW_VSYNC);
	}
};