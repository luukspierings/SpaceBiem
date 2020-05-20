#pragma once
#pragma once


#include "../systems/System.h"
#include "../entities/Entity.h"

#include <vector>

namespace biemgine
{
    class SystemManager
    {
    public:

        SystemManager();

        ~SystemManager();

         void preUpdate();
        void preUpdate(const float deltaTime);

         void postUpdate();
         void postUpdate(const float deltaTime);

         void acceptForUpdate();
         void acceptForUpdate(const float deltaTime);

        void addSystem(System* system);

        void onSceneSwitch();
        void onAddEntity(Entity& entity);
    private:
        std::vector<System*> systems;
    };
}
