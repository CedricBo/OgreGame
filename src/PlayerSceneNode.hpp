#pragma once

#include <Ogre.h>
#include <OgreBullet.h>

#include "Player.hpp"

class PlayerSceneNode
{
public:
    PlayerSceneNode(Player& player, Ogre::Entity* entity, Ogre::SceneNode* parent, Ogre::Bullet::DynamicsWorld& physicWorld);
    ~PlayerSceneNode();

    Player* getPlayer();

    Ogre::Entity* getEntity();
    Ogre::SceneNode* getNode();
    btRigidBody* getBody();
private:
    Player& _player;

    Ogre::Entity* _entity;
    Ogre::SceneNode* _node;
    btRigidBody* _body;
};