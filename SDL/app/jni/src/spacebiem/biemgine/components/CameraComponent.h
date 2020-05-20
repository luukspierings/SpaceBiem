#pragma once




#include "Component.h"

#include <string>
#include <functional>

namespace biemgine
{
    class CameraComponent :
        public Component
    {
    public:
        CameraComponent(std::string onlyWithSuffix = "");
        ~CameraComponent() {};

        float getDeltaX() const;
        float getDeltaY() const;
        int getWindowWidth() const;
        int getWindowHeight() const;
        float getOriginX() const;
        float getOriginY() const;
        std::string getOnlyWithSuffix() const;

        void setDeltaX(float x);
        void setDeltaY(float y);
        void setWindowWidth(int width);
        void setWindowHeight(int height);
        void setOriginX(float x);
        void setOriginY(float y);

    private:
        float windowWidth;
        float windowHeight;

        float deltaX;
        float deltaY;

        float originX;
        float originY;

        std::string onlyWithSuffix = "";
    };
}
