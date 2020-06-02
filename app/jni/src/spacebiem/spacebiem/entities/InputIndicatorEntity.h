#pragma once

#include "../../biemgine/Biemgine.h"

using biemgine::Entity;
using biemgine::PositionComponent;
using biemgine::ColorComponent;
using biemgine::UIComponent;
using biemgine::RectangleComponent;
using biemgine::TextureComponent;

#include "../components/OxygenComponent.h"
#include "../globals/Fonts.h"

namespace spacebiem
{
    class InputIndicatorEntity :
        public Entity
    {
    public:
        InputIndicatorEntity(int wW, int wH)
        {
            auto aspectRatio = 3;
            auto margin = 50;

            auto halfW = wW / 2;
            auto arrowW = (halfW - (2 * margin)) / 3;
            auto arrowH = arrowW / aspectRatio;

            auto arrowY = wH - arrowH - margin;
//            auto xOffset = (halfW - arrowW - (2 * margin)) / 2;
            auto xOffset = margin;

            addComponent("position", new PositionComponent(0, 0));
            addComponent("ui", new UIComponent);
            addComponent("texture", new TextureComponent("textures/arrow_left.png", xOffset , arrowY, arrowW, arrowH, 190u, true, "arrow_left", { 255, 255, 255, 50 }));
            addComponent("texture", new TextureComponent("textures/arrow_right.png", wW - arrowW - xOffset, arrowY, arrowW, arrowH, 190u, true, "arrow_right", { 255, 255, 255, 50 }));

            auto textW = 30;
            addComponent("text", new TextComponent(Fonts::Roboto(), "Swipe up to jump!", { 255,255,255,255 }, true, halfW, wH - margin - (arrowH / 2) + 20));

            setTag("InputIndicator");
        };
    };
}
