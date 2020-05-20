#pragma once

#include "../scenes/Scene.h"
#include "StateManager.h"
#include <map>
#include <vector>
#include <memory>

using std::map;
using std::string;

namespace biemgine
{
    class SceneManager
    {
    public:
        void createStateManager(const Window& window);
        bool checkNextScene();

        SceneManager();
        ~SceneManager();

        std::shared_ptr<StateManager> getStateManager();

        template<class TScene, typename ...TArgs>
        void navigateTo(TArgs && ...arguments);

        std::shared_ptr<EntityManager> getEntityManager() const;
        Entity* getCurrentSceneEntity(int id) const;

    private:
        std::unique_ptr<Scene> currentScene{ nullptr };
        const Window* currentWindow;
        std::shared_ptr<StateManager> stateManager{ nullptr };

        std::unique_ptr<Scene> nextScene{ nullptr };

        //int nextScene;
    };

    template<class TScene, typename ...TArgs>
    void SceneManager::navigateTo(TArgs && ...arguments)
    {
        nextScene = std::make_unique<TScene>(*stateManager, std::forward<TArgs>(arguments)...);

        if (currentScene != nullptr)
            currentScene->signalQuit();
    }
}
