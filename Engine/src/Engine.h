#pragma once
#include <chrono>

#include "StateMachine.h"

class Engine
{
public:
	Engine(const Engine&) = delete;

	static Engine& get()
	{
		static Engine s_Instance;
		return s_Instance;
	}

	void run(StateRef state);
private:
	StateMachine m_Machine;

	Engine() = default;
};