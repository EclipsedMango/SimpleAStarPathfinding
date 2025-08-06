#pragma once

#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include "Agent.h"
#include "State.h"

class StateMachine : public Behaviour {
public:
	StateMachine(State* s) : m_currentState(s), m_newState(nullptr) {}
	virtual ~StateMachine();

	void AddState(State* s);

	void Enter(Agent* agent);
	void Update(Agent* agent, float deltaTime);
	void Exit(Agent* agent);
private:
	std::vector<State*> m_states;

	State* m_currentState;
	State* m_newState;
};

#endif //STATEMACHINE_H
