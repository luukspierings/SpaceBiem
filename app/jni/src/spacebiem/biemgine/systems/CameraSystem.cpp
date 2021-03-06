
#include "CameraSystem.h"


#include <android/log.h>
#define LOG(...) __android_log_print(ANDROID_LOG_WARN, "SPACEBIEM", __VA_ARGS__)

namespace biemgine
{
    void CameraSystem::onAddEntity(Entity & pEntity)
    {
        auto camera = pEntity.getComponent<CameraComponent>("camera");
        auto pc = pEntity.getComponent<PositionComponent>("position");

        if (pc == nullptr)
            return;

        CSEntity entity;
        entity.positionComponent = pc;
        entity.entity = &pEntity;
        allEntities.push_back(std::move(entity));

        if (camera != nullptr)
        {
            CameraEntity cEntity;
            cEntity.positionComponent = pc;
            cEntity.cameraComponent = camera;
            cEntity.entity = &pEntity;
             
            cameraEntity = cEntity;
        }      
    }

    void CameraSystem::update()
    {
        if (cameraEntity.cameraComponent) {
            LOG("SETTING VARS IN CAMERA COMPONENT");

            cameraEntity.cameraComponent->setWindowWidth(getStateManager()->getWindowWidth());
            cameraEntity.cameraComponent->setWindowHeight(getStateManager()->getWindowHeight());

            cameraEntity.cameraComponent->setOriginX(cameraEntity.positionComponent->getOriginX());
            cameraEntity.cameraComponent->setOriginY(cameraEntity.positionComponent->getOriginY());

            int xDelta = static_cast<int>((cameraEntity.cameraComponent->getWindowWidth()) / 2 - static_cast<int>(cameraEntity.positionComponent->getOriginX()));
            int yDelta = static_cast<int>((cameraEntity.cameraComponent->getWindowHeight()) / 2 - static_cast<int>(cameraEntity.positionComponent->getOriginY()));

            cameraEntity.cameraComponent->setDeltaX(static_cast<float>(xDelta));
            cameraEntity.cameraComponent->setDeltaY(static_cast<float>(yDelta));

        }

        LOG("SETTING ENTITIES ONSCREEN");
        for (const auto &e : allEntities)
        {
            e.entity->setIsOnScreen(isOnScreen(e));
        }
        
    }

    bool CameraSystem::isOnScreen(const CSEntity & e)
    {
        //if (!e.entity->isAlive()) return false;
//        LOG("CHECKING ONSCREEN");

        if (e.entity->isCheckable() && cameraEntity.cameraComponent)
        {
//            LOG("ENTITY IS CHECKABLE");

            float dX = cameraEntity.cameraComponent->getOriginX();
            float dY = cameraEntity.cameraComponent->getOriginY();
            int wW = cameraEntity.cameraComponent->getWindowWidth() / 2;
            int wH = cameraEntity.cameraComponent->getWindowHeight() / 2;

//            LOG("RETRIEVED VARS");

            if (e.entity->getTag().find(cameraEntity.cameraComponent->getOnlyWithSuffix()) == std::string::npos) {
                return true;
            }

//            LOG("CHECKING CORDS");

            if (e.entity->minX + e.positionComponent->getOriginX() > dX + wW){
                return false;
            }
            if (e.entity->maxX + e.positionComponent->getOriginX() < dX - wW) {
                return false;
            }
            if (e.entity->minY + e.positionComponent->getOriginY() > dY + wH) {
                return false;
            }
            if (e.entity->maxY + e.positionComponent->getOriginY() < dY - wH) {
                return false;
            }
        }

        return true;
    }
}
