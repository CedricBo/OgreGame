#include "GameScene.hpp"

#include <iostream>

using namespace MazeGame;


std::string const GameScene::typeName = "MazeScene";


GameScene::GameScene(std::string instanceName)
    : Ogre::SceneManager(instanceName),
    _world({0.0f, -9.0f, 0.0f})
{
    std::cout << "Create GameScene" << std::endl;

    setShadowTechnique(Ogre::ShadowTechnique::SHADOWTYPE_STENCIL_ADDITIVE);

    setAmbientLight(Ogre::ColourValue::White * 0.5f);

    _cameraNode = getRootSceneNode()->createChildSceneNode("CameraNode");
    _torchLightNode = _cameraNode->createChildSceneNode("TorchLightNode");

    initTorchLight(_torchLightNode);
    initCamera(_cameraNode);
    initMap();
    initGound();

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

    _torchLight->setSpecularColour(Ogre::ColourValue::White);
    _torchLight->setAttenuation(25000, 0.9f, 0.03f, 0);

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

void MazeGame::GameScene::initMap()
{
    auto rootNode = getRootSceneNode();

    for(int i = 1; i <= 10; i++)
    {
        auto entity = createEntity("cube.mesh");

        entity->setMaterialName("SimpleBox");

        auto meshNode = rootNode->createChildSceneNode("EntityNode" + std::to_string(i), {60.0f * i, 130.0f * i, 0});
        meshNode->attachObject(entity);

        meshNode->scale(1, (0.1f * i), 1);

        auto body = _world.addRigidBody(5, entity, Ogre::Bullet::CT_BOX);

        // body->setLinearVelocity({0, 40, 0});
    }
}

void MazeGame::GameScene::initGound()
{
    auto rootNode = getRootSceneNode();

    Ogre::Plane ground{0, 0, 1, 1};

    auto groundMesh = Ogre::MeshManager::getSingleton().createPlane("Ground", Ogre::RGN_DEFAULT, ground, 1200, 1200);
    auto groundEntity = createEntity(groundMesh);

    groundEntity->setMaterialName("SimpleGround");

    rootNode
        ->createChildSceneNode("Ground", {0, 0, 0}, Ogre::Quaternion(Ogre::Degree(90), Ogre::Vector3::NEGATIVE_UNIT_X))
        ->attachObject(groundEntity);

    _world.addRigidBody(0, groundEntity, Ogre::Bullet::CT_BOX);
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

void MazeGame::GameScene::update()
{

}

Ogre::Bullet::DynamicsWorld* MazeGame::GameScene::getWorld()
{
    return &_world;
}