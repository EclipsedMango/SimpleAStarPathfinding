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

float DefendBehaviour::Evaluate(Agent *agent) {
	const Agent* target = agent->GetTarget();

	if (agent->GetBaseNode() == nullptr) {
		return 0;
	}

	const float dist = glm::distance(target->GetPosition(), agent->GetBaseNode()->position);

	if (dist > 5 * agent->GetNodeMap()->GetCellSize()) {
		return 0;
	}

	float eval = 30 * agent->GetNodeMap()->GetCellSize() - dist;
	if (eval < 0) {
		eval = 0;
	}

	return eval;
}

