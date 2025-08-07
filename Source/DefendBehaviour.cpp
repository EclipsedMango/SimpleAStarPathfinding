#include "../Headers/DefendBehaviour.h"
#include "../Headers/Agent.h"

void DefendBehaviour::Enter(Agent* agent) {
	agent->SetColour(ORANGE);
	agent->SetSpeed(128 * 5);
	agent->Reset();
}

void DefendBehaviour::Exit(Agent* agent) {
	agent->SetColour(WHITE);
	agent->SetSpeed(128 * 2.5);
	agent->Reset();
}

void DefendBehaviour::Update(Agent* agent, float deltaTime) {
	Agent* target = agent->GetTarget();

	float dist = glm::distance(target->GetPosition(), lastTargetPosition);
	if (dist > agent->GetNodeMap()->GetCellSize()) {
		lastTargetPosition = target->GetPosition() / target->GetNodeMap()->GetCellSize();
		agent->GoTo(lastTargetPosition);
	}
}
