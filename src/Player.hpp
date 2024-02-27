#pragma once

#include <Ogre.h>
#include <OgreBullet.h>

class Player
{
    public:
        Player(Ogre::Entity* entity, Ogre::SceneNode* parent, Ogre::Bullet::DynamicsWorld& physicWorld);
        ~Player();

        Ogre::Entity* getEntity();
        Ogre::SceneNode* getNode();
        btRigidBody* getBody();

    private:
        Ogre::Entity* _entity;
        Ogre::SceneNode* _node;
        btRigidBody* _body;
};