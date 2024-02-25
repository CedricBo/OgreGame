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

        void init();

        void initTorchLight(Ogre::SceneNode* parent);
        void initCamera(Ogre::SceneNode* parent);
        void initPlayer(Ogre::SceneNode* parent);

        void initMap(Ogre::SceneNode* parent);
        void initGound(Ogre::SceneNode* parent);

        void addFire(Ogre::SceneNode* parent);
        void addTree(Ogre::SceneNode* parent, float angle, float distance);

        Ogre::Camera* getCamera() const;

        Ogre::SceneNode* getCameraNode() const;
        Ogre::SceneNode* getPlayerNode() const;
        btRigidBody* getPlayerBody() const;
        Ogre::Light* getTorchLight() const;

        void update();

        Ogre::Bullet::DynamicsWorld* getWorld();

        Ogre::SceneNode* createSceneNodeImpl() override;
        Ogre::SceneNode* createSceneNodeImpl(const std::string& name) override;
    private:
        Ogre::Bullet::DynamicsWorld _world;

        Ogre::SceneNode* _cameraNode;
        Ogre::Camera* _camera;

        Ogre::SceneNode* _playerNode;
        Ogre::Entity* _player;
        btRigidBody* _playerBody;

        Ogre::SceneNode* _torchLightNode;
        Ogre::Light* _torchLight;

        Ogre::Entity* _fire;
        Ogre::Light* _fireLight;
        Ogre::SceneNode* _fireNode;

        std::vector<Ogre::Entity*> _trees;
        std::vector<Ogre::SceneNode*> _treeNodes;
    };
}