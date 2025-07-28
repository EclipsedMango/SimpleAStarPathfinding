#include <iostream>
#include <vector>

#include "raylib.h"
#include "Headers/NodeMap.h"
#include "Headers/PathAgent.h"
#include "Headers/Pathfinding.h"

using namespace AIForGames;

void DrawPath(const PathAgent& agent);

int main() {
    constexpr int screenWidth = 1200;
    constexpr int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "AI For Games");

    std::vector<std::string> asciiMap;

    asciiMap.emplace_back("000000000000");
    asciiMap.emplace_back("011101110110");
    asciiMap.emplace_back("010111010100");
    asciiMap.emplace_back("010001011110");
    asciiMap.emplace_back("011101010010");
    asciiMap.emplace_back("010111110110");
    asciiMap.emplace_back("010001000100");
    asciiMap.emplace_back("000000000000");

    auto *nodeMap = new NodeMap;
    nodeMap->Initialise(asciiMap, 100);

    Node* start = nodeMap->GetNode(1, 1);
    Node* end = nodeMap->GetNode(5, 6);

    std::vector<Node*> path = NodeMap::DijkstrasSearch(start, end);

    PathAgent agent;
    agent.SetNode(start);
    agent.SetSpeed(128);

    auto time = static_cast<float>(GetTime());

    while (!WindowShouldClose()) {
        const auto fTime = static_cast<float>(GetTime());
        const float deltaTime = fTime - time;
        time = fTime;

        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
            glm::vec2 mousePos = {GetMousePosition().x, GetMousePosition().y};
            end = nodeMap->GetClosestNode(mousePos);
            agent.GoToNode(end);
        }

        BeginDrawing();
        ClearBackground(Color(62, 65, 66));

        nodeMap->Draw();
        DrawPath(agent);

        agent.Update(deltaTime);
        agent.Draw(12, Color(255, 255, 255, 255));

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

void DrawPath(const PathAgent& agent) {
    const std::vector<Node*> path = agent.GetPath();
    for (int i = 1; i < path.size(); ++i) {
        const Node* node = path.at(i);
        DrawLineEx({node->previous->position.x, node->previous->position.y}, {node->position.x, node->position.y}, 6.0f, RED);
    }
}
