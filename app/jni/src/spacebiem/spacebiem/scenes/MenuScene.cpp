#include "MenuScene.h"

#include "../factories/ScoreUIFactory.h"
#include "LevelScene.h"
#include "HighScoreScene.h"
#include "GameoverScene.h"
#include "HelpScene.h"
#include "CreditsScene.h"
#include "DifficultyScene.h"
#include "../entities/PlanetEarthEntity.h"
#include "../entities/AdEntity.h"
#include "../entities/PlanetMoonEntity.h"
#include "../entities/ButtonUIEntity.h"
#include "../systems/ScoreUISystem.h"
#include "../systems/ResourceUISystem.h"
#include "../entities/ResourceUIEntity.h"
#include "../globals/Functions.h"
#include "../globals/Ads.h"
#include "../globals/Player.h"
#include "./ProfileScene.h"
#include "LevelLoadScene.h"

using biemgine::AnimationComponent;
using biemgine::TextureComponent;
using biemgine::SpriteEntity;
using biemgine::Size;
using biemgine::FileHandler;

namespace spacebiem
{
    void MenuScene::created()
    {
        enableRendering();
        enableUI();
        enableScripts();
        enableAnimations();

        getTransitionManager().getAudioDevice().stopSoundEffect("");

        addSystem<ResourceUISystem>();

        int wW = getTransitionManager().getWindowWidth();
        int wH = getTransitionManager().getWindowHeight();
        float planetWidth = 500;
        float planetHeight = 500;
        float playerWidth = 15 * 2;
        float playerHeight = 25 * 2;
        int w = 50;
        int x = wW / 2 - 175;

        int overlayId = addEntityExtra<SpriteEntity>([](Entity* entity)
        {
            entity->addComponent("animation", new AnimationComponent(255, 0, 300.f, [sprite = entity->getComponent<TextureComponent>("texture")](float newValue) { sprite->setColor(sprite->getColor().WithAlpha(newValue)); }, nullptr, false));
        },"textures/rectangle.png", 0, 0, Color{ 0, 0, 0, 0 }, wW, wH, 9999);
        auto overlayEntity = getEntity(overlayId);
        auto overlayAnimation = overlayEntity->getComponent<AnimationComponent>("animation");

        if (fadeIn)
        {
            overlayAnimation->play();
        }

        addEntity(new SpriteEntity("textures/spacebiem.png", x, 100, Color::White(), -1, -1));
        addEntity(new SpriteEntity("textures/player-standing.png", x + 260, 115, Color::White(), playerWidth, playerHeight));
        addEntity(new PlanetEarthEntity(-250.f, static_cast<float>(wH - 250), Color({ 71, 166, 245, 255 }), planetWidth, planetHeight, 0, 10.f));
        addEntity(new PlanetMoonEntity(static_cast<float>(wW - 250), static_cast<float>(wH - 250), Color::White(), planetWidth, planetHeight, 0));

        auto buttonTexture = "textures/button_white.png";
        auto buttonColor = Color{ 35, 65, 112 };
        auto buttonTextColor = Color::White();
        auto buttonSize = Size{ 250, 100 };

        int beginY = 330;
        int incr = 115;

        auto newGameClick = [](StateManager* e) {  e->getSceneManager().navigateTo<DifficultyScene>(); };
        auto continueClick = [overlayAnimation](StateManager* e)
        {
            overlayAnimation->setOnFinished([e] { e->getSceneManager().navigateTo<LevelScene>(false);  });
            overlayAnimation->playReversed();
        };

        auto highscoreClick =[](StateManager* e) { e->getSceneManager().navigateTo<HighScoreScene>(); };
        auto helpClick = [](StateManager* e) {  e->getSceneManager().navigateTo<HelpScene>(); };
        auto CreditsButtonClicked = [](StateManager* e) { e->getSceneManager().navigateTo<CreditsScene>(); };
        auto LevelEditorButtonClicked = [](StateManager* e) { e->getSceneManager().navigateTo<LevelLoadScene>(); };

        auto buttonX = x + 50;

        addEntity(new ButtonUIEntity(buttonX , beginY + (incr * 0), buttonColor, buttonTextColor, buttonSize, "New game", buttonTexture, newGameClick, nullptr));

        std::function<void(StateManager*)> continueEventHandler = nullptr;
        bool saveBlobExists = FileHandler::exists(Player::current().saveLocation());

        if (saveBlobExists) {
            continueEventHandler = continueClick;
        }

//        addEntity(new ButtonUIEntity(x + 100, beginY + (incr * 1), buttonColor, buttonTextColor, buttonSize, "Continue", buttonTexture, continueEventHandler, nullptr));
//        addEntity(new ButtonUIEntity(x + 100, beginY + (incr * 2), buttonColor, buttonTextColor, buttonSize, "Level editor", buttonTexture, LevelEditorButtonClicked, nullptr));

        beginY += 20;
        addEntity(new ButtonUIEntity(buttonX , beginY + (incr * 1), buttonColor, buttonTextColor, buttonSize, "Highscores", buttonTexture, highscoreClick, nullptr));
        addEntity(new ButtonUIEntity(buttonX , beginY + (incr * 2), buttonColor, buttonTextColor, buttonSize, "Help", buttonTexture, helpClick, nullptr));
        addEntity(new ButtonUIEntity(buttonX , beginY + (incr * 3), buttonColor, buttonTextColor, buttonSize, "Credits", buttonTexture, CreditsButtonClicked));
        beginY += 20;
//        addEntity(new ButtonUIEntity(x + 100, beginY + (incr * 6), buttonColor, buttonTextColor, buttonSize, "Change profile", buttonTexture, [this](StateManager* b) { b->getSceneManager().navigateTo<ProfileScene>(); }, nullptr));
//        addEntity(new ButtonUIEntity(x + 100, beginY + (incr * 7), buttonColor, buttonTextColor, buttonSize, "Quit", buttonTexture, [this](auto b) { signalQuit(); }, nullptr));

        FileParser parser;
        map<string, int> resources = parser.resourcesContent();

        addEntity(new SpriteEntity("textures/resources-hud.png", 25.f, 25.f, Color::White(), 601, 253, 100u));
        float rX = 99.f;
        float rIncr = 136.f;
        float rY = 202.f;
        addEntity(new ResourceUIEntity(rX + (rIncr * 0), rY, Color::White(), "uranium", resources["uranium"], 30));
        addEntity(new ResourceUIEntity(rX + (rIncr * 1), rY, Color::White(), "diamond", resources["diamond"], 30));
        addEntity(new ResourceUIEntity(rX + (rIncr * 2), rY, Color::White(), "metal", resources["metal"], 30));
        addEntity(new ResourceUIEntity(rX + (rIncr * 3), rY, Color::White(), "anti-matter", resources["anti-matter"], 30));

        if(!getTransitionManager().getAudioDevice().isPlayingMusic("audio/menu.mp3"))
            getTransitionManager().getAudioDevice().playMusic("audio/menu.mp3", -1);
    }

    void MenuScene::input()
    {
        if (im.isKeyDown("Q")) {
            signalQuit();
        }

        if (im.isKeyDown("S")) {
//            getTransitionManager().navigateTo<HighScoreScene>();
        }

        if (im.isKeyDown("Return")) {
            getTransitionManager().getAudioDevice().playSoundEffect("audio/switch.mp3", 0, 5, 64);
//            getTransitionManager().navigateTo<LevelScene>();
        }
    }

    void MenuScene::update()
    {
        updateEntities();
    }

    void MenuScene::render(const float deltaTime)
    {
        getTransitionManager().drawBackground("textures/space.png");
        updateEntities(deltaTime);
    }
}
