#pragma once

#include <OgreSceneManager.h>
#include <Bullet/OgreBullet.h>

#include "Game.hpp"
#include "Player.hpp"
#include "Battery.hpp"

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

        void initCamera(Ogre::SceneNode* parent);
        void initPlayer(Ogre::SceneNode* parent);
        void initGound(Ogre::SceneNode* parent);

        void addBattery(Ogre::SceneNode* parent, Ogre::Vector3f position);

        Ogre::Camera* getCamera() const;

        Ogre::SceneNode* getCameraNode() const;

        Player* getPlayer() const;

        void update(MazeGame::Game& game);

        Ogre::Bullet::DynamicsWorld* getWorld();
    private:
        Ogre::Bullet::DynamicsWorld _world;

        Ogre::SceneNode* _cameraNode;
        Ogre::Camera* _camera;

        Ogre::Entity* _groundEntity;

        std::unique_ptr<Player> _player;

        std::vector<Battery> _batteries;
    };
}