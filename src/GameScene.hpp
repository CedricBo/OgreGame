#pragma once

#include <OgreSceneManager.h>
#include <Bullet/OgreBullet.h>

#include "Game.hpp"
#include "Player.hpp"
#include "Battery.hpp"
#include "PlayerSceneNode.hpp"

namespace MazeGame
{
    class GameScene : public Ogre::SceneManager
    {
    public:
        static const std::string typeName;

        GameScene(std::string instanceName, Game& game);
        ~GameScene();

        const std::string& getTypeName() const;

        void init();

        void createSceneCamera(Ogre::SceneNode* parent);
        void createPlayer(Ogre::SceneNode* parent);
        void createGound(Ogre::SceneNode* parent);

        void addBattery(Ogre::SceneNode* parent, Ogre::Vector3f position);

        Ogre::Camera* getCamera() const;

        Ogre::SceneNode* getCameraNode() const;

        void update();

        Ogre::Bullet::DynamicsWorld *getWorld();

    private:
        Ogre::Bullet::DynamicsWorld _world;

        Ogre::SceneNode* _cameraNode;
        Ogre::Camera* _camera;

        Ogre::Entity* _groundEntity;

        // std::unique_ptr<Player> _player;
        std::unique_ptr<PlayerSceneNode> _playerSceneNode;

        std::vector<Battery> _batteries;

        Game& _game;
    };
}