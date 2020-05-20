#pragma once


#include "../../biemgine/Biemgine.h"
#include <vector>

using biemgine::FileHandler;
using biemgine::RandomGenerator;

namespace spacebiem
{
    class NameGenerator
    {

    public:
        NameGenerator();

        string getName();
    private:
        vector<string> names;

    };
}
