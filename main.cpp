#include <iostream>
#include <vector>

#include "raylib.h"
#include "Headers/Agent.h"
#include "Headers/GotoPointBehaviour.h"
#include "Headers/NodeMap.h"
#include "Headers/PathAgent.h"
#include "Headers/Pathfinding.h"
#include "Headers/WanderBehaviour.h"
#include "Headers/FollowBehaviour.h"
#include "Headers/SelectorBehaviour.h"

using namespace AIForGames;

int main() {
    constexpr int screenWidth = 1200;
    constexpr int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "AI For Games");

    const Image mapImage = LoadImage("GrayscaleMaze2.png");

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
    nodeMap->SetMapImage(mapImage);

    Node* start = nodeMap->GetNode(1, 1);
    Node* end = nodeMap->GetNode(1, 1);

    std::vector<Node*> path = NodeMap::AStarSearch(start, end);

    Agent agent(nodeMap, new GotoPointBehaviour());
    agent.SetNode(start);
    agent.SetLineColour(Color(24, 204, 240, 255));

    Agent agent2(nodeMap, new WanderBehaviour());
    agent2.SetNode(nodeMap->GetRandomNode());
    agent2.SetLineColour(Color(240, 157, 24, 255));

    Agent agent3(nodeMap, new SelectorBehaviour(new FollowBehaviour(), new WanderBehaviour()));
    agent3.SetNode(nodeMap->GetRandomNode());
    agent3.SetTarget(&agent);
    agent3.SetSpeed(128 * 2.5);
    agent3.SetLineColour(Color(24, 240, 49, 255));

    auto time = static_cast<float>(GetTime());

    bool switchedAlgo = false;

    while (!WindowShouldClose()) {
        const auto fTime = static_cast<float>(GetTime());
        const float deltaTime = fTime - time;
        time = fTime;

        if (IsKeyPressed(KEY_S)) {
            switchedAlgo = !switchedAlgo;

            if (switchedAlgo) {
                agent.SwitchAlgorithm(DIJKSTRA);
                agent2.SwitchAlgorithm(DIJKSTRA);
                agent3.SwitchAlgorithm(DIJKSTRA);
            } else {
                agent.SwitchAlgorithm(ASTAR);
                agent2.SwitchAlgorithm(ASTAR);
                agent3.SwitchAlgorithm(ASTAR);
            }
        }

        BeginDrawing();
        ClearBackground(Color(62, 65, 66));

        nodeMap->Draw();

        agent.Update(deltaTime);
        agent.Draw();

        agent2.Update(deltaTime);
        agent2.Draw();

        agent3.Update(deltaTime);
        agent3.Draw();

        DrawText("Press S to switch Algorithm", 25, 15, 25, LIME);
        if (agent.GetAlgorithm() == DIJKSTRA) {
            DrawText("Current Algorithm: DIJKSTRA", 400, 15, 25, BLUE);
        } else {
            DrawText("Current Algorithm: ASTAR", 400, 15, 25, BLUE);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
