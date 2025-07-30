#pragma once

#ifndef NODEMAP_H
#define NODEMAP_H

#include <iostream>
#include <string>
#include <vector>

#include <raylib.h>

#include "Pathfinding.h"

class NodeMap {
    ~NodeMap();

    int m_width = 0, m_height = 0;
    float m_cellSize = 0;

    Image m_mapImage = {};

    AIForGames::Node** m_nodes = {};

public:
    void Initialise(std::vector<std::string> &asciiMap, int cellSize);
    void Draw() const;

    static std::vector<AIForGames::Node*> AStarSearch(AIForGames::Node* startNode, AIForGames::Node* endNode);
    static std::vector<AIForGames::Node*> DijkstrasSearch(AIForGames::Node* startNode, AIForGames::Node* endNode);

    void SetMapImage(Image mapImage);

    [[nodiscard]] AIForGames::Node* GetClosestNode(glm::vec2 worldPos) const;
    [[nodiscard]] AIForGames::Node* GetNode(const int x, const int y) const { return m_nodes[x + m_width * y]; }
    [[nodiscard]] AIForGames::Node* GetRandomNode() const;
    [[nodiscard]] float GetCellSize() const;
    [[nodiscard]] Image GetMapImage() const;
};

#endif //NODEMAP_H
