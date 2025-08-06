#ifndef WANDERBEHAVIOUR_H
#define WANDERBEHAVIOUR_H

#include "Behaviour.h"

class WanderBehaviour final : public Behaviour {
public:
    void Enter(Agent* agent) override;
    void Update(Agent* agent, float deltaTime) override;
    void Exit(Agent* agent) override;
};

#endif //WANDERBEHAVIOUR_H
