#include <SFML\Graphics.hpp>
#include "Data.h"
#include "Engine.h"

#include "PINState.h"

int main()
{
	Data::INIT();

	Engine::RUN(StateRef(new PINState()), Data::g_Machine);

	return 0;
}