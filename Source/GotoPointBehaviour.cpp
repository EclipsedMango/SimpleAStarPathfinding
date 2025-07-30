#include "../Headers/GotoPointBehaviour.h"

#include <raylib.h>

#include "../Headers/Agent.h"
#include "glm/vec2.hpp"

void GotoPointBehaviour::Update(Agent* agent, float deltaTime) {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        NodeMap* map = agent->GetNodeMap();
        glm::vec2 mousePos = {GetMousePosition().x / 50, GetMousePosition().y / 50};

        if (GetImageColor(map->GetMapImage(), mousePos.x, mousePos.y).r > 127) {
            agent->GoTo(glm::vec2(mousePos.x, mousePos.y));
        }
    }
}
