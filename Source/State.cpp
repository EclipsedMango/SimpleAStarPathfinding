#include "../Headers/State.h"

State::State(Behaviour* b) {
	m_behaviours.push_back(b);
}

State::~State() {
	for (Behaviour* b : m_behaviours) {
		delete b;
	}

	for (Transition t : m_transitions) {
		delete t.condition;
	}
}

void State::AddTransition(Condition* c, State* s) {
	m_transitions.push_back(Transition{c, s});
}

void State::Update(Agent* agent, float deltaTime) {
	for (Behaviour* b : m_behaviours) {
		b->Update(agent, deltaTime);
	}
}

void State::Enter(Agent* agent) {
	for (Behaviour* b : m_behaviours) {
		b->Enter(agent);
	}
}

void State::Exit(Agent* agent) {
	for (Behaviour* b : m_behaviours) {
		b->Exit(agent);
	}
}

std::vector<State::Transition>& State::GetTransitions() {
	return m_transitions;
}