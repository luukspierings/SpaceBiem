
#include "CreditsScene.h"
#include "MenuScene.h"

#include "../entities/PlanetEarthEntity.h"
#include "../entities/PlanetMoonEntity.h"
#include "../entities/ButtonUIEntity.h"

#include "../globals/Fonts.h"

using biemgine::Size;
using biemgine::SpriteEntity;
using biemgine::TextUIEntity;
using biemgine::TextComponent;

namespace spacebiem
{

    void onCreditsButtonEntered(StateManager* e)
    {
        e->getAudioDevice().playSoundEffect("audio/switch.mp3", 0, -1, 128);
    }

    void CreditsMenuButtonClicked(StateManager* e)
    {
        e->getAudioDevice().playSoundEffect("audio/idroid.mp3", 0, -1, 128);
        e->getSceneManager().navigateTo<MenuScene>();
    }


    void CreditsScene::created() {
        enableRendering();
        enableUI();
        enableScripts();

        int wW = getTransitionManager().getWindowWidth();
        int wH = getTransitionManager().getWindowHeight();
        float planetWidth = 500;
        float planetHeight = 500;
        int w = 50;
        int x = wW / 2;

        addEntity(new SpriteEntity("textures/teambiem.png", static_cast<float>(wW / 2 - 500.f), 50.f, Color::White(), -1, -1, 100u));
        addEntity(new SpriteEntity("textures/spacebiem.png", static_cast<float>(wW / 2 + 200.f), 50.f, Color::White(), -1, -1, 100u));

        auto thanksToTextId = addEntity(new TextUIEntity(Fonts::Roboto(), x, 300, Color{ 232, 228, 41 }, "Thanks to:", true));
        getEntity(thanksToTextId)->getComponent<TextComponent>("text")->setColor(Color{ 232, 228, 41 });

        auto nameY = 350;
        auto nameYIncr = 50;

        addEntity(new TextUIEntity(Fonts::Roboto(), x, nameY + (0 * nameYIncr), Color::White(), "Tom van Nimwegen", true));
        addEntity(new TextUIEntity(Fonts::Roboto(), x, nameY + (1 * nameYIncr), Color::White(), "Luuk Spierings", true));
        addEntity(new TextUIEntity(Fonts::Roboto(), x, nameY + (2 * nameYIncr), Color::White(), "Kevin Schuurmans", true));
        addEntity(new TextUIEntity(Fonts::Roboto(), x, nameY + (3 * nameYIncr), Color::White(), "Stijn Mommersteeg", true));
        addEntity(new TextUIEntity(Fonts::Roboto(), x, nameY + (4 * nameYIncr), Color::White(), "Jonathan \"sjonnie\" Immink", true));
        addEntity(new TextUIEntity(Fonts::Roboto(), x, nameY + (5 * nameYIncr), Color::White(), "Wilfred \"willy\" van Eck", true));
        addEntity(new TextUIEntity(Fonts::Roboto(), x, nameY + (6 * nameYIncr), Color::White(), "El Cheapo Coffee", true));

//        addEntity(new TextUIEntity(Fonts::Roboto(), x, 450, Color{ 232, 228, 41 }, "Packages: ", true));
//        addEntity(new SpriteEntity("textures/SDL_logo.png", static_cast<float>(x - 100), 425.f, Color::White(), -1, -1, 100u));
//        addEntity(new SpriteEntity("textures/box2d.png", static_cast<float>(x - 100), 575.f, Color::White(), -1, -1, 100u));

//        auto testerTextId = addEntity(new TextUIEntity(Fonts::Roboto(), x, 700, Color::White(), "Special thanks to all testers", true));
//        getEntity(testerTextId)->getComponent<TextComponent>("text")->setColor(Color{ 232, 228, 41 });

        addEntity(new TextUIEntity(Fonts::Roboto(), x, 750, Color::White(), "Copyright 2020 Team Biem", true));

        addEntity(new PlanetEarthEntity(-250.f, static_cast<float>(wH - 250), Color({ 71, 166, 245, 255 }), planetWidth, planetHeight, 0, 10.f));
        addEntity(new PlanetMoonEntity(static_cast<float>(wW - 250), static_cast<float>(wH - 250), Color::White(), planetWidth, planetHeight, 0));

        auto buttonTexture = "textures/button_white.png";
        auto buttonColor = Color{ 35, 65, 112 };
        auto buttonTextColor = Color::White();
        auto buttonSize = Size{ 250, 100 };

        addEntity(new ButtonUIEntity(x - 125, 825, buttonColor, buttonTextColor, buttonSize, "Menu", buttonTexture, CreditsMenuButtonClicked, onCreditsButtonEntered));
    }

    void CreditsScene::input()
    {
        if (im.isKeyDown("Q")) {
            signalQuit();
        }

        if (im.isKeyDown("Backspace")) {
//            // getTransitionManager().navigateTo<MenuScene>();
        }
    }

    void CreditsScene::update()
    {
        updateEntities();
    }

    void CreditsScene::render(const float deltaTime)
    {
        getTransitionManager().drawBackground("textures/space.png");
        updateEntities(deltaTime);
    }
}
