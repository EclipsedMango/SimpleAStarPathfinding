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

    const Image mapImage = LoadImage("GrayscaleMaze.png");

    std::vector<std::string> asciiMap;

    for (int y = 0; y < mapImage.height; ++y) {
        std::string line;

        for (int x = 0; x < mapImage.width; ++x) {
            if (GetImageColor(mapImage, x, y).r > 127) {
                line.append("1");
            } else {
                line.append("0");
            }
        }

        asciiMap.push_back(line);
    }

    auto *nodeMap = new NodeMap;
    nodeMap->Initialise(asciiMap, 50);

    Node* start = nodeMap->GetNode(1, 1);
    Node* end = nodeMap->GetNode(1, 1);

    std::vector<Node*> path = NodeMap::AStarSearch(start, end);

    PathAgent agent;
    agent.SetNode(start);
    agent.SetSpeed(128 * 5);

    auto time = static_cast<float>(GetTime());

    while (!WindowShouldClose()) {
        const auto fTime = static_cast<float>(GetTime());
        const float deltaTime = fTime - time;
        time = fTime;

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            glm::vec2 mousePos = {GetMousePosition().x / 50, GetMousePosition().y / 50};
            if (GetImageColor(mapImage, mousePos.x, mousePos.y).r > 127) {
                end = nodeMap->GetClosestNode(mousePos);
                agent.GoToNode(end);
            }
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
        DrawLineEx({node->parent->position.x, node->parent->position.y}, {node->position.x, node->position.y}, 6.0f, RED);
    }
}
