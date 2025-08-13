#include "../Headers/WanderBehaviour.h"
#include "../Headers/Agent.h"

void WanderBehaviour::Enter(Agent* agent) {
    agent->SetColour(WHITE);
    agent->Reset();
}

void WanderBehaviour::Exit(Agent* agent) {
    agent->SetColour(GRAY);
    agent->Reset();
}

void WanderBehaviour::Update(Agent *agent, float deltaTime) {
    if (agent->PathComplete()) {
        const glm::vec2 pos = agent->GetNodeMap()->GetRandomNode()->position / agent->GetNodeMap()->GetCellSize();
        agent->GoTo(pos);
    }
}

float WanderBehaviour::Evaluate(Agent *agent) {
    const Agent* target = agent->GetTarget();
    const float dist = glm::distance(target->GetPosition(), agent->GetPosition());

    float eval = dist;
    if (eval < 0) {
        eval = 0;
    }

    return eval;
}

