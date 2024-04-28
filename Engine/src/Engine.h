#pragma once
#include <chrono>

#include "StateMachine.h"

namespace Engine
{
	void RUN(StateRef state, StateMachine& machine);
};