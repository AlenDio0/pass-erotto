#include "StateMachine.h"

StateMachine::StateMachine()
	: m_NewState(nullptr), m_Adding(false), m_Replacing(false), m_Removing(false)
{
}

StateMachine::~StateMachine()
{
}

void StateMachine::add(StateRef state, bool replacing)
{
	m_NewState = std::move(state);

	m_Adding = true;
	m_Replacing = replacing;
}

void StateMachine::remove()
{
	m_Removing = true;
}

StateRef& StateMachine::getCurrentState()
{
	return m_States.empty() ? m_NewState : m_States.top();
}

void StateMachine::updateStateChanges()
{
	if (m_Removing)
	{
		if (!m_States.empty())
		{
			m_States.pop();
		}

		if (!m_States.empty())
		{
			m_States.top()->init();
		}

		m_Removing = false;
	}

	if (m_Adding)
	{
		if (m_NewState)
		{
			if (m_Replacing)
			{
				if (!m_States.empty())
				{
					m_States.pop();
				}
			}

			m_States.push(std::move(m_NewState));
			m_States.top()->init();
		}

		m_Adding = false;
		m_Replacing = false;
	}
}