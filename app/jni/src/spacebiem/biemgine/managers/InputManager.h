#pragma once


#include "../primitives/Primitives.h"
#include "../core/Window.h"

namespace biemgine
{
    class InputManager
    {
    public:
        InputManager();
        ~InputManager();

        void setWindow(const Window * pWindow);
        void update();
        bool isKeyDown(const char* key) const;
        Point getMouseLocation() const;
        bool isLeftMouseDown() const;
        bool isRightMouseDown() const;
        bool isMiddleMouseDown() const;

    private:
        const unsigned char* keyStates;
        const Window* window;

        bool ignoreInput = false;

        bool mouseDown = false;
        bool mouseUp = false;
        bool mouseMoving = false;

        int swiping = 0;
        std::string swipeDirection;
        int swipe_det_sX = 0;
        int swipe_det_sY = 0;
        int swipe_det_eX = 0;
        int swipe_det_eY = 0;
        int min_x = 30;  //min x swipe for horizontal swipe
        int max_x = 400;  //max x difference for vertical swipe
        int min_y = 50;  //min y swipe for vertical swipe
        int max_y = 60;  //max y difference for horizontal swipe

        int swipePersistence = 60;

        void checkSwipe();

    };
}
