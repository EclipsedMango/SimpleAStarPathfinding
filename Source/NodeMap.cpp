#include "../Headers/NodeMap.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <raylib.h>
#include <unordered_set>

using namespace AIForGames;

NodeMap::~NodeMap() {
    delete m_nodes;
}

void NodeMap::Initialise(std::vector<std::string>& asciiMap, const int cellSize) {
    m_cellSize = cellSize;

    m_height = asciiMap.size();
    m_width = asciiMap[0].size();

    m_nodes = new Node*[m_width * m_height];

    for (int y = 0; y < m_height; y++) {
        std::string& line = asciiMap[y];

        if (line.size() != m_width) {
            std::cout << "Mismatched line #" << y << " in ASCII map (" << line.size() << " instead of " << m_width << ")" << std::endl;
        }

        for (int x = 0; x < m_width; x++) {
            constexpr char emptySquare = '0';
            char tile = x < line.size() ? line[x] : emptySquare;

            if (tile == emptySquare) {
                m_nodes[x + m_width * y] = nullptr;
                continue;
            }

            m_nodes[x + m_width * y] = new Node(glm::vec2((x + 0.5f) * m_cellSize, (y + 0.5f) * m_cellSize));
        }
    }

    // Loop over the nodes, creating connections between each node and its neighbour.
    for (int y = 0; y < m_height; y++) {
        for (int x = 0; x < m_width; x++) {
            Node* node = GetNode(x, y);
            if (node == nullptr) {
                continue;
            }

            // Are we on one of the edges?
            Node* nodeWest = x == 0 ? nullptr : GetNode(x - 1, y);
            Node* nodeSouth = y == 0 ? nullptr : GetNode(x, y - 1);

            if (nodeWest) {
                float dist = glm::distance(node->position, nodeWest->position);
                node->ConnectTo(nodeWest, dist);
                nodeWest->ConnectTo(node, dist);
            }

            if (nodeSouth) {
                float dist = glm::distance(node->position, nodeSouth->position);
                node->ConnectTo(nodeSouth, dist);
                nodeSouth->ConnectTo(node, dist);
            }
        }
    }
}

float CalculateHeuristic(const Node* a, const Node* b) {
    const float dx = abs(a->position.x - b->position.x);
    const float dy = abs(a->position.y - b->position.y);
    return dx + dy;
}

std::vector<Node*> NodeMap::AStarSearch(Node *startNode, Node *endNode) {
    if (startNode == nullptr || endNode == nullptr) {
        std::cout << "Start or End nodes are null." << std::endl;
        return {};
    }

    if (startNode == endNode) {
        return {};
    }

    startNode->score = 0;
    startNode->parent = nullptr;

    std::vector<Node*> open = {};
    std::unordered_set<Node*> closed = {};

    open.push_back(startNode);

    while (!open.empty()) {
        std::sort(open.begin(), open.end(), [](const Node* a, const Node* b) { return a->fScore < b->fScore; });

        Node* currentNode = open.front();

        // Are we at the end?
        if (currentNode == endNode) {
            break;
        }

        open.erase(open.begin());
        closed.insert(currentNode);

        for (Edge c : currentNode->connections) {
            if (!closed.contains(c.target)) {
                const float gScr = currentNode->score + c.cost;
                const float hScr = CalculateHeuristic(c.target, endNode);
                const float fScr = gScr + hScr;

                // Haven't visited node.
                if (std::ranges::find(open, c.target) == open.end()) {
                    c.target->score = gScr;
                    c.target->hScore = hScr;
                    c.target->fScore = fScr;
                    c.target->parent = currentNode;
                    open.push_back(c.target);

                    // Have visited node.
                } else if (fScr < c.target->fScore) {
                    c.target->score = gScr;
                    c.target->fScore = fScr;
                    c.target->parent = currentNode;
                }
            }
        }
    }

    std::vector<Node*> path = {};
    Node* currentNode = endNode;

    while (currentNode != nullptr) {
        path.insert(path.begin(), currentNode);
        currentNode = currentNode->parent;
    }

    if (path.front() == endNode) {
        return {};
    }

    return path;
}

std::vector<Node*> NodeMap::DijkstrasSearch(Node *startNode, Node *endNode) {
    if (startNode == nullptr || endNode == nullptr) {
        throw std::invalid_argument("Start or End node is null.");
    }

    if (startNode == endNode) {
        return {};
    }

    startNode->score = 0;
    startNode->parent = nullptr;

    std::vector<Node*> open = {};
    std::unordered_set<Node*> closed = {};

    open.push_back(startNode);

    while (!open.empty()) {
        std::sort(open.begin(), open.end(), [](const Node* a, const Node* b) { return a->score < b->score; });

        Node* currentNode = open.front();

        // Are we at the end?
        if (currentNode == endNode) {
            break;
        }

        open.erase(open.begin());
        closed.insert(currentNode);

        for (Edge c : currentNode->connections) {
            if (!closed.contains(c.target)) {
                const float gScr = currentNode->score + c.cost;
              
                // Haven't visited node.
                if (std::ranges::find(open, c.target) == open.end()) {
                    c.target->score = gScr;
                    c.target->parent = currentNode;
                    open.push_back(c.target);

                    // Have visited node.
                } else if (gScr < c.target->score) {
                    c.target->score = gScr;
                    c.target->parent = currentNode;
                }
            }
        }
    }

    std::vector<Node*> path = {};
    Node* currentNode = endNode;

    while (currentNode != nullptr) {
        path.insert(path.begin(), currentNode);
        currentNode = currentNode->parent;
    }

    if (path.front() == endNode) {
        return {};
    }
   
    return path;
}


Node* NodeMap::GetClosestNode(const glm::vec2 worldPos) const {
    int i = static_cast<int>(worldPos.x);
    if (i < 0 || i >= m_width) return nullptr;

    int j = static_cast<int>(worldPos.y);
    if (j < 0 || j >= m_height) return nullptr;

    return GetNode(i, j);
}

Node* NodeMap::GetRandomNode() const {
    Node* node = nullptr;
    while (node == nullptr) {
        const int x = rand() % m_width;
        const int y = rand() % m_height;
        node = GetNode(x, y);
    }
    return node;
}

float NodeMap::GetCellSize() const {
    return m_cellSize;
}

Image NodeMap::GetMapImage() const {
    return m_mapImage;
}

void NodeMap::SetMapImage(Image mapImage) {
    m_mapImage = mapImage;
}

void NodeMap::Draw() const {
    constexpr auto cellColor = Color(43, 43, 43, 255);
    constexpr auto lineColor = Color(175, 175, 175, 255);

    for (int y = 0; y < m_height; y++) {
        for (int x = 0; x < m_width; x++) {
            Node* node = GetNode(x, y);

            // Walls.
            if (node == nullptr) {
                DrawRectangle(
                    static_cast<int>(x * m_cellSize),
                    static_cast<int>(y * m_cellSize),
                    static_cast<int>(m_cellSize),
                    static_cast<int>(m_cellSize),
                    cellColor
                );
            } else {
                // Connections between neighbours.
                for (const auto & connection : node->connections) {
                    const Node* other = connection.target;
                    DrawLineEx(
                        {(x + 0.5f) * m_cellSize, (y + 0.5f) * m_cellSize},
                        {(other->position.x), (other->position.y)},
                        6.0f,
                        lineColor
                    );
                }
            }
        }
    }
}

