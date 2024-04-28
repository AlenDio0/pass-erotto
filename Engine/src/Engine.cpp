#include "Engine.h"

void Engine::run(StateRef state)
{
	const std::chrono::microseconds FRAME_DURATION(16667);
	std::chrono::microseconds lag(0);
	std::chrono::steady_clock::time_point previousTime = std::chrono::steady_clock::now();

	m_Machine.add(std::move(state), false);
	do
	{
		std::chrono::microseconds delta_time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - previousTime);
		lag += delta_time;
		previousTime += delta_time;

		m_Machine.updateStateChanges();
		if (!m_Machine.getCurrentState())
			break;

		while (FRAME_DURATION <= lag)
		{
			lag -= FRAME_DURATION;

			m_Machine.getCurrentState()->pollEvent();

			m_Machine.getCurrentState()->update();

			if (FRAME_DURATION > lag)
				m_Machine.getCurrentState()->render();
		}
	} while (true);
}