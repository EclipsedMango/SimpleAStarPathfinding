#pragma once

#ifndef FOLLOWBEHAVIOUR_H
#define FOLLOWBEHAVIOUR_H

#include <glm/glm.hpp>
#include "Behaviour.h"

class FollowBehaviour final : public Behaviour {
public:
    void Enter(Agent* agent) override;
    void Update(Agent* agent, float deltaTime) override;
    void Exit(Agent* agent) override;
private:
    glm::vec2 lastTargetPosition = {};
};

#endif //FOLLOWBEHAVIOUR_H
