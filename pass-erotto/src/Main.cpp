#include <SFML\Graphics.hpp>
#include "Data.h"
#include "Engine.h"

int main()
{
	Data::INIT();

	Engine::RUN(StateRef(), Data::s_Machine);

	return 0;
}