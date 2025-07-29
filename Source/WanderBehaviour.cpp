#include "../Headers/WanderBehaviour.h"

#include "../Headers/Agent.h"

void WanderBehaviour::Update(Agent *agent, float deltaTime) {
    if (agent->PathComplete()) {
        const glm::vec2 pos = agent->GetNodeMap()->GetRandomNode()->position / agent->GetNodeMap()->GetCellSize();
        agent->GoTo(pos);
    }
}
