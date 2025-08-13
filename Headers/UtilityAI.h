#ifndef UTILITYAI_H
#define UTILITYAI_H
#include <vector>

#include "Behaviour.h"

class UtilityAI final : public Behaviour {
public:
    ~UtilityAI() override;

    void AddBehaviour(Behaviour* behaviour);
    void SetStartBehaviour(Behaviour* behaviour);
    void Update(Agent *agent, float deltaTime) override;
private:
    float cooldown = 500;
    float timer = 0;

    std::vector<Behaviour*> m_behaviours = {};
    Behaviour* m_currentBehaviour = {};
};

#endif //UTILITYAI_H
