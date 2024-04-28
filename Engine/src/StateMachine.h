#pragma once
#include <stack>
#include <memory>

#include "State.h"

typedef std::unique_ptr<State> StateRef;

class StateMachine
{
public:
	StateMachine();
	virtual ~StateMachine();

	void add(StateRef state, bool replacing = true);
	void remove();

	StateRef& getCurrentState();

	void updateStateChanges();
private:
	std::stack<StateRef> m_States;
	StateRef m_NewState;

	bool m_Adding;
	bool m_Removing;
	bool m_Replacing;
};