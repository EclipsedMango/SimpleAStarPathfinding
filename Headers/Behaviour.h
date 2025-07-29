#pragma once

#ifndef BEHAVIOUR_H
#define BEHAVIOUR_H

class Agent;

class Behaviour {
public:
    virtual ~Behaviour() = default;

    virtual void Update(Agent* agent, float deltaTime) = 0;
};

#endif //BEHAVIOUR_H
