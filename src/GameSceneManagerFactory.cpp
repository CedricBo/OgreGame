#include "GameSceneManagerFactory.hpp"

#include <OgreSceneManager.h>

#include <iostream>

using namespace Game;

std::string GameScene::typeName = "MazeScene";

GameSceneManagerFactory::GameSceneManagerFactory()
{
}

GameSceneManagerFactory::~GameSceneManagerFactory()
{
}

const std::string& GameSceneManagerFactory::getTypeName(void) const
{
    return GameScene::typeName;
}

Ogre::SceneManager* GameSceneManagerFactory::createInstance(const std::string &instanceName)
{
    return new GameScene(instanceName);
}

GameScene::GameScene(std::string instanceName)
    : Ogre::SceneManager(instanceName)
{
    std::cout << "Create GameScene" << std::endl;
}

GameScene::~GameScene()
{
}

const std::string& GameScene::getTypeName(void) const
{
    return GameScene::typeName;
}
