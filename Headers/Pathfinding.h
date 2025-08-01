#pragma once

#ifndef PATHFINDING_H
#define PATHFINDING_H

#include <glm/glm.hpp>
#include <vector>

namespace AIForGames {
    struct Node;

    enum Algorithm {
        DIJKSTRA = 0,
        ASTAR = 1
    };

    struct Edge {
        Edge() { target = nullptr; cost = 0; }
        Edge(Node* _target, const float _cost) : target(_target), cost(_cost) {}

        Node* target = {};
        float cost = 0;
    };

    struct Node {
        glm::vec2 position = {};
        std::vector<Edge> connections = {};

        void ConnectTo(Node *other, float cost);

        Node* parent = {};
        float score = 0;
        float hScore = 0;
        float fScore = 0;
    };
}
#endif //PATHFINDING_H
