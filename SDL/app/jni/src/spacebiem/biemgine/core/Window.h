#pragma once

#include "../devices/graphics/GraphicsDevice.h"
#include <string>

using std::string;

namespace biemgine
{
    class Window
    {
    public:
        Window
        (
            const string& title = "Untitled Window",
            const int32_t& width = 800,
            const int32_t& height = 600,
            bool maximize = false
        );

        ~Window();

        int getRenderWidth() const;
        int getRenderHeight() const;

        Size getActualSize() const;

        Point actualToRender(Point actual) const;

        GraphicsDevice* getGraphicsDevice() const;

    private:
        bool init();
        int initWindow(
            const string& title,
            const int32_t& width,
            const int32_t& height,
            const int32_t& options
        );

        int windowId = -1;
        //SDL_Window* window = nullptr;
        GraphicsDevice* gd = nullptr;

        SDL_Window * getWindow(int id) const;
    };
}
