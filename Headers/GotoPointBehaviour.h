#pragma once

#ifndef GOTOPOINTBEHAVIOUR_H
#define GOTOPOINTBEHAVIOUR_H
#include "Behaviour.h"

class GotoPointBehaviour final : public Behaviour {
public:
    void Update(Agent* agent, float deltaTime) override;
};

#endif //GOTOPOINTBEHAVIOUR_H
