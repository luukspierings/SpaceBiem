/*This source code copyrighted by Lazy Foo' Productions (2004-2020)
and may not be redistributed without written permission.*/

//Using SDL, standard IO, and, strings
#include <SDL.h>
#include <SDL_ttf.h>
#include "../SDL2_mixer/SDL_mixer.h"
#include "../SDL2_image/SDL_image.h"
//#include <SDL_mixer.h>
//#include <SDL_image.h>
//#include <Box2D.h>
//#include <Box2D/Box2D.h>
#include <../Box2D/src/Box2D.h>

#include <stdio.h>
#include <string>
#include <string.h>

#include "spacebiem/biemgine/Biemgine.h"

#include "spacebiem/biemgine/devices/graphics/SDLGraphicsDevice.h"
#include "spacebiem/biemgine/systems/physics/PhysicsSystem.h"

#include "spacebiem/spacebiem/stdafx.h"
#include "spacebiem/spacebiem/scenes/MenuScene.h"
#include "spacebiem/spacebiem/globals/Ads.h"
#include "spacebiem/spacebiem/scenes/ProfileScene.h"
#include "spacebiem/spacebiem/globals/Player.h"

#include "spacebiem/biemgine/core/Engine.h"

using biemgine::Engine;
using biemgine::Size;
using spacebiem::ProfileScene;
using spacebiem::MenuScene;
using spacebiem::Player;

#include <android/log.h>
#define LOG(...) __android_log_print(ANDROID_LOG_WARN, "SPACEBIEM", __VA_ARGS__)

int main( int argc, char* args[] )
{
//    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    try
    {

//    if( !init() )
//    {
//        SDL_Log( "Failed to init!\n" );
//    }
//    else {
//        while (true) {}
//    }

        LOG("Starting up app...");


//        Ads::instance().initialize();

        Engine engine;

        Player::current().setName(Player::playerOneName());

        engine.start<MenuScene>("SpaceBiem", Size{ 1920, 1080 }, false);

//        Ads::instance().close();


    }
    catch (const std::exception& e)
    {
        LOG("An unexpected error occured..", e.what());
//        system("pause");
    }

    LOG("Stopping app..");

    while (true) {}


    return 0;
}

