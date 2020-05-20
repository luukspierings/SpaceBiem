
#include "EntityManager.h"

#include <chrono>

#include <android/log.h>
#define LOG(...) __android_log_print(ANDROID_LOG_WARN, "SPACEBIEM", __VA_ARGS__)

namespace biemgine
{
    EntityManager::EntityManager(std::shared_ptr<SystemManager> manager) : systemManager(manager)
    {}

    EntityManager::~EntityManager()
    {
        for (auto it = entities.begin(); it != entities.end(); ++it)
        {
            delete (*it);
        }

        entities.clear();
    }

    int EntityManager::addEntity(Entity* entity)
    {
//        entities.push_back(entity);
//
        auto tc = entity->getComponent<TextureComponent>("texture");

        if(tc != nullptr) {
            LOG("ADDING ENTITY: %s", tc->getPath().data());
        }
//        return entity->getId();

        LOG("ADDING ENTITY, ONSCREEN: %s", entity->getIsOnScreen() ? "1" : "0");

        entities.emplace_back(entity);

        entities.back()->calculateBounds();
        entities.back()->checkOCCheckable();
        systemManager->onAddEntity(*entities.back());

        return entities.back()->getId();
    }

    void EntityManager::updateEntities(std::shared_ptr<SystemManager> manager)
    {
        manager->preUpdate();
        manager->acceptForUpdate();

        manager->postUpdate();
    }

    void EntityManager::updateEntities(std::shared_ptr<SystemManager> manager, const float deltaTime)
    {
        manager->preUpdate(deltaTime);
        manager->acceptForUpdate(deltaTime);

        manager->postUpdate(deltaTime); 
    }

    void EntityManager::addEntitiesToSystems()
    {
        for (auto & entity : entities)
        {
            entity->calculateBounds();
            entity->checkOCCheckable();

            systemManager->onAddEntity(*entity); 
        }
    }

    Entity* EntityManager::getEntity(int id) const
    {
        for (auto entity = entities.begin(); entity != entities.end(); ++entity)
        {
            if ((*entity)->getId() == id) return (*entity);
        }

        return nullptr;
    }

    Entity * EntityManager::getEntity(string tag) const
    {
        for (auto entity = entities.begin(); entity != entities.end(); ++entity)
        {
            if ((*entity)->getTag() == tag) return (*entity);
        }

        return nullptr;
    }
}
