#pragma once

#ifndef AGENT_H
#define AGENT_H

#include "Behaviour.h"
#include "NodeMap.h"
#include "PathAgent.h"

class Agent {
public:
    Agent() = default;
    Agent(NodeMap* _nodeMap, Behaviour* _behaviour);
    ~Agent() { delete m_current; }

    void GoTo(glm::vec2 point);

    void SwitchAlgorithm(AIForGames::Algorithm algo);
    void Reset();

    void SetTarget(Agent* agent);
    void SetSpeed(float value);
    void SetPosition(glm::vec2 pos);
    void SetColour(Color colour);
    void SetLineColour(Color colour);
    void SetNode(AIForGames::Node* node);

    [[nodiscard]] Agent* GetTarget() const;
    [[nodiscard]] glm::vec2 GetPosition() const;
    [[nodiscard]] int GetCurrentIndex() const;
    [[nodiscard]] AIForGames::Algorithm GetAlgorithm() const;
    [[nodiscard]] bool PathComplete() const;
    [[nodiscard]] NodeMap* GetNodeMap() const;

    void Update(float deltaTime);
    void Draw() const;

private:
    static void DrawPath(const PathAgent& agent, const Color lineCol);

    Agent* m_target = {};
    PathAgent m_pathAgent = {};
    Behaviour* m_current = {};
    NodeMap* m_nodeMap = {};
    Color m_color = {};
    Color m_lineColour = {};
};

#endif //AGENT_H
