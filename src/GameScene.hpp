#pragma once

#include <OgreSceneManager.h>
#include <Bullet/OgreBullet.h>

namespace MazeGame
{
    class GameScene : public Ogre::SceneManager
    {
    public:
        static const std::string typeName;

        GameScene(std::string instanceName);
        ~GameScene();

        const std::string& getTypeName() const;

        void initTorchLight(Ogre::SceneNode* parent);
        void initCamera(Ogre::SceneNode* parent);

        void initMap();
        void initGound();

        Ogre::Camera* getCamera() const;

        Ogre::SceneNode* getCameraNode() const;
        Ogre::Light* getTorchLight() const;

        void update();

        Ogre::Bullet::DynamicsWorld* getWorld();
    private:
        Ogre::Bullet::DynamicsWorld _world;

        Ogre::Camera* _camera;
        Ogre::Light* _torchLight;

        Ogre::SceneNode* _cameraNode;
        Ogre::SceneNode* _torchLightNode;
    };
}