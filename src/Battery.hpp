#pragma once

#include <Ogre.h>
#include <OgreBullet.h>

#include "EntityMembers.hpp"

class Battery
{
    public:
        Battery(Ogre::Entity* entity, Ogre::SceneNode* parent, Ogre::Bullet::DynamicsWorld& physicWorld);

        Ogre::Entity* getEntity() const;
        Ogre::SceneNode* getNode() const;
        btRigidBody* getBody() const;

        const int getCapacity();
        const int getLevel();

        bool isEmpty();
        bool isFull();
    private:
        EntityMembers _entityMembers { nullptr, nullptr, nullptr };

        int _capacity{0};
        int _level{0};
};