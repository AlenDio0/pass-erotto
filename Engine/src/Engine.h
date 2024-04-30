#pragma once
#include <chrono>

#include <SFML\Graphics\RenderWindow.hpp>
#include "StateMachine.h"

namespace Engine
{
	void RUN(StateRef state, StateMachine& machine, sf::RenderWindow& window);
};