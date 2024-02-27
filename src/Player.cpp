#include "Player.hpp"

Player::Player(
    Ogre::Entity* entity,
    Ogre::SceneNode* parent,
    Ogre::Bullet::DynamicsWorld& physicWorld
)
    : _entity(entity),
    _node(parent)
{
    _entity->setMaterialName("SimpleBox");

    parent->attachObject(_entity);

    _body = physicWorld.addRigidBody(5, _entity, Ogre::Bullet::CT_BOX);

    _body->setAngularFactor({0, 0, 0});
    _body->setFriction(0);
}

Player::~Player()
{
}

Ogre::Entity* Player::getEntity()
{
    return _entity;
}

Ogre::SceneNode *Player::getNode()
{
    return _node;
}

btRigidBody *Player::getBody()
{
    return _body;
}
