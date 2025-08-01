#include "../Headers/PathAgent.h"
#include "../Headers/NodeMap.h"

void PathAgent::GoToNode(AIForGames::Node *node) {
    std::vector<AIForGames::Node*> newPath;

    if (m_algo == AIForGames::DIJKSTRA) {
        newPath = NodeMap::DijkstrasSearch(m_currentNode, node);
    } else {
        newPath = NodeMap::AStarSearch(m_currentNode, node);
    }

    if (!newPath.empty()) {
        m_path = newPath;
        m_currentIndex = 0;
    }    
}

void PathAgent::Update(const float deltaTime) {
    if (m_path.empty()) {
        return;
    }

    glm::vec2 dir = m_path.at(m_currentIndex)->position - m_position;
    const float dist = glm::length(dir);

    float step = m_speed * deltaTime;

    if (step < dist) {
        m_position += step * normalize(dir);
        return;
    }

	AIForGames::Node* passedNode = m_path.at(m_currentIndex);

	m_currentIndex += 1;
	if (m_currentIndex == m_path.size()) {
		m_position = passedNode->position;
		m_path.clear();
		m_currentIndex = 0;
        return;
	}

    m_currentNode = m_path.at(m_currentIndex);

	glm::vec2 newDir = (m_path.at(m_currentIndex)->position - passedNode->position);

	if (glm::length(newDir) > 0) {
		newDir = normalize(newDir);
	}

	m_position = passedNode->position + (step - dist) * newDir;
}

void PathAgent::SetNode(AIForGames::Node *node) {
    m_currentNode = node;
    m_position = node->position;
}

void PathAgent::SetPosition(glm::vec2 pos) {
    m_position = pos;
}

void PathAgent::SetSpeed(const float value) {
    m_speed = value;
}

void PathAgent::SetAlgorithm(AIForGames::Algorithm algo) {
    this->Reset();
    m_algo = algo;
}

void PathAgent::Reset() {
    m_path.clear();
}

AIForGames::Algorithm PathAgent::GetAlgorithm() const {
    return m_algo;
}

int PathAgent::GetCurrentIndex() const {
    return m_currentIndex;
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


