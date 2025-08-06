#include "../Headers/FollowBehaviour.h"
#include "../Headers/Agent.h"

void FollowBehaviour::Enter(Agent* agent) {
	agent->SetColour(RED);
	agent->Reset();
}

void FollowBehaviour::Exit(Agent* agent) {
	agent->SetColour(WHITE);
	agent->Reset();
}

void FollowBehaviour::Update(Agent* agent, float deltaTime) {
	Agent* target = agent->GetTarget();

	float dist = glm::distance(target->GetPosition(), lastTargetPosition);
	if (dist > agent->GetNodeMap()->GetCellSize()) {
		lastTargetPosition = target->GetPosition() / target->GetNodeMap()->GetCellSize();
		agent->GoTo(lastTargetPosition);
	}
}
