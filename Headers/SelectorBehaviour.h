#pragma once

#ifndef SELECTORBEHAVIOUR_H
#define SELECTORBEHAVIOUR_H

#include "Behaviour.h"

class SelectorBehaviour final : public Behaviour {
public:
    SelectorBehaviour(Behaviour* b1, Behaviour* b2) : m_b1(b1), m_b2(b2) {}
    ~SelectorBehaviour();

    void Update(Agent* agent, float deltaTime) override;

    void SetBehaviour(Behaviour* b, Agent* agent);
private:
    Behaviour* m_b1;
    Behaviour* m_b2;
    Behaviour* m_selected;
};

#endif //SELECTORBEHAVIOUR_H
