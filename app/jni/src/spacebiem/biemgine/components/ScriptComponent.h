#pragma once


#include "Component.h"
#include <string>
#include "ColorComponent.h"
#include "../primitives/Primitives.h"
#include "../entities/Entity.h"

#include <functional>

using std::function;

namespace biemgine
{
    class ScriptComponent :
        public Component
    {
    public:
        ScriptComponent(function<void(float)> pScript);

        void run(float deltaTime);

    private:
        function<void(float)> script;
    };
}
