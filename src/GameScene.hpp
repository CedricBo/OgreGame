#pragma once

#include <OgreSceneManager.h>
#include <Bullet/OgreBullet.h>

#include "Player.hpp"
#include "Tree.hpp"

namespace MazeGame
{
    class GameScene : public Ogre::SceneManager
    {
    public:
        static const std::string typeName;

        GameScene(std::string instanceName);
        ~GameScene();

        const std::string& getTypeName() const;

        void init();

        void initTorchLight(Ogre::SceneNode* parent);
        void initCamera(Ogre::SceneNode* parent);
        void initPlayer(Ogre::SceneNode* parent);
        void initGound(Ogre::SceneNode* parent);

        void addFire(Ogre::SceneNode* parent);
        void addTree(Ogre::SceneNode* parent, Ogre::Vector3f position);

        Ogre::Camera* getCamera() const;

        Ogre::SceneNode* getCameraNode() const;

        Player* getPlayer() const;

        Ogre::Light* getTorchLight() const;

        void update();

        Ogre::Bullet::DynamicsWorld* getWorld();
    private:
        Ogre::Bullet::DynamicsWorld _world;

        Ogre::SceneNode* _cameraNode;
        Ogre::Camera* _camera;

        std::unique_ptr<Player> _player;

        Ogre::SceneNode* _torchLightNode;
        Ogre::Light* _torchLight;

        Ogre::Entity* _fire;
        Ogre::Light* _fireLight;
        Ogre::SceneNode* _fireNode;

        std::vector<Tree> _trees;
    };
}