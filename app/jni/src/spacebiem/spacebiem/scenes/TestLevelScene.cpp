
#include "TestLevelScene.h"

#include "../factories/UniverseBuilder.h"
#include "../factories/UniverseGenerator.h"

#include "../entities/PlayerEntity.h"
#include "../entities/PlanetEarthEntity.h"
#include "../entities/PlanetMoonEntity.h"
#include "../entities/ScoreUIEntity.h"
#include "../entities/OxygenUIEntity.h"
#include "../entities/ResourceUIEntity.h"
#include "../entities/ButtonUIEntity.h"
#include "../factories/ScoreUIFactory.h"
#include "../factories/PlanetFactory.h"

#include "MenuScene.h"
#include "HelpScene.h"

#include "../systems/GravitySystem.h"
#include "../systems/MovementSystem.h"
#include "../systems/JumpSystem.h"
#include "../systems/OxygenSystem.h"
#include "../systems/OxygenUISystem.h"
#include "../systems/ScoreUISystem.h"
#include "../systems/ScoreSystem.h"
#include "../systems/ResourceUISystem.h"
#include "../systems/ResourceCollectingSystem.h"
#include "../systems/GameoverSystem.h"
#include "../systems/CheatSystem.h"
#include "../systems/WinSystem.h"
#include "../systems/AIMovementSystem.h"

#include "../globals/Fonts.h"
#include "../globals//Player.h"

#include <functional>
#include <chrono>
#include "../factories/SaveBlobFactory.h"
#include "../globals/Functions.h"

using biemgine::TextComponent;
using biemgine::TextureComponent;
using biemgine::TextEntity;
using biemgine::TextUIEntity;
using biemgine::ScriptComponent;
using std::function;

#include <android/log.h>
#define LOG(...) __android_log_print(ANDROID_LOG_WARN, "SPACEBIEM", __VA_ARGS__)

namespace spacebiem
{

    void TestLevelScene::created()
    {
        enableCamera();
        enableRendering();
        enablePhysics();
        enableUI();
        enableScripts();
        enableAnimations();

        addSystem<GravitySystem>();
        addSystem<MovementSystem>();
        addSystem<JumpSystem>();
        addSystem<OxygenSystem>();
        addSystem<OxygenUISystem>();
        addSystem<ScoreSystem>();
        addSystem<ScoreUISystem>();
        addSystem<ResourceUISystem>();
        addSystem<ResourceCollectingSystem>();
//        addSystem<AIMovementSystem>();
//        addSystem<WinSystem>(difficulty);
//        addSystem<CheatSystem>();
//        addSystem<GameoverSystem>((customLevel != ""));

        addEntity<OxygenUIEntity>();
        addEntity(new ScoreUIEntity(25.f, 280.f));
        addEntity(new SpriteEntity("textures/resources-hud.png", 25.f, 25.f, Color::White(), 401.f, 169.f, 101u));
        addEntity(new ResourceUIEntity(66.f, 145.f, Color::White(), "uranium", 0, 20));
        addEntity(new ResourceUIEntity(157.f, 145.f, Color::White(), "diamond", 0, 20));
        addEntity(new ResourceUIEntity(248.f, 145.f, Color::White(), "metal", 0, 20));
        addEntity(new ResourceUIEntity(339.f, 145.f, Color::White(), "anti-matter", 0, 20));



        FPSId = addEntity(new TextUIEntity(Fonts::Consolas(), getTransitionManager().getWindowWidth() - 220, 40, Color{ 66, 143, 244 }, ""));
        fpsEntity = getEntity(FPSId);

        int wW = getTransitionManager().getWindowWidth();
        int wH = getTransitionManager().getWindowHeight();

        PlanetFactory planetFactory;
        FileParser fileParser;
        NameGenerator nameGenerator;
        ResourceFactory resourceFactory;

        map<string, float> atmosphereM = fileParser.atmosphereContent();
        map<string, int> scoreBonus = fileParser.planetScoreContent();

        int size = 300;

        int x = wW / 2;
        int y = wH / 2;

        x -= size / 2;
        y -= size / 2;

        planetFactory.create("earth", x, y, size, size, getEntityManager(), resourceFactory, nameGenerator, atmosphereM, scoreBonus);

        int pX = wW / 2;
        int pY = wH / 4;

        auto player = new PlayerEntity(pX, pY, Color::White(), 25, 50, 1.f, true);
        int playerId = getEntityManager()->addEntity(player);

        auto oxygenComponent = player->getComponent<OxygenComponent>("oxygen");
        oxygenComponent->setOxygenAmount(stod("1"));

        auto scoreComponent = player->getComponent<ScoreComponent>("score");
        scoreComponent->setScore(stod("0"));

        auto resourceComponent = player->getComponent<ResourceComponent>("resources");
        auto physicsComponent = player->getComponent<PhysicsComponent>("physics");
        auto positionComponent = player->getComponent<PositionComponent>("position");

        resourceComponent->addResource("metal", 0);
        resourceComponent->addResource("diamond", 0);
        resourceComponent->addResource("uranium", 0);
        resourceComponent->addResource("anti-matter", 0);

//        physicsComponent->setVelocity({ physics[0], physics[1] }, true);
//        positionComponent->setRotation(physics[2]);

        addEntity(new SpriteEntity("textures/resources-need.png", wW - 250 - 25.f, 70.f, Color::White(), 250, 382, 100u, "resource-needed-background"));
        float rX = 66.f;
        float rIncr = 91.f;
        addEntity(new ResourceUIEntity(wW - 234.f, 143.f, Color::White(), "uranium", 0, 20, "resource-needed"));
        addEntity(new ResourceUIEntity(wW - 234.f, 143.f + 78.f, Color::White(), "diamond", 0, 20, "resource-needed"));
        addEntity(new ResourceUIEntity(wW - 234.f, 145.f + 78.f * 2.f, Color::White(), "metal", 0, 20, "resource-needed"));
        addEntity(new ResourceUIEntity(wW - 234.f, 145.f + 78.f * 3.f, Color::White(), "anti-matter", 0, 20, "resource-needed"));

    }

    void TestLevelScene::input()
    {

    }

    void TestLevelScene::update()
    {
        updateEntities();
    }

    void TestLevelScene::resetFPScounters()
    {
        timeout = 0;
        counter = 0;
        totalDeltaTime = 0;
    }

    void TestLevelScene::render(const float deltaTime)
    {
        totalDeltaTime += deltaTime;
        counter++;

        if (timeout >= 500.f) {
            auto tc = fpsEntity->getComponent<TextComponent>("text");

            tc->setText("FPS: " + std::to_string(static_cast<int>(counter / totalDeltaTime * 1000)), Color{ 255, 255, 255 });
            resetFPScounters();
        }

        timeout += deltaTime;
        getTransitionManager().drawBackground("textures/space.png");
        updateEntities(deltaTime);
    }

}
