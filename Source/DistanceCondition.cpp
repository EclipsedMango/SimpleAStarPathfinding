#include "../Headers/DistanceCondition.h"

bool DistanceCondition::IsTrue(Agent* agent) {
	return (glm::distance(agent->GetPosition(), agent->GetTarget()->GetPosition()) < m_distance) == m_lessThan;
}