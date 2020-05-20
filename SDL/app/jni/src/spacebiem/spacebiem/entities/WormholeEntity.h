#pragma once

#include "../../biemgine/Biemgine.h"

using biemgine::Color;

#include "PlanetEntity.h"

namespace spacebiem
{
    class WormholeEntity :
        public Entity
    {
    public:
        WormholeEntity(float x, float y, Color color, float w, float h);
    };
}
