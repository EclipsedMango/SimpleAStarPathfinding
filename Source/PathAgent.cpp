#include "../Headers/PathAgent.h"

#include "../Headers/NodeMap.h"

void PathAgent::GoToNode(AIForGames::Node *node) {
    m_path = NodeMap::DijkstrasSearch(m_currentNode, node);
    m_currentIndex = 0;
}

void PathAgent::Update(const float deltaTime) {
    if (m_path.empty()) {
        return;
    }

    glm::vec2 dir = m_currentNode->position - m_position;
    const float dist = glm::length(dir);

    float step = m_speed * deltaTime;

    if (step < dist) {
        m_position += step * normalize(dir);
    } else {
        AIForGames::Node* passedNode = m_currentNode;

        m_currentIndex += 1;
        if (m_currentIndex == m_path.size()) {
            m_position = passedNode->position;
            m_path.clear();
            m_currentIndex = 0;
        } else {
            m_currentNode = m_path.at(m_currentIndex);

            glm::vec2 newDir = (m_currentNode->position - passedNode->position);

            if (glm::length(newDir) > 0) {
                newDir = normalize(newDir);
            }

            m_position = passedNode->position + (step - dist) * newDir;
        }
    }
}

void PathAgent::SetNode(AIForGames::Node *node) {
    m_currentNode = node;
    m_position = node->position;
}

void PathAgent::SetSpeed(const float value) {
    m_speed = value;
}

glm::vec2 PathAgent::GetPosition() const {
    return m_position;
}

std::vector<AIForGames::Node *> PathAgent::GetPath() const {
    return m_path;
}

void PathAgent::Draw(const float rad, const Color color) const {
    DrawCircleV({m_position.x, m_position.y}, rad, color);
}


