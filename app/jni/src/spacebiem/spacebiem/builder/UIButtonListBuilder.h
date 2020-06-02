#pragma once


#include "../../biemgine/Biemgine.h"
#include "../../biemgine/managers/StateManager.h"
#include <functional>
#include <string>
#include <initializer_list>
#include <memory>
#include <vector>
#include <SDL.h>

using std::string;
using biemgine::EntityManager;
using biemgine::StateManager;
using biemgine::Entity;
using biemgine::Color;
using biemgine::Size;

using std::string;
using std::function;
using std::initializer_list;
using std::shared_ptr;

namespace spacebiem
{
    enum class StackMode {
        Vertical,
        Horizontal
    };

    struct UIButtonDef {
        string text;
        Size buttonSize;
        function<void(StateManager* test)> onClick = nullptr;
    };

    struct UIButtonList {
        float startX, startY;

        Color buttonColor;
        Color textColor;
        string texture;
        StackMode stackMode = StackMode::Vertical;
        float hPadding = 0, wPadding = 0;
    };
}
