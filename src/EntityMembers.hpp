#pragma once

#include <Ogre.h>
#include <OgreBullet.h>

struct EntityMembers
{
    Ogre::Entity* entity;
    Ogre::SceneNode* node;
    btRigidBody* body;
};
