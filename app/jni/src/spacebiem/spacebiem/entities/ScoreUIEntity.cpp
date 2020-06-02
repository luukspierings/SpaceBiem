
#include "ScoreUIEntity.h"
#include "../components/ScoreComponent.h"
#include "../globals/Fonts.h"
#include "../../biemgine/primitives/Primitives.h"

using std::string;
using biemgine::PositionComponent;
using biemgine::ColorComponent;
using biemgine::UIComponent;
using biemgine::TextComponent;
using biemgine::Size;
using biemgine::SizeRect;
using biemgine::Point;
using biemgine::Color;

namespace spacebiem
{
    ScoreUIEntity::ScoreUIEntity(float x, float y, float score, const string& name)
    {
        addComponent("position", new PositionComponent(x, y));
        addComponent("color", new ColorComponent(Color::White()));
        addComponent("ui", new UIComponent(SizeRect{Point{0,0,0}, Size{100, 100}}));
        addComponent("score", new ScoreComponent(score, name));
        addComponent("text", new TextComponent(Fonts::Roboto()));
    }
}
