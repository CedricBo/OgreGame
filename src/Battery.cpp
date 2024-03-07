#include "Battery.hpp"

Battery::Battery(Ogre::Entity *entity, Ogre::SceneNode *parent, Ogre::Bullet::DynamicsWorld &physicWorld)
    : _entityMembers({ entity, parent, nullptr })
{
    entity->setMaterialName("SimpleBox");

    parent->attachObject(entity);

    parent->scale(0.1f, 0.1f, 0.1f);

    _entityMembers.body = physicWorld.addRigidBody(5, entity, Ogre::Bullet::CT_BOX);

    _entityMembers.body->setGravity({0, -9.0f, 0});
}

Ogre::Entity* Battery::getEntity()
{
    return _entityMembers.entity;
}

Ogre::SceneNode *Battery::getNode()
{
    return _entityMembers.node;
}

btRigidBody *Battery::getBody()
{
    return _entityMembers.body;
}

const int Battery::getCapacity()
{
    return _capacity;
}

const int Battery::getLevel()
{
    return _level;
}

bool Battery::isEmpty()
{
    return _level == 0;
}

bool Battery::isFull()
{
    return _level == _capacity;
}
