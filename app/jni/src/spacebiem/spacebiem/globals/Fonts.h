#pragma once

#include "../../biemgine/Biemgine.h"

using biemgine::Font;

namespace spacebiem
{
    class Fonts
    {
    public:
        static Font Roboto(int size = 30) {
            return {
                "Roboto-Regular",
                size
            };
        }

        static Font Consolas(int size = 30) {
            return {
                "Consolas",
                size
            };
        }
    };
}
