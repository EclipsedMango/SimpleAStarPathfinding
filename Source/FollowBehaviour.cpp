#include "../Headers/FollowBehaviour.h"
#include "../Headers/Agent.h"

void FollowBehaviour::Update(Agent* agent, float deltaTime) {
	Agent* target = agent->GetTarget();

	float dist = glm::distance(target->GetPosition(), lastTargetPosition);
	if (dist > agent->GetNodeMap()->GetCellSize()) {
		lastTargetPosition = target->GetPosition() / target->GetNodeMap()->GetCellSize();
		agent->GoTo(lastTargetPosition);
	}
}
