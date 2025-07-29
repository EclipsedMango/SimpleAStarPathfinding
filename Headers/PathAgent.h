#pragma once

#ifndef PATHAGENT_H
#define PATHAGENT_H
#include <raylib.h>
#include <vector>

#include "Pathfinding.h"
#include "glm/vec2.hpp"

class PathAgent {
private:
    glm::vec2 m_position = {};

    std::vector<AIForGames::Node*> m_path = {};
    int m_currentIndex = 0;
    AIForGames::Node* m_currentNode = {};

    float m_speed = 128 * 5;

public:
    void Update(float deltaTime);

    void GoToNode(AIForGames::Node* node);
    void SetNode(AIForGames::Node* node);
    void SetSpeed(float value);

    [[nodiscard]] glm::vec2 GetPosition() const;
    [[nodiscard]] std::vector<AIForGames::Node*> GetPath() const;

    void Draw(float rad, Color color) const;
};
#endif //PATHAGENT_H
