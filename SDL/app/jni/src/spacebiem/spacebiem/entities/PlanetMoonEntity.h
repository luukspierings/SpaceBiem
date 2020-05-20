#pragma once

#include "../../biemgine/Biemgine.h"


using biemgine::Color;

#include "PlanetEntity.h"

namespace spacebiem
{
    class PlanetMoonEntity :
        public PlanetEntity
    {
    public:
        PlanetMoonEntity(float x, float y, Color color, float w, float h, int pScoreBonus, string pName="", bool scoreGiven = false);
    };
}
