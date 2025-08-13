#include "../Headers/Agent.h"

Agent::Agent(NodeMap* _nodeMap, Behaviour* _behaviour) : m_current(_behaviour), m_nodeMap(_nodeMap), m_color(WHITE) {
    m_current->Enter(this);
}

Agent::~Agent() {
    delete m_current;
}

void Agent::Update(float deltaTime) {
    if (m_current) {
        m_current->Update(this, deltaTime);
    }

    m_pathAgent.Update(deltaTime);
}

void Agent::SetNode(AIForGames::Node *node){
    m_pathAgent.SetNode(node);
}

void Agent::SetBaseNode(AIForGames::Node *node) {
    m_baseNode = node;
}

void Agent::SetNodeMap(NodeMap* _nodeMap) {
    m_nodeMap = _nodeMap;
}

void Agent::SetTarget(Agent* agent) {
    m_target = agent;
}

void Agent::SetPosition(glm::vec2 position) {
    m_pathAgent.SetPosition(position);
}

void Agent::SetSpeed(float value) {
    m_pathAgent.SetSpeed(value);
}

void Agent::SetColour(Color colour) {
    m_color = colour;
}

void Agent::SetLineColour(Color colour) {
    m_lineColour = colour;
}

void Agent::GoTo(glm::vec2 point) {
    AIForGames::Node* end = m_nodeMap->GetClosestNode(point);
    m_pathAgent.GoToNode(end);
}

void Agent::SwitchAlgorithm(AIForGames::Algorithm algo) {
    m_pathAgent.SetAlgorithm(algo);
}

void Agent::Reset() {
    m_pathAgent.Reset();
}

Agent* Agent::GetTarget() const {
    return m_target;
}

glm::vec2 Agent::GetPosition() const {
    return m_pathAgent.GetPosition();
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

AIForGames::Node* Agent::GetBaseNode() const {
    return m_baseNode;
}

void Agent::Draw() const {
    DrawPath(m_pathAgent, m_lineColour);
    m_pathAgent.Draw(12, m_color);
}

void Agent::DrawPath(const PathAgent& agent, const Color lineCol) {
    const std::vector<AIForGames::Node*> path = agent.GetPath();
    for (int i = agent.GetCurrentIndex() + 1; i < path.size(); ++i) {
        const AIForGames::Node* node = path.at(i);
        const AIForGames::Node* nextNode = path.at(i - 1);
        if (nextNode == nullptr) {
            continue;
        }

        DrawLineEx({nextNode->position.x, nextNode->position.y}, {node->position.x, node->position.y}, 6.0f, lineCol);
    }

    if (agent.GetCurrentIndex() >= path.size()) {
        return;
    }

    AIForGames::Node* currentNode = path[agent.GetCurrentIndex()];
    AIForGames::Node* endNode = path.back();
    DrawLineEx({agent.GetPosition().x, agent.GetPosition().y}, {currentNode->position.x, currentNode->position.y}, 6.0f, lineCol);
    DrawCircleV({endNode->position.x, endNode->position.y}, 8.0f, lineCol);
}

