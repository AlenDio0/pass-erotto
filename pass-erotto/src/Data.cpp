#include "Data.h"

namespace Data
{
	void INIT()
	{
		window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGTH), WINDOW_TITLE, WINDOW_STYLE);
	}
};