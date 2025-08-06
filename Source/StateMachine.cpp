#include "../Headers/StateMachine.h"

StateMachine::~StateMachine() {
	for (State* s : m_states) {
		delete s;
	}
}

void StateMachine::AddState(State* state) {
	m_states.push_back(state);
}

void StateMachine::Enter(Agent* agent) {
	m_currentState->Enter(agent);
}

void StateMachine::Exit(Agent* agent) {
	m_currentState->Exit(agent);
}

void StateMachine::Update(Agent* agent, float deltaTime) {
	State* newState = nullptr;

	for (State::Transition t : m_currentState->GetTransitions()) {
		if (t.condition->IsTrue(agent)) {
			newState = t.targetState;
		}
	}

	if (newState != nullptr && newState != m_currentState) {
		m_currentState->Exit(agent);
		m_currentState = newState;
		m_currentState->Enter(agent);
	}

	m_currentState->Update(agent, deltaTime);
}