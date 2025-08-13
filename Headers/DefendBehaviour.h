#pragma once

#ifndef DEFENDBEHAVIOUR_H
#define DEFENDBEHAVIOUR_H

#include <glm/glm.hpp>
#include "Behaviour.h"

class DefendBehaviour final : public Behaviour {
public:
    void Enter(Agent* agent) override;
    void Update(Agent* agent, float deltaTime) override;
    void Exit(Agent* agent) override;

    float Evaluate(Agent *agent) override;
private:
    glm::vec2 lastTargetPosition = {};
};

#endif //DEFENDBEHAVIOUR_H
