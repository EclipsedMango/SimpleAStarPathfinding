#include <iostream>
#include <vector>

#include "raylib.h"
#include "Headers/Agent.h"
#include "Headers/GotoPointBehaviour.h"
#include "Headers/NodeMap.h"
#include "Headers/PathAgent.h"
#include "Headers/Pathfinding.h"
#include "Headers/WanderBehaviour.h"

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

    Agent agent(nodeMap, new GotoPointBehaviour());
    agent.SetNode(start);

    Agent agent2(nodeMap, new WanderBehaviour());
    agent2.SetNode(nodeMap->GetRandomNode());

    auto time = static_cast<float>(GetTime());

    while (!WindowShouldClose()) {
        const auto fTime = static_cast<float>(GetTime());
        const float deltaTime = fTime - time;
        time = fTime;

        BeginDrawing();
        ClearBackground(Color(62, 65, 66));

        nodeMap->Draw();

        agent.Update(deltaTime);
        agent.Draw();

        agent2.Update(deltaTime);
        agent2.Draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
