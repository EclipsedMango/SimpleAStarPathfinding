#include "../Headers/Agent.h"

void Agent::Update(float deltaTime) {
    if (m_current) {
        m_current->Update(this, deltaTime);
    }

    m_pathAgent.Update(deltaTime);
}

void Agent::SetNode(AIForGames::Node *node) {
    m_pathAgent.SetNode(node);
}

void Agent::GoTo(glm::vec2 point) {
    AIForGames::Node* end = m_nodeMap->GetClosestNode(point);
    m_pathAgent.GoToNode(end);
}

bool Agent::PathComplete() const {
    return m_pathAgent.GetPath().empty();
}

NodeMap *Agent::GetNodeMap() const {
    return m_nodeMap;
}


void Agent::Draw() const {
    DrawPath(m_pathAgent);
    m_pathAgent.Draw(12, m_color);
}

void Agent::DrawPath(const PathAgent& agent) {
    const std::vector<AIForGames::Node*> path = agent.GetPath();
    for (int i = 1; i < path.size(); ++i) {
        const AIForGames::Node* node = path.at(i);
        DrawLineEx({node->parent->position.x, node->parent->position.y}, {node->position.x, node->position.y}, 6.0f, RED);
    }
}

