#pragma once

#ifndef CONDITION_H
#define CONDITION_H

#include "Agent.h"

class Condition {
public:
	virtual bool IsTrue(Agent* agent) = 0;
};

#endif //CONDITION_H
