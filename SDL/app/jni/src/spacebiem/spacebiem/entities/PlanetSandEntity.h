#pragma once

#include "../../biemgine/Biemgine.h"


using biemgine::Color;

#include "PlanetEntity.h"

namespace spacebiem
{
    class PlanetSandEntity :
        public PlanetEntity
    {
    public:
        PlanetSandEntity(float x, float y, Color color, float w, float h, int pScoreBonus, float atmosphere, string pName = "", bool scoreGiven = false);
    };
}
