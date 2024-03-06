#pragma once

#include <Ogre.h>
#include <OgreBullet.h>

class Battery
{
    public:
        Battery(Ogre::Entity* entity, Ogre::SceneNode* parent, Ogre::Bullet::DynamicsWorld& physicWorld);
        ~Battery();

        Ogre::Entity* getEntity();
        Ogre::SceneNode* getNode();
        btRigidBody* getBody();

        const int getCapacity();
        const int getLevel();

        bool isEmpty();
        bool isFull();


    private:
        Ogre::Entity* _entity;
        Ogre::SceneNode* _node;
        btRigidBody* _body;

        int _capacity;
        int _level;
};