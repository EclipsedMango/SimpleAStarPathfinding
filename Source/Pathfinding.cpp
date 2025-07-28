#include "../Headers/Pathfinding.h"

using namespace AIForGames;

void Node::ConnectTo(Node* other, const float cost) {
    connections.emplace_back(other, cost);
}


