#pragma once
#include "../../biemgine/Biemgine.h"
#include "../entities/PlanetEarthEntity.h"
#include "../entities/PlanetMoonEntity.h"
#include "../entities/ButtonUIEntity.h"
#include "../globals/Player.h"

using biemgine::Scene;
using biemgine::StateManager;
using biemgine::Color;
using biemgine::SpriteEntity;
using biemgine::AnimationComponent;
using biemgine::TextureComponent;
using biemgine::Size;

#include <android/log.h>
#define LOG(...) __android_log_print(ANDROID_LOG_WARN, "SPACEBIEM", __VA_ARGS__)

namespace spacebiem
{
    class ProfileScene
        : public Scene
    {
    public:
        void input() override {};
        void update() override;
        void render(const float deltaTime) override;
        void created() override;

        ~ProfileScene() {};

        ProfileScene(StateManager& manager)
            : Scene(manager) {
            LOG("Initialized profilescene");
        };
    private:
        bool fadeIn{ true };
    };
}

