#include "Engine.h"

void Engine::RUN(StateRef state, StateMachine& machine)
{
	const std::chrono::microseconds FRAME_DURATION(16667);
	std::chrono::microseconds lag(0);
	std::chrono::steady_clock::time_point previousTime = std::chrono::steady_clock::now();

	machine.add(std::move(state), false);
	do
	{
		std::chrono::microseconds delta_time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - previousTime);
		lag += delta_time;
		previousTime += delta_time;

		machine.updateStateChanges();
		if (!machine.getCurrentState())
			break;

		while (FRAME_DURATION <= lag)
		{
			lag -= FRAME_DURATION;

			machine.getCurrentState()->pollEvent();

			machine.getCurrentState()->update();

			if (FRAME_DURATION > lag)
				machine.getCurrentState()->render();
		}
	} while (true);
}