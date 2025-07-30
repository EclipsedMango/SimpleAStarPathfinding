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

void Agent::SwitchAlgorithm(AIForGames::Algorithm algo) {
    m_pathAgent.SetAlgorithm(algo);
}

AIForGames::Algorithm Agent::GetAlgorithm() const {
    return m_pathAgent.GetAlgorithm();
}

int Agent::GetCurrentIndex() const {
    return m_pathAgent.GetCurrentIndex();
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
    Color lineCol = Color(2, 168, 209, 255);

    const std::vector<AIForGames::Node*> path = agent.GetPath();
    for (int i = agent.GetCurrentIndex() + 1; i < path.size(); ++i) {
        const AIForGames::Node* node = path.at(i);
        if (node->parent == nullptr) {
            continue;
        }

        DrawLineEx({node->parent->position.x, node->parent->position.y}, {node->position.x, node->position.y}, 6.0f, lineCol);
    }

    if (agent.GetCurrentIndex() >= path.size()) {
        return;
    }

    AIForGames::Node* currentNode = path[agent.GetCurrentIndex()];
    DrawLineEx({agent.GetPosition().x, agent.GetPosition().y}, {currentNode->position.x, currentNode->position.y}, 6.0f, lineCol);
}

