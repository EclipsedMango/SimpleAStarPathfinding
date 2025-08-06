#pragma once

#ifndef DISTANCECONDITION_H
#define DISTANCECONDITION_H

#include "Agent.h"
#include "Condition.h"

class DistanceCondition final : public Condition {
public:
	DistanceCondition(float d, bool lt) : m_distance(d), m_lessThan(lt) {}
	virtual bool IsTrue(Agent* agent);
private:
	float m_distance = 0;
	bool m_lessThan = false;
};

#endif //DISTANCECONDITION_H
