#include "../Headers/DefendCondition.h"

bool DefendCondition::IsTrue(Agent* agent) {
	return (glm::distance(m_location, agent->GetTarget()->GetPosition()) < m_distance) == m_lessThan;
}