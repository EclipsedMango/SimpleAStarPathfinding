#ifndef WANDERBEHAVIOUR_H
#define WANDERBEHAVIOUR_H

#include "Behaviour.h"

class WanderBehaviour final : public Behaviour {
public:
    void Update(Agent* agent, float deltaTime) override;
};

#endif //WANDERBEHAVIOUR_H
