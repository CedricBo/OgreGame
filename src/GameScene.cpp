#include "GameScene.hpp"

#include <iostream>

using namespace MazeGame;


std::string const GameScene::typeName = "MazeScene";


GameScene::GameScene(std::string instanceName)
    : Ogre::SceneManager(instanceName)
{
    std::cout << "Create GameScene" << std::endl;

    setShadowTechnique(Ogre::ShadowTechnique::SHADOWTYPE_STENCIL_ADDITIVE);

    _cameraNode = getRootSceneNode()->createChildSceneNode("CameraNode");
    _torchLightNode = _cameraNode->createChildSceneNode("TorchLightNode");

    initTorchLight(_torchLightNode);
    initCamera(_cameraNode);

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

void MazeGame::GameScene::initTorchLight(Ogre::SceneNode* parent)
{
    _torchLight = createLight(Ogre::Light::LightTypes::LT_SPOTLIGHT);

    _torchLight->setSpecularColour(Ogre::ColourValue::Green);
    _torchLight->setAttenuation(25000, 0.9f, 0.05f, 0);

    parent->attachObject(_torchLight);
}

void MazeGame::GameScene::initCamera(Ogre::SceneNode* parent)
{
    _camera = createCamera("Camera");

    _camera->setNearClipDistance(5);
    _camera->setAutoAspectRatio(true);

    parent->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TransformSpace::TS_WORLD);
    parent->setPosition({100, 150, 200});
    parent->lookAt({0, 0, 0}, Ogre::Node::TS_WORLD);

    parent->attachObject(_camera);
}

Ogre::Camera *MazeGame::GameScene::getCamera() const
{
    return _camera;
}

Ogre::SceneNode *MazeGame::GameScene::getCameraNode() const
{
    return _cameraNode;
}

Ogre::Light *MazeGame::GameScene::getTorchLight() const
{
    return _torchLight;
}
