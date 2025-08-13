#pragma once

#ifndef DEFENDCONDITION_H
#define DEFEMCONDITION_H

#include "Agent.h"
#include "Condition.h"
#include <glm/glm.hpp>

class DefendCondition final : public Condition {
public:
	DefendCondition(const glm::vec2 l, const float d, const bool lt) : m_location(l), m_distance(d), m_lessThan(lt) {}
	bool IsTrue(Agent* agent) override;
private:
	glm::vec2 m_location = {};
	float m_distance = 0;
	bool m_lessThan = false;
};

#endif //DEFENDCONDITION_H
