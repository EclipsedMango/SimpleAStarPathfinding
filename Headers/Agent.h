#pragma once

#ifndef AGENT_H
#define AGENT_H

#include "Behaviour.h"
#include "NodeMap.h"
#include "PathAgent.h"

class Agent {
public:
    Agent() = default;
    Agent(NodeMap* _nodeMap, Behaviour* _behaviour) : m_current(_behaviour), m_nodeMap(_nodeMap), m_color({ 255, 255, 255, 255 }) {}
    ~Agent() { delete m_current; }

    void GoTo(glm::vec2 point);
    void SetNode(AIForGames::Node* node);

    [[nodiscard]] bool PathComplete() const;
    [[nodiscard]] NodeMap* GetNodeMap() const;

    void Update(float deltaTime);
    void Draw() const;

private:
    static void DrawPath(const PathAgent& agent) ;

    PathAgent m_pathAgent = {};
    Behaviour* m_current = {};
    NodeMap* m_nodeMap = {};
    Color m_color = {};
};

#endif //AGENT_H
