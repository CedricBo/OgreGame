#include "GameSceneManagerFactory.hpp"

#include <iostream>

#include <OgreSceneManager.h>

#include "GameScene.hpp"

using namespace MazeGame;

GameSceneManagerFactory::GameSceneManagerFactory()
{
}

GameSceneManagerFactory::~GameSceneManagerFactory()
{
}

const std::string& GameSceneManagerFactory::getTypeName() const
{
    return GameScene::typeName;
}

Ogre::SceneManager* GameSceneManagerFactory::createInstance(const std::string &instanceName)
{
    return new GameScene(instanceName);
}