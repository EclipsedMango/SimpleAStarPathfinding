#pragma once

#ifndef BEHAVIOUR_H
#define BEHAVIOUR_H

class Agent;

class Behaviour {
public:
    virtual ~Behaviour() = default;

    virtual void Enter(Agent* agent) {};
    virtual void Update(Agent* agent, float deltaTime) = 0;
    virtual void Exit(Agent* agent) {};

    virtual float Evaluate(Agent* agent) { return 0.0f; }
};

#endif //BEHAVIOUR_H
