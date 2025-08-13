#include "../Headers/UtilityAI.h"

#include "../Headers/Agent.h"

UtilityAI::~UtilityAI() {
    for (const Behaviour* b : m_behaviours) {
        delete b;
    }
}

void UtilityAI::AddBehaviour(Behaviour *behaviour) {
    m_behaviours.push_back(behaviour);
}

void UtilityAI::SetStartBehaviour(Behaviour *behaviour) {
    m_currentBehaviour = behaviour;
}

void UtilityAI::Update(Agent *agent, float deltaTime) {
    float bestEval = 0;
    Behaviour* newBehaviour = nullptr;

    timer++;
    if (timer < cooldown) {
        if (m_currentBehaviour != nullptr) {
            m_currentBehaviour->Update(agent, deltaTime);
        }

        return;
    }

    for (Behaviour* b : m_behaviours) {
        float eval = b->Evaluate(agent);

        if (eval > bestEval) {
            bestEval = eval;
            newBehaviour = b;
        }
    }

    if (newBehaviour != nullptr && newBehaviour != m_currentBehaviour) {
        if (m_currentBehaviour) {
            m_currentBehaviour->Exit(agent);
        }

        m_currentBehaviour = newBehaviour;
        m_currentBehaviour->Enter(agent);
    }

    timer = 0;
    m_currentBehaviour->Update(agent, deltaTime);
}


