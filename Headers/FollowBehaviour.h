#pragma once

#ifndef FOLLOWBEHAVIOUR_H
#define FOLLOWBEHAVIOUR_H

#include <glm/glm.hpp>
#include "Behaviour.h"

class FollowBehaviour final : public Behaviour {
public:
    void Update(Agent* agent, float deltaTime) override;
private:
    glm::vec2 lastTargetPosition;
};

#endif //FOLLOWBEHAVIOUR_H
