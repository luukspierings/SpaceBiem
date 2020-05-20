
#include "HelpScene.h"
#include "MenuScene.h"
#include "LevelScene.h"

#include "../entities/ButtonUIEntity.h"
#include "../entities/PlayerEntity.h"

#include "../entities/ScoreUIEntity.h"
#include "../entities/OxygenUIEntity.h"
#include "../entities/ResourceUIEntity.h"

#include "../entities/PlanetEarthEntity.h"
#include "../entities/PlanetMoonEntity.h"
#include "../entities/PlanetSandEntity.h"
#include "../entities/PlanetToxicEntity.h"
#include "../entities/PlanetLavaEntity.h"
#include "../entities/PlanetIceEntity.h"

#include "../systems/MovementSystem.h"
#include "../systems/GravitySystem.h"
#include "../systems/JumpSystem.h"
#include "../systems/OxygenSystem.h"
#include "../systems/OxygenUISystem.h"
#include "../systems/ScoreUISystem.h"
#include "../systems/ScoreSystem.h"
#include "../systems/ResourceUISystem.h"
#include "../systems/ResourceCollectingSystem.h"

#include "../globals/Fonts.h"
#include "../globals/Colors.h"
#include "../FileParser.h"

using biemgine::AnimationComponent;
using biemgine::TextUIEntity;
using biemgine::SpriteEntity;

namespace spacebiem
{

    void previousButtonClicked(StateManager* e)
    {

    }
    void nextButtonClicked(StateManager* e)
    {

    }
    void returnToGameButtonClicked(StateManager* e)
    {
        e->getSceneManager().navigateTo<LevelScene>(false);
    }
    void returnToMenuButtonClicked(StateManager* e)
    {
        e->getSceneManager().navigateTo<MenuScene>();
    }

    void HelpScene::created()
    {
        enableRendering();
        enablePhysics();
        enableUI();
        enableScripts();
        enableAnimations();

        addSystem<GravitySystem>();
        addSystem<MovementSystem>();
        addSystem<JumpSystem>();

        getTransitionManager().getAudioDevice().stopSoundEffect("");

        if (currentSlide > 1) {
            addSystem<OxygenSystem>();
            addSystem<OxygenUISystem>();
            addSystem<ScoreSystem>();
            addSystem<ScoreUISystem>();
            addSystem<ResourceUISystem>();
            addSystem<ResourceCollectingSystem>();
        }

        int wW = getTransitionManager().getWindowWidth();
        int wH = getTransitionManager().getWindowHeight();
        int bW = 300;
        int bH = 100;
        int edgeMargin = 20;
        int middleMargin = 10;


        int overlayId = addEntityExtra<SpriteEntity>([](Entity* entity)
        {
            entity->addComponent("animation", new AnimationComponent(255, 0, 300.f,[sprite = entity->getComponent<TextureComponent>("texture")](float newValue) { sprite->setColor(sprite->getColor().WithAlpha(newValue)); }, nullptr, false));
        }, "textures/rectangle.png", 0, 0, Color{ 0, 0, 0, 0 }, wW, wH, 9999);

        auto overlayEntity = getEntity(overlayId);
        auto overlayAnimation = overlayEntity->getComponent<AnimationComponent>("animation");
      
        if(fade)
            overlayAnimation->play();
        if (fromLevel) {
            addEntity(new ButtonUIEntity((wW - bW - bW) / 2 - middleMargin, wH - edgeMargin - bH, Color{ 35, 65, 112 }, Color::White(), Size{ bW,bH }, "Return to menu", "textures/button_white.png", returnToMenuButtonClicked));
            addEntity(new ButtonUIEntity((wW) / 2 + middleMargin, wH - edgeMargin - bH, Color{ 35, 65, 112 }, Color::White(), Size{ bW,bH }, "Return to game", "textures/button_white.png",
                    [this, overlayAnimation](StateManager* e)
                    {
                        overlayAnimation->setOnFinished([e] { /* e->getSceneManager().navigateTo(new LevelScene(false); */ }); overlayAnimation->playReversed(); })
             );
        }
        else {
            addEntity(new ButtonUIEntity((wW-bW)/2, wH - edgeMargin - bH, Color{ 35, 65, 112 }, Color::White(), Size{ bW,bH }, "Return to menu", "textures/button_white.png", returnToMenuButtonClicked));
        }

        if(currentSlide > 1)addEntity(new ButtonUIEntity(edgeMargin, wH - edgeMargin - bH, Color{ 35, 65, 112 }, Color::White(), Size{ bW,bH }, "Previous", "textures/button_white.png", [this](StateManager* e) { e->getSceneManager().navigateTo<HelpScene>(fromLevel, false, currentSlide - 1); }));
        else addEntity(new ButtonUIEntity(edgeMargin, wH - edgeMargin - bH, Color{ 35, 65, 112 }, Color::White(), Size{ bW,bH }, "Previous", "textures/button_white.png"));

        if(currentSlide < maxSlides) addEntity(new ButtonUIEntity(wW - edgeMargin - bW, wH - edgeMargin - bH, Color{ 35, 65, 112 }, Color::White(), Size{ bW,bH }, "Next", "textures/button_white.png", [this](StateManager* e) { e->getSceneManager().navigateTo<HelpScene>(fromLevel, false, currentSlide + 1); }));
        else addEntity(new ButtonUIEntity(wW - edgeMargin - bW, wH - edgeMargin - bH, Color{ 35, 65, 112 }, Color::White(), Size{ bW,bH }, "Next", "textures/button_white.png"));


        int pRadius = 500;
        int planetX = (wW - (pRadius*1.5f));
        int planetY = (wH - pRadius) / 2;


        FileParser fp;
        auto atmosphere = fp.atmosphereContent();
        auto score = fp.planetScoreContent();

        // Planet in the slide
        if (currentSlide > 1 && currentSlide <= 4) addEntity(new PlanetEarthEntity(planetX, planetY, Colors::EarthAtmosphere(), pRadius, pRadius, score["earth"], atmosphere["earth"], "Type: Earth"));
        else if (currentSlide == 5) addEntity(new PlanetMoonEntity(planetX, planetY, Colors::MoonAtmosphere(), pRadius, pRadius, score["moon"], "Type: Moon"));
        else if (currentSlide == 6) addEntity(new PlanetSandEntity(planetX, planetY, Colors::SandAtmosphere(), pRadius, pRadius, score["sand"], atmosphere["sand"], "Type: Sand"));
        else if (currentSlide == 7) addEntity(new PlanetToxicEntity(planetX, planetY, Colors::ToxicAtmosphere(), pRadius, pRadius, score["toxic"], atmosphere["toxic"], "Type: Toxic"));
        else if (currentSlide == 8) addEntity(new PlanetIceEntity(planetX, planetY, Colors::IceAtmosphere(), pRadius, pRadius, score["ice"], atmosphere["ice"], "Type: Ice"));
        else if (currentSlide == 9) addEntity(new PlanetLavaEntity(planetX, planetY, Colors::LavaAtmosphere(), pRadius, pRadius, score["lava"], atmosphere["lava"], "Type: Lava"));


        int dialogX = 70;
        int dialogY = 130;
        int yIncr = 55;

        int keyWidth = 50;
        int keyHeight = 50;
        string moveLeft = "textures/keys/LeftArrow.png";
        string moveRight = "textures/keys/RightArrow.png";
        string pause = "textures/keys/P.png";
        string jump = "textures/keys/Space.png";
        int textOffset = 75;


        // Info about things
        switch (currentSlide){
        case 1:
            // slide 1 level info
            addEntity(new TextUIEntity(Fonts::Roboto(50), dialogX, dialogX, Color::White(), "Help 1: The beginning"));

            addEntity(new TextUIEntity(Fonts::Roboto(), dialogX, dialogY + (yIncr * 1), Color::White(), "When starting a new level, you first choose a difficulty."));
            addEntity(new TextUIEntity(Fonts::Roboto(), dialogX, dialogY + (yIncr * 2), Color::White(), "Harder levels are generated with more dangerous planets than easier levels."));
            addEntity(new TextUIEntity(Fonts::Roboto(), dialogX, dialogY + (yIncr * 3), Color::White(), "This makes the level less survivable, but makes it yield more resources."));



//            addEntity(new TextUIEntity(Fonts::Roboto(), dialogX, dialogY + (yIncr * 5), Color::White(), "Use the"));
//            addEntity(new SpriteEntity(pause, textOffset + dialogX, dialogY + (yIncr * 5) - (keyHeight / 4), Color::White(), keyWidth, keyHeight));
//            addEntity(new TextUIEntity(Fonts::Roboto(), textOffset + keyWidth + dialogX, dialogY + (yIncr * 5), Color::White(), "  key in-game to open a menu."));
//
//            addEntity(new TextUIEntity(Fonts::Roboto(), dialogX, dialogY + (yIncr * 6), Color::White(), "Each time when you return to the menu, the game gets saved."));
//            addEntity(new TextUIEntity(Fonts::Roboto(), dialogX, dialogY + (yIncr * 7), Color::White(), "So you can return later to play further."));
//
            addEntity(new TextUIEntity(Fonts::Roboto(), dialogX, dialogY + (yIncr * 5), Color::White(), "When you're gameover your resources are saved."));
            addEntity(new TextUIEntity(Fonts::Roboto(), dialogX, dialogY + (yIncr * 6), Color::White(), "You need to use these resources to unlock further difficulties by going through wormholes."));

            break;
        case 2:
            // slide 2 movement right/left & jumping
            addEntity(new TextUIEntity(Fonts::Roboto(50),dialogX, dialogX, Color::White(), "Help 2: Moving & jumping"));

            addEntity(new TextUIEntity(Fonts::Roboto(), dialogX, dialogY + (yIncr * 1), Color::White(), "By using the wonders of your legs you are able to move around a planet."));

            addEntity(new TextUIEntity(Fonts::Roboto(), dialogX, dialogY + (yIncr * 2), Color::White(), "Tap the RIGHT part of the screen to move left."));
//            addEntity(new SpriteEntity(moveLeft, textOffset + dialogX, dialogY + (yIncr * 2) - (keyHeight / 4), Color::White(), keyWidth, keyHeight));
//            addEntity(new TextUIEntity(Fonts::Roboto(), textOffset + keyWidth + dialogX, dialogY + (yIncr * 2), Color::White(), "  key to move left."));

            addEntity(new TextUIEntity(Fonts::Roboto(), dialogX, dialogY + (yIncr * 3), Color::White(), "Tap the RIGHT part of the screen to move right."));
//            addEntity(new SpriteEntity(moveRight, textOffset + dialogX, dialogY + (yIncr * 3) - (keyHeight / 4), Color::White(), keyWidth, keyHeight));
//            addEntity(new TextUIEntity(Fonts::Roboto(), textOffset + keyWidth + dialogX, dialogY + (yIncr * 3), Color::White(), "  key to move right."));

            
            addEntity(new TextUIEntity(Fonts::Roboto(), dialogX, dialogY + (yIncr * 5), Color::White(), "Getting off the planet, using only your legs, is not enough."));
            addEntity(new TextUIEntity(Fonts::Roboto(), dialogX, dialogY + (yIncr * 6), Color::White(), "Try using your jetpack to jump."));

            keyWidth *= 2; // Spacebar is double the width (TODO: add another modifier for each key texture (1 for normal keys, 2 for space, shift, etc.))
            addEntity(new TextUIEntity(Fonts::Roboto(), dialogX, dialogY + (yIncr * 7), Color::White(), "Swipe UP to jump!"));
//            addEntity(new SpriteEntity(jump, textOffset + dialogX, dialogY + (yIncr * 7) - (keyHeight / 4), Color::White(), keyWidth, keyHeight));
//            addEntity(new TextUIEntity(Fonts::Roboto(), textOffset + keyWidth + dialogX, dialogY + (yIncr * 7), Color::White(), "  key to jump."));
            keyWidth /= 2;

            addEntity(new TextUIEntity(Fonts::Roboto(), dialogX, dialogY + (yIncr * 9), Color::White(), "However when you are moving through space,"));
            addEntity(new TextUIEntity(Fonts::Roboto(), dialogX, dialogY + (yIncr * 10), Color::White(), "there is nothing stopping you from moving further away."));
            addEntity(new TextUIEntity(Fonts::Roboto(), dialogX, dialogY + (yIncr * 11), Color::White(), "So be wise with the choice of trajectory from the planet through endless space..."));

            break;
        case 3:
            // slide 3 UI

            addEntity(new TextUIEntity(Fonts::Roboto(50), dialogX, dialogX, Color::White(), "Help 3: Resources, Oxygen and Score"));

            addEntity(new TextUIEntity(Fonts::Roboto(), dialogX, dialogY + (yIncr * 1), Color::White(), "This is your resource inventory:"));

            addEntity(new SpriteEntity("textures/resources-hud.png", dialogX, dialogY + (yIncr * 2), Color::White(), 401.f, 169.f, 100u));
            addEntity(new ResourceUIEntity(dialogX + 41.f, dialogY + (yIncr * 2) + 120.f, Color::White(), "uranium"));
            addEntity(new ResourceUIEntity(dialogX + 132.f, dialogY + (yIncr * 2) + 120.f, Color::White(), "diamond"));
            addEntity(new ResourceUIEntity(dialogX + 223.f, dialogY + (yIncr * 2) + 120.f, Color::White(), "metal"));
            addEntity(new ResourceUIEntity(dialogX + 314.f, dialogY + (yIncr * 2) + 120.f, Color::White(), "anti-matter"));

            addEntity(new TextUIEntity(Fonts::Roboto(), dialogX, dialogY + (yIncr * 6), Color::White(), "The resources you collect in-game are added to your total resources."));


            addEntity(new TextUIEntity(Fonts::Roboto(), dialogX, dialogY + (yIncr * 8), Color::White(), "This is your oxygentank:"));
            addEntity(new OxygenUIEntity(dialogX + 20.f, dialogY + (yIncr * 9)));
//            addEntity(new TextUIEntity(Fonts::Roboto(), dialogX, dialogY + (yIncr * 10), Color::White(), "The increase and decrease of oxygen can vary between planets."));
            addEntity(new TextUIEntity(Fonts::Roboto(), dialogX, dialogY + (yIncr * 10), Color::White(), "The level is over when there is no oxygen left."));

            addEntity(new TextUIEntity(Fonts::Roboto(), dialogX, dialogY + (yIncr * 12), Color::White(), "This is your score:"));
            addEntity(new ScoreUIEntity(dialogX, dialogY + (yIncr * 13)));
//            addEntity(new TextUIEntity(Fonts::Roboto(), dialogX, dialogY + (yIncr * 14), Color::White(), "Try to get as much as possible and compare it with your friends."));

            break;
        case 4:
            // slide 4 earth

            addEntity(new TextUIEntity(Fonts::Roboto(50), dialogX, dialogX, Color::White(), "Help 4: Planet Earth"));

            addEntity(new TextUIEntity(Fonts::Roboto(), dialogX, dialogY + (yIncr * 1), Color::White(), "This planet is a safe-zone."));
            addEntity(new TextUIEntity(Fonts::Roboto(), dialogX, dialogY + (yIncr * 2), Color::White(), "It is mostly spawned in the middle belt of the planetary system."));
            addEntity(new TextUIEntity(Fonts::Roboto(), dialogX, dialogY + (yIncr * 3), Color::White(), "Safe to land on: Yes"));
            addEntity(new TextUIEntity(Fonts::Roboto(), dialogX, dialogY + (yIncr * 4), Color::White(), "Score increase: " + to_string(score["earth"])));
            addEntity(new TextUIEntity(Fonts::Roboto(), dialogX, dialogY + (yIncr * 5), Color::White(), "Oxygen: " + string((atmosphere["earth"] >= 1)? "Increase" : (atmosphere["earth"] >= -1)? "Decrease" : "Heavy decrease")));

            break;
        case 5:
            // slide 5 moon

            addEntity(new TextUIEntity(Fonts::Roboto(50), dialogX, dialogX, Color::White(), "Help 5: Planet Moon"));

            addEntity(new TextUIEntity(Fonts::Roboto(), dialogX, dialogY + (yIncr * 1), Color::White(), "This planet is mostly a way to other planets."));
            addEntity(new TextUIEntity(Fonts::Roboto(), dialogX, dialogY + (yIncr * 2), Color::White(), "It is mostly spawned in the inner belt of the planetary system, or in the asteroid belts."));
            addEntity(new TextUIEntity(Fonts::Roboto(), dialogX, dialogY + (yIncr * 3), Color::White(), "Safe to land on: Yes"));
            addEntity(new TextUIEntity(Fonts::Roboto(), dialogX, dialogY + (yIncr * 4), Color::White(), "Score increase: " + to_string(score["moon"])));
            addEntity(new TextUIEntity(Fonts::Roboto(), dialogX, dialogY + (yIncr * 5), Color::White(), "Oxygen: Decrease"));

            break;
        case 6:
            // slide 6 sand

            addEntity(new TextUIEntity(Fonts::Roboto(50), dialogX, dialogX, Color::White(), "Help 6: Planet Sand"));

            addEntity(new TextUIEntity(Fonts::Roboto(), dialogX, dialogY + (yIncr * 1), Color::White(), "This planet is partly a safe zone, watch out for the mummies!"));
            addEntity(new TextUIEntity(Fonts::Roboto(), dialogX, dialogY + (yIncr * 2), Color::White(), "It is mostly spawned in the inner belt of the planetary system."));
            addEntity(new TextUIEntity(Fonts::Roboto(), dialogX, dialogY + (yIncr * 3), Color::White(), "Safe to land on: Yes"));
            addEntity(new TextUIEntity(Fonts::Roboto(), dialogX, dialogY + (yIncr * 4), Color::White(), "Score increase: " + to_string(score["sand"])));
            addEntity(new TextUIEntity(Fonts::Roboto(), dialogX, dialogY + (yIncr * 5), Color::White(), "Oxygen: " + string((atmosphere["sand"] >= 1) ? "Increase" : (atmosphere["sand"] >= -1) ? "Decrease" : "Heavy decrease")));

            break;
        case 7:
            // slide 7 toxic

            addEntity(new TextUIEntity(Fonts::Roboto(50), dialogX, dialogX, Color::White(), "Help 7: Planet Toxic"));

            addEntity(new TextUIEntity(Fonts::Roboto(), dialogX, dialogY + (yIncr * 1), Color::White(), "This planet is dangerous, don't stay here too long!"));
            addEntity(new TextUIEntity(Fonts::Roboto(), dialogX, dialogY + (yIncr * 2), Color::White(), "It is mostly spawned in the outer belt of the planetary system."));
            addEntity(new TextUIEntity(Fonts::Roboto(), dialogX, dialogY + (yIncr * 3), Color::White(), "Safe to land on: Yes"));
            addEntity(new TextUIEntity(Fonts::Roboto(), dialogX, dialogY + (yIncr * 4), Color::White(), "Score increase: " + to_string(score["toxic"])));
            addEntity(new TextUIEntity(Fonts::Roboto(), dialogX, dialogY + (yIncr * 5), Color::White(), "Oxygen: " + string((atmosphere["toxic"] >= 1) ? "Increase" : (atmosphere["toxic"] >= -1) ? "Decrease" : "Heavy decrease")));

            break;
        case 8:
            // slide 8 ice

            addEntity(new TextUIEntity(Fonts::Roboto(50), dialogX, dialogX, Color::White(), "Help 8: Planet Ice"));

            addEntity(new TextUIEntity(Fonts::Roboto(), dialogX, dialogY + (yIncr * 1), Color::White(), "This planet is partly a safe zone, watch out for the snowmen!"));
            addEntity(new TextUIEntity(Fonts::Roboto(), dialogX, dialogY + (yIncr * 2), Color::White(), "It is mostly spawned in the outer belt of the planetary system."));
            addEntity(new TextUIEntity(Fonts::Roboto(), dialogX, dialogY + (yIncr * 3), Color::White(), "Safe to land on: Yes"));
            addEntity(new TextUIEntity(Fonts::Roboto(), dialogX, dialogY + (yIncr * 4), Color::White(), "Score increase: " + to_string(score["ice"])));
            addEntity(new TextUIEntity(Fonts::Roboto(), dialogX, dialogY + (yIncr * 5), Color::White(), "Oxygen: " + string((atmosphere["ice"] >= 1) ? "Increase" : (atmosphere["ice"] >= -1) ? "Decrease" : "Heavy decrease")));


            break;
        case 9:
            // slide 8 lava

            addEntity(new TextUIEntity(Fonts::Roboto(50), dialogX, dialogX, Color::White(), "Help 9: Planet Lava"));

            addEntity(new TextUIEntity(Fonts::Roboto(), dialogX, dialogY + (yIncr * 1), Color::White(), "This planet is highly dangerous!"));
            addEntity(new TextUIEntity(Fonts::Roboto(), dialogX, dialogY + (yIncr * 2), Color::White(), "It is mostly spawned in the middle or the inner belt of the planetary system."));
            addEntity(new TextUIEntity(Fonts::Roboto(), dialogX, dialogY + (yIncr * 3), Color::White(), "Safe to land on: No"));

            break;
        default:
            break;
        }

        if(currentSlide != 9) addEntity(new PlayerEntity(planetX + (pRadius / 2), planetY - 50, Color::White(), 25.f, 50.f, 1.0f, false));

    }

    void HelpScene::sceneEnd()
    {
        getTransitionManager().getAudioDevice().stopSoundEffect("");
    }

    void HelpScene::input()
    {
        if (im.isKeyDown("Q")) {
            signalQuit();
        }

        if (im.isKeyDown("Backspace")) {
//            // getTransitionManager().navigateTo<MenuScene>();
        }
    }

    void HelpScene::update()
    {
        updateEntities();
    }

    void HelpScene::render(const float deltaTime)
    {
        getTransitionManager().drawBackground("textures/space.png");
        updateEntities(deltaTime);
    }

}
