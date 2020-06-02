#pragma once

#include "../../biemgine/Biemgine.h"
#include "../globals/Difficulty.h"

using biemgine::AnimationComponent;
using biemgine::SpriteEntity;
using biemgine::Scene;
using biemgine::StateManager;
using biemgine::Entity;

namespace spacebiem
{
    class TestLevelScene :
            public Scene
    {
    public:
        void input() override;
        void update() override;
        void render(const float deltaTime) override;
        void created() override;

        void resetFPScounters();

        TestLevelScene(StateManager& manager) :
                Scene(manager)
        {};

        ~TestLevelScene() {}

    private:

        int FPSId;
        Entity * fpsEntity = nullptr;
        int timeout;
        float counter = 0;
        float totalDeltaTime = 0;

    };
}
