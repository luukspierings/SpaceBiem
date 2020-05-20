
#include "Window.h"
#include "../devices/graphics/SDLGraphicsDevice.h"

#include <SDL.h>

namespace biemgine
{

#include <android/log.h>
#define LOG(...) __android_log_print(ANDROID_LOG_WARN, "SPACEBIEM", __VA_ARGS__)

    SDL_Window * Window::getWindow(int id) const {
        return SDL_GetWindowFromID(id);
    }

    Window::Window(
        const string & title,
        const int32_t & width,
        const int32_t & height,
        bool maximize)
    {
        LOG("CONSTRUCTOR WINDOW");

        if (init()) {

            int flags = 0;
            if (maximize)
                flags = SDL_WINDOW_FULLSCREEN;

            int id = initWindow(title, width, height, flags);

            gd = new SDLGraphicsDevice(getWindow(id));

            SDL_MaximizeWindow(getWindow(id));
        }
    }

    Window::~Window()
    {
        if (gd != nullptr) {
            delete gd;
        }

        LOG("DESTROYING WINDOW");

        SDL_DestroyWindow(getWindow(windowId));
        SDL_Quit();
    }

    int Window::getRenderWidth() const
    {
        auto renderer = SDL_GetRenderer(getWindow(windowId));
        int w, h = 0;
        SDL_RenderGetLogicalSize(renderer, &w, &h);

        return w;
    }

    int Window::getRenderHeight() const
    {
        auto renderer = SDL_GetRenderer(getWindow(windowId));
        int w, h = 0;
        SDL_RenderGetLogicalSize(renderer, &w, &h);

        return h;
    }

    Size Window::getActualSize() const
    {
//        LOG("ACTUAL SIZE");
//
//        if(windowId == -1)
//        {
//            LOG("ACTUAL SIZE is -1");
//
//            Size size;
//            size.width = 0;
//            size.height = 0;
//            return size;
//        }
//
//        LOG("ACTUAL SIZE is not -1");
//
//        LOG("ACTUAL SIZE W ID: %s", std::to_string(windowId).data());

        auto window = getWindow(windowId);
        Size size;
        SDL_GetWindowSize(window, &size.width, &size.height);

        return size;
    }

    Point Window::actualToRender(Point actual) const
    {
//        LOG("ACTUAL TO RENDER");

        Size a = getActualSize();
//        LOG("ACTUAL TO RENDER A: %s", std::to_string(a.width).data());
//        LOG("ACTUAL TO RENDER A: %s", std::to_string(a.height).data());

        Size r = { getRenderWidth(), getRenderHeight() };
//        LOG("ACTUAL TO RENDER R: %s", std::to_string(r.width).data());
//        LOG("ACTUAL TO RENDER R: %s", std::to_string(r.height).data());

        auto scaleH = static_cast<float>(r.height) / static_cast<float>(a.height);
        auto scaleW = 1.f;

        if (a.width != r.width) {
            scaleW = static_cast<float>(r.width) / static_cast<float>(a.width);
        }

        return {
            static_cast<int>(ceil(actual.x * scaleW)),
            static_cast<int>(ceil(actual.y * scaleH))
        };
    }

    GraphicsDevice * Window::getGraphicsDevice() const
    {
        return gd;
    }

    bool Window::init()
    {
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        {
            SDL_Log(  "could not initialize SDL2 /n" , SDL_GetError() );
            return false;
        }

        return true;
    }

    int Window::initWindow(
        const string & title,
        const int32_t & width,
        const int32_t & height,
        const int32_t & options)
    {
        LOG("INITING WINDOW");

        auto w = SDL_CreateWindow(
            (const char*)title.c_str(),
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            width,
            height,
            options
        );

//        SDL_Rect gScreenRect = { 0, 0, 320, 240 };
//
//        SDL_DisplayMode displayMode;
//        if( SDL_GetCurrentDisplayMode( 0, &displayMode ) == 0 )
//        {
//            gScreenRect.w = displayMode.w;
//            gScreenRect.h = displayMode.h;
//        }
//
//        auto w = SDL_CreateWindow( "SpaceBiem", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, gScreenRect.w, gScreenRect.h, SDL_WINDOW_SHOWN );

        if (w == nullptr) {
            SDL_Log(  "Failed to initialize Window/n", SDL_GetError() );
            return 0;
        }
        else {
            windowId = SDL_GetWindowID(w);
            return windowId;
        }
    }
}
