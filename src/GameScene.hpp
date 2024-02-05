#pragma once

#include <OgreSceneManager.h>

namespace MazeGame
{
    class GameScene : public Ogre::SceneManager
    {
    public:
        static const std::string typeName;

        GameScene(std::string instanceName);
        ~GameScene();

        const std::string& getTypeName() const;

        void initTorchLight();
        void initCamera();
    private:
        Ogre::Camera* _camera;
        Ogre::Light* _torchLight;
    };
}