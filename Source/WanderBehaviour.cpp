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
