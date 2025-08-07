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
#include "Headers/DefendBehaviour.h"
#include "Headers/DistanceCondition.h"
#include "Headers/DefendCondition.h"
#include "Headers/StateMachine.h"
#include "Headers/State.h"

using namespace AIForGames;

std::vector<std::string> GenerateMap(Image image);

int main() {
    constexpr int screenWidth = 1200;
    constexpr int screenHeight = 800;

    srand(time(nullptr));

    InitWindow(screenWidth, screenHeight, "AI For Games");

    Image mapImage = LoadImage("GrayscaleMaze.png");
    std::vector<std::string> asciiMap = GenerateMap(mapImage);

    auto *nodeMap = new NodeMap;
    nodeMap->SetMapImage(mapImage);
    nodeMap->Initialise(asciiMap, 50);

    Node* start = nodeMap->GetNode(1, 1);
    Node* end = nodeMap->GetNode(1, 1);

    std::vector<Node*> path = NodeMap::AStarSearch(start, end);

    Agent agent(nodeMap, new GotoPointBehaviour());
    agent.SetNode(start);
    agent.SetLineColour(Color(24, 204, 240, 255));

    Agent agent2(nodeMap, new WanderBehaviour());
    agent2.SetNode(nodeMap->GetRandomNode());
    agent2.SetLineColour(Color(240, 157, 24, 255));

    Node* agentBaseNode = nodeMap->GetRandomNode();

    DistanceCondition* closerThan5 = new DistanceCondition(5.0f * nodeMap->GetCellSize(), true);
    DistanceCondition* furtherThan7 = new DistanceCondition(7.0f * nodeMap->GetCellSize(), false);

    DefendCondition* withinRange = new DefendCondition(agentBaseNode->position, 5 * nodeMap->GetCellSize(), true);
    DefendCondition* notWithinRange = new DefendCondition(agentBaseNode->position, 5 * nodeMap->GetCellSize(), false);

    State* wanderState = new State(new WanderBehaviour());
    State* followState = new State(new FollowBehaviour());
    State* defendState = new State(new DefendBehaviour());

    wanderState->AddTransition(closerThan5, followState);
    wanderState->AddTransition(withinRange, defendState);

    followState->AddTransition(furtherThan7, wanderState);
    followState->AddTransition(withinRange, defendState);

    defendState->AddTransition(notWithinRange, wanderState);

    StateMachine* sm = new StateMachine(wanderState);
    sm->AddState(wanderState);
    sm->AddState(followState);
    sm->AddState(defendState);

    Agent agent3(nodeMap, sm);
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

        float halfSize = nodeMap->GetCellSize() * 0.5;
        DrawRectangleV({ agentBaseNode->position.x - halfSize, agentBaseNode->position.y - halfSize},
            { nodeMap->GetCellSize(), nodeMap->GetCellSize() }, {255, 0, 0, 75});

        DrawText("Press S to switch Algorithm", 25, 15, 25, LIME);
        if (agent.GetAlgorithm() == DIJKSTRA) {
            DrawText("Current Algorithm: DIJKSTRA", 400, 15, 25, BLUE);
        } else {
            DrawText("Current Algorithm: ASTAR", 400, 15, 25, BLUE);
        }

        EndDrawing();
    }

    delete nodeMap;
    UnloadImage(mapImage);

    delete closerThan5;
    delete furtherThan7;
    delete withinRange;
    delete notWithinRange;

    CloseWindow();
    return 0;
}

std::vector<std::string> GenerateMap(Image image) {
    std::vector<std::string> map = {};

    for (int y = 0; y < image.height; ++y) {
        std::string line;

        for (int x = 0; x < image.width; ++x) {
            if (GetImageColor(image, x, y).r > 127) {
                line.append("1");
            } else {
                line.append("0");
            }
        }

        map.push_back(line);
    }

    return map;
}
