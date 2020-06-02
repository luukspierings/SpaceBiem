
#include "InputManager.h"

#include <SDL.h>

#include <android/log.h>
#define LOG(...) __android_log_print(ANDROID_LOG_WARN, "SPACEBIEM", __VA_ARGS__)

namespace biemgine
{
    InputManager::~InputManager() {
        LOG("INPUT MANAGER DECONSTRUCTING");
    }

    InputManager::InputManager()
    {
//        update();
    }

    void InputManager::setWindow(const Window * pWindow)
    {
        window = pWindow;
    }

    void InputManager::update()
    {
        SDL_PumpEvents();
//        keyStates = SDL_GetKeyboardState(nullptr);

        mouseDown = false;
        mouseUp = false;
        mouseMoving = false;

        SDL_Event e;
        while(SDL_PollEvent( &e ) != 0){
            switch(e.type){
                case SDL_MOUSEBUTTONDOWN:
                    mouseDown = true;
                    break;
                case SDL_MOUSEBUTTONUP:
                    mouseUp = true;
                    break;
                case SDL_MOUSEMOTION:
                    mouseMoving = true;
                    break;
            }
        }

        checkSwipe();
    }

    void InputManager::checkSwipe()
    {
        if(swiping != 0)
            swiping--;

        swipeDirection = "";

        if(mouseDown){
//            LOG("CHECKING SWIPE MOUSEDOWN");
////            Point position = getMouseLocation();
//
//            int x = 0, y = 0;
//
//            SDL_GetMouseState(&x, &y);
//
//            LOG("GOT MOUSE STATE");
//
//            LOG("MOUSE STATE X: %s", std::to_string(x).data());
//            LOG("MOUSE STATE Y: %s", std::to_string(y).data());
//
//            if(window == nullptr)
//                return;
//
//            Point position = window->actualToRender({ x,y });
//
//
//            LOG("CHECKING SWIPE MOUSEDOWN X: %s", std::to_string(position.x).data());
//            LOG("CHECKING SWIPE MOUSEDOWN Y: %s", std::to_string(position.y).data());
//
//            swipe_det_sX = position.x;
//            swipe_det_sY = position.y;
        }
        if(mouseMoving){
            LOG("CHECKING SWIPE MOUSEMOVING");
            Point position = getMouseLocation();

            if(swipe_det_sX == 0)
                swipe_det_sX = position.x;
            if(swipe_det_eY == 0)
                swipe_det_sY = position.y;

            swipe_det_eX = position.x;
            swipe_det_eY = position.y;
        }
        if(mouseUp){
            LOG("CHECKING SWIPE MOUSEUP");
//            if ((((swipe_det_eX - min_x > swipe_det_sX) || (swipe_det_eX + min_x < swipe_det_sX)) && ((swipe_det_eY < swipe_det_sY + max_y) && (swipe_det_sY > swipe_det_eY - max_y) && (swipe_det_eX > 0)))) {
//                if(swipe_det_eX > swipe_det_sX) swipeDirection = "r";
//                else swipeDirection = "l";
//            }
                //vertical detection
            if ((((swipe_det_eY - min_y > swipe_det_sY) || (swipe_det_eY + min_y < swipe_det_sY)) && ((swipe_det_eX < swipe_det_sX + max_x) && (swipe_det_sX > swipe_det_eX - max_x) && (swipe_det_eY > 0)))) {
                if(swipe_det_eY > swipe_det_sY) swipeDirection = "d";
                else swipeDirection = "u";
            }

            if (swipeDirection != "") {
                swiping = swipePersistence;
                LOG("SWIPE! %s", swipeDirection.data());
            }

            swipe_det_sX = 0;
            swipe_det_sY = 0;
            swipe_det_eX = 0;
            swipe_det_eY = 0;
        }
    }

    bool InputManager::isKeyDown(const char * key) const
    {
        if(key == "Space" && swiping != 0 && swipeDirection == "u")
            return true;

        bool mouseDown = isLeftMouseDown();
        if(!mouseDown)
            return false;

        Point position = getMouseLocation();
        int wW = window->getRenderWidth();
        int wH = window->getRenderHeight();

        int cornerWidth = wW / 2;
        int cornerHeight = wH / 2;

        if(key == "Left" && position.x < cornerWidth && position.y > cornerHeight)
            return true;

        if (key == "Right" && position.x > cornerWidth && position.y > cornerHeight)
            return true;

        return false;

//        return keyStates[SDL_GetScancodeFromName(key)];
    }

    Point InputManager::getMouseLocation() const
    {
        int x = 0, y = 0;

        SDL_GetMouseState(&x, &y);

        return window->actualToRender({ x,y });
    }

    bool InputManager::isLeftMouseDown() const
    {
        return (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) == 1;
    }

    bool InputManager::isRightMouseDown() const
    {
        return (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT)) == 1;
    }

    bool InputManager::isMiddleMouseDown() const
    {
        return (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_MIDDLE)) == 1;
    }
}
