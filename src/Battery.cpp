#include "Battery.hpp"

Battery::Battery(Ogre::Entity *entity, Ogre::SceneNode *parent, Ogre::Bullet::DynamicsWorld &physicWorld)
    : _entityMembers({ entity, parent, nullptr })
{
    entity->setMaterialName("SimpleBox");

    parent->attachObject(entity);

    _entityMembers.body = physicWorld.addRigidBody(5, entity, Ogre::Bullet::CT_CYLINDER);

    applyGravitySettings();
}

Ogre::Entity* Battery::getEntity() const
{
    return _entityMembers.entity;
}

Ogre::SceneNode *Battery::getNode() const
{
    return _entityMembers.node;
}

btRigidBody *Battery::getBody() const
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

void Battery::applyGravitySettings()
{
    _entityMembers.body->setAngularFactor(1);
    _entityMembers.body->setGravity({0, 0, -9.81f});

    _entityMembers.body->setCollisionFlags(_entityMembers.body->getCollisionFlags() & ~btCollisionObject::CF_NO_CONTACT_RESPONSE);
}
