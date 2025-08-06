#pragma once

#ifndef GOTOPOINTBEHAVIOUR_H
#define GOTOPOINTBEHAVIOUR_H
#include "Behaviour.h"

class GotoPointBehaviour final : public Behaviour {
public:
    void Enter(Agent* agent) override;
    void Update(Agent* agent, float deltaTime) override;
    void Exit(Agent* agent) override;
};

#endif //GOTOPOINTBEHAVIOUR_H
