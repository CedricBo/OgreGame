#include "Tree.hpp"

Tree::Tree(
    Ogre::Entity *entity,
    Ogre::SceneNode *parent,
    Ogre::Bullet::DynamicsWorld &physicWorld
)
    : _entity(entity),
    _node(parent)
{
    _entity->setMaterialName("SimpleBox");

    _body = physicWorld.addRigidBody(0, _entity, Ogre::Bullet::CT_BOX);
}

Tree::~Tree()
{
}
