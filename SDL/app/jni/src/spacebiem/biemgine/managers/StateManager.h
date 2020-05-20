#pragma once


//#include "../../biemgine/scenes/Scene.h"
#include "../core/Window.h"
#include "InputManager.h"
#include "../entities/Entity.h"
#include "../devices/audio/AudioDevice.h"

using std::string;

namespace biemgine
{
    class SceneManager;
    class Scene;

    class StateManager
    {
    public:
        StateManager( SceneManager& pSceneManager,const Window& pWindow);
        ~StateManager();

        int getWindowWidth() const;
        int getWindowHeight() const;

        void drawBackground(const string& backgroundPath);

        void setInputManager(const InputManager* manager) {
            inputManager = manager;
        }

        const InputManager* getInputManager() const
        {
            return inputManager;
        }

        AudioDevice& getAudioDevice() const
        {
            return *audioDevice;
        }

        Entity * getEntity(int id) const;

        SceneManager & getSceneManager() const;

    private:
        SceneManager* sceneManager = nullptr;
        const InputManager* inputManager = nullptr;
        const Window* window = nullptr;
        AudioDevice* audioDevice;
    };
}
