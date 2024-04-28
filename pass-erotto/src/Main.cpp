#include <SFML\Graphics.hpp>
#include "Engine.h"

int main()
{
	Engine::get().run(StateRef());

	return 0;
}