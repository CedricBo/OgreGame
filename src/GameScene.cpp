#include "GameScene.hpp"

#include <iostream>

using namespace MazeGame;


std::string const GameScene::typeName = "MazeScene";


GameScene::GameScene(std::string instanceName)
    : Ogre::SceneManager(instanceName)
{
    std::cout << "Create GameScene" << std::endl;

    setShadowTechnique(Ogre::ShadowTechnique::SHADOWTYPE_STENCIL_ADDITIVE);

    initTorchLight();
    initCamera();

    auto cameraNode = createSceneNode("CameraNode");
    auto lightNode = cameraNode->createChildSceneNode("TorchLight", {5.0, 0.0, 0.0});

    cameraNode->attachObject(_camera);
    lightNode->attachObject(_torchLight);

    // Add second fix light
    auto light2 = createLight(Ogre::Light::LightTypes::LT_SPOTLIGHT);
    auto light2Node = getRootSceneNode()->createChildSceneNode({ -149.8, 157.86, 69.1937 }, Ogre::Quaternion(Ogre::Degree(-90), Ogre::Vector3::UNIT_Y));

    light2->setSpecularColour(Ogre::ColourValue::Red);
    light2Node->attachObject(light2);
}

GameScene::~GameScene()
{
}

const std::string& GameScene::getTypeName() const
{
    return GameScene::typeName;
}

void MazeGame::GameScene::initTorchLight()
{
    _torchLight = createLight(Ogre::Light::LightTypes::LT_SPOTLIGHT);

    _torchLight->setSpecularColour(Ogre::ColourValue::Green);
    _torchLight->setAttenuation(25000, 0.9f, 0.05f, 0);
}

void MazeGame::GameScene::initCamera()
{
    _camera = createCamera("Camera");

    _camera->setNearClipDistance(5);
}
