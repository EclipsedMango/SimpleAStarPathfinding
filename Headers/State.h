#pragma once

#ifndef STATE_H
#define STATE_H

#include "Agent.h"
#include "Condition.h"

class State {
public:
	State() = default;
	State(Behaviour* b);
	~State();

	struct Transition {
		Condition* condition;
		State* targetState;
	};

	void AddTransition(Condition* c, State* s);
	std::vector<Transition>& GetTransitions();

	virtual void Enter(Agent* agent);
	virtual void Update(Agent* agent, float deltaTime);
	virtual void Exit(Agent* agent);
private:
	std::vector<Behaviour*> m_behaviours = {};
	std::vector<Transition> m_transitions = {};
};

#endif //STATE_H
