#pragma once

#include <Ogre.h>
#include <OgreBullet.h>

class Ship
{
    public:
        Ship(Ogre::Entity* entity, Ogre::SceneNode* parent, Ogre::Bullet::DynamicsWorld& physicWorld);
        ~Ship();
    private:
};