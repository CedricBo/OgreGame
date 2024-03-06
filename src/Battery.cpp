#include "Battery.hpp"

Battery::Battery(Ogre::Entity *entity, Ogre::SceneNode *parent, Ogre::Bullet::DynamicsWorld &physicWorld)
{
}

Battery::~Battery()
{
}

Ogre::Entity* Battery::getEntity()
{
    return _entity;
}

Ogre::SceneNode *Battery::getNode()
{
    return _node;
}

btRigidBody *Battery::getBody()
{
    return _body;
}
