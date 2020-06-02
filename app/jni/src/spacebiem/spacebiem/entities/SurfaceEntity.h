#pragma once

#include "../../biemgine/Biemgine.h"
using biemgine::Entity;
using biemgine::Color;

namespace spacebiem
{
    class SurfaceEntity :
        public Entity
    {
    public:
        SurfaceEntity(float x, float y, Color color, float w, float h);
    };
}
