
#include "RenderSystem.h"
#include "../components/ColorComponent.h"
#include "../components/RectangleComponent.h"
#include "../entities/Entity.h"
#include "../devices/graphics/TextureFlip.h"
#include "../components/AnimatedTextureComponent.h"

#include <android/log.h>
#define LOG(...) __android_log_print(ANDROID_LOG_WARN, "SPACEBIEM", __VA_ARGS__)

namespace biemgine
{
    RenderSystem::~RenderSystem() {
        LOG("DESTROYING RENDERSYSTEM");
    }
 
    void RenderSystem::setGraphicsDevice(GraphicsDevice* graphicsDevice)
    {
        this->graphicsDevice = graphicsDevice;
    }


    bool sortByLayer(const std::shared_ptr<OptDrawable> first, const std::shared_ptr<OptDrawable> second)
    {
        return first->layer < second->layer;
    }

    void RenderSystem::onAddEntity(Entity & entity)
    {
        if (!cameraComponent)
        {
            cameraComponent = entity.getComponent<CameraComponent>("camera");
        }

        auto pc = entity.getComponent<PositionComponent>("position");
        if (pc == nullptr)
        {
            return;
        }
           
        auto txs = entity.getComponents<TextComponent>("text");

        for (auto tx : txs)
        {
            LOG("ADDING TEXT TO RENDERING");

            OptDrawText opt;
            opt.entity = &entity;
            opt.textComponent = tx;
            opt.positionComponent = pc;
            opt.isUI = entity.hasComponent("ui");
            opt.type = 0;
            opt.layer = tx->getLayer();

            optDrawableList.push_back(std::make_shared<OptDrawText>(opt));
        }

        auto tc = entity.getComponents<TextureComponent>("texture");

        for (const auto& tex : tc)
        {
            LOG("ADDING TEXTURE ENTITY: %s", tex->getPath().data());

            OptDrawTexture opt;
            opt.entity = &entity;
            opt.textureComponent = tex;
            opt.positionComponent = pc;
            opt.isUI = entity.hasComponent("ui");
            opt.type = 1;
            opt.layer = tex->getLayer();

            optDrawableList.push_back(std::make_shared<OptDrawTexture>(opt));
        }

        std::sort(optDrawableList.begin(), optDrawableList.end(), sortByLayer);
    }

    void RenderSystem::update(const float deltaTime)
    {
        int deltaX = 0;
        int deltaY = 0;

//        LOG("UPDATING DRAWABLES");

        for (const auto& drawable : optDrawableList)
        {
            if(!drawable->entity->getIsOnScreen()){
                LOG("DRAWABLE NOT ON SCREEN");
                continue;
            }
            else if (!drawable->entity->isAlive()){
//                LOG("DRAWABLE NOT ALIVE");
                continue;
            }

//            LOG("DRAWABLE ON SCREEN");
//            LOG("DRAWABLE TYPE: %s", drawable->type);

            if (drawable->type == 0)
            {
//                LOG("DRAWING TEXT");

                auto text = std::static_pointer_cast<OptDrawText>(drawable);

                if (!text->textComponent->isVisible()) continue;

                deltaX = 0;
                deltaY = 0;

                if (cameraComponent != nullptr && !text->isUI)
                {
                    deltaX = cameraComponent->getDeltaX();
                    deltaY = cameraComponent->getDeltaY();
                }

                auto size = graphicsDevice->drawText(
                    text->textComponent->getFont(),
                    text->textComponent->getText(),
                    text->textComponent->getOffsetX() + text->positionComponent->getX() + deltaX,
                    text->textComponent->getOffsetY() + text->positionComponent->getY() + deltaY,
                    text->textComponent->getColor(),
                    0,
                    biemgine::NONE,
                    text->textComponent->isCenter()
                );

                text->textComponent->setTextSize(size);
            }
            else
            {
                auto texture = std::static_pointer_cast<OptDrawTexture>(drawable);

                if (!texture->textureComponent->isVisible()) continue;

                deltaX = 0;
                deltaY = 0;
                string onlyWithSuffix = "";

                if (cameraComponent != nullptr && !texture->isUI)
                {
                    deltaX = cameraComponent->getDeltaX();
                    deltaY = cameraComponent->getDeltaY();
                    onlyWithSuffix = cameraComponent->getOnlyWithSuffix();
                }

                graphicsDevice->drawTexture(
                    texture->textureComponent->getPath(),
                    texture->textureComponent->getOffsetX() + texture->positionComponent->getOriginX() + ((drawable->entity->getTag().find(onlyWithSuffix) != std::string::npos || onlyWithSuffix == "") ? deltaX : 0.f),
                    texture->textureComponent->getOffsetY() + texture->positionComponent->getOriginY() + ((drawable->entity->getTag().find(onlyWithSuffix) != std::string::npos || onlyWithSuffix == "") ? deltaY : 0.f),
                    texture->textureComponent->getWidth(),
                    texture->textureComponent->getHeight(),
                    texture->textureComponent->getRotation() + texture->positionComponent->getRotation(),
                    texture->textureComponent->getColor(),
                    texture->textureComponent->getFlip(),
                    false,
                    texture->textureComponent->getRect(),
                    texture->textureComponent->getBlendMode()
                );

                texture->textureComponent->update(deltaTime);
            }

           
        }
    }

    void RenderSystem::onSceneSwitch()
    {
        if (graphicsDevice != nullptr)
            graphicsDevice->clear();
    }
}
