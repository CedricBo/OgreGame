#pragma once

#include <Ogre.h>
#include <OgreBullet.h>

class Tree
{
    public:
        Tree(Ogre::Entity* entity, Ogre::SceneNode* parent, Ogre::Bullet::DynamicsWorld& physicWorld);
        ~Tree();

    private:
        Ogre::Entity* _entity;
        Ogre::SceneNode* _node;
        btRigidBody* _body;
};