#include "GameScene.hpp"

#include <iostream>
#include <random>

#include <btBulletDynamicsCommon.h>

using namespace MazeGame;


std::string const GameScene::typeName = "MazeScene";

GameScene::GameScene(std::string instanceName)
    : Ogre::SceneManager(instanceName),
    _world({0.0f, 0.0f, 0.0f})
{
    std::cout << "Create GameScene" << std::endl;

    setShadowTechnique(Ogre::ShadowTechnique::SHADOWTYPE_STENCIL_ADDITIVE);

    setAmbientLight(Ogre::ColourValue::White * 0.0f);
}

GameScene::~GameScene()
{
}

const std::string& GameScene::getTypeName() const
{
    return GameScene::typeName;
}

void MazeGame::GameScene::init()
{
    Ogre::SceneNode* root = getRootSceneNode();

    auto playerNode = root->createChildSceneNode("PlayerNode");
    _cameraNode = playerNode->createChildSceneNode("CameraNode");
    _torchLightNode = _cameraNode->createChildSceneNode("TorchLightNode");

    initTorchLight(_torchLightNode);
    initCamera(_cameraNode);
    initPlayer(playerNode);
    initGound(root);
    addFire(root);

    std::random_device rd{};
    std::mt19937 gen{rd()};

    std::uniform_real_distribution<float> angleDistribution{0, 360};
    std::uniform_real_distribution<float> distanceDistribution{100, 500};

    for(int i = 0; i < 50; i++)
    {
        float angleRad = Ogre::Degree(angleDistribution(gen)).valueRadians();
        float distance = distanceDistribution(gen);

        Ogre::Vector3f treePosition = { distance * std::sin(angleRad), 20, distance * std::cos(angleRad)};

        addTree(root, treePosition);
    }
}

void MazeGame::GameScene::initTorchLight(Ogre::SceneNode* parent)
{
    _torchLight = createLight(Ogre::Light::LightTypes::LT_SPOTLIGHT);

    _torchLight->setSpecularColour(Ogre::ColourValue::White);
    _torchLight->setDiffuseColour(Ogre::ColourValue::White);
    _torchLight->setAttenuation(25000, 0.05f, 0.042f, 0);

    auto _torchLightSubNode = parent->createChildSceneNode({10, 0, 0}, Ogre::Quaternion::IDENTITY);

    _torchLightSubNode->attachObject(_torchLight);
}

void MazeGame::GameScene::initCamera(Ogre::SceneNode* parent)
{
    _camera = createCamera("Camera");

    _camera->setNearClipDistance(5);
    _camera->setAutoAspectRatio(true);

    parent->setPosition({ 0, 250, 0});
    parent->lookAt({0, 0, 0}, Ogre::Node::TS_WORLD);

    parent->attachObject(_camera);
}

void MazeGame::GameScene::initPlayer(Ogre::SceneNode* parent)
{
    parent->setPosition({0, 100, 0});
    parent->scale({0.1f, 0.1f, 0.1f});

    _player = std::make_unique<Player>(
        createEntity("cube.mesh"),
        parent,
        _world
    );
}

void MazeGame::GameScene::initGound(Ogre::SceneNode* parent)
{
    Ogre::Plane ground{0, 0, 1, 1};

    auto groundMesh = Ogre::MeshManager::getSingleton().createPlane("Ground", Ogre::RGN_DEFAULT, ground, 1200, 1200);
    auto groundEntity = createEntity(groundMesh);
    groundEntity->setCastShadows(true);

    groundEntity->setMaterialName("SimpleGround");

    parent
        ->createChildSceneNode("Ground", {0, 0, 0}, Ogre::Quaternion(Ogre::Degree(90), Ogre::Vector3::NEGATIVE_UNIT_X))
        ->attachObject(groundEntity);

    _world.addRigidBody(0, groundEntity, Ogre::Bullet::CT_BOX);
}

Ogre::Camera* MazeGame::GameScene::getCamera() const
{
    return _camera;
}

Ogre::SceneNode* MazeGame::GameScene::getCameraNode() const
{
    return _cameraNode;
}

Player* MazeGame::GameScene::getPlayer() const
{
    return _player.get();
}

Ogre::Light* MazeGame::GameScene::getTorchLight() const
{
    return _fireLight;
}

void MazeGame::GameScene::update()
{

}

void MazeGame::GameScene::addFire(Ogre::SceneNode* parent)
{
    // _fire = createEntity("cube.mesh");

    // _fire->setMaterialName("SimpleBox");

    _fireNode = parent->createChildSceneNode({ 0, 20, 0}, Ogre::Quaternion::IDENTITY);

    // _fireNode->attachObject(_fire);

    _fireLight = createLight(Ogre::Light::LightTypes::LT_POINT);
    _fireLight->setSpecularColour(Ogre::ColourValue(1, 0.5f, 0));
    _fireLight->setDiffuseColour(Ogre::ColourValue(1, 0.5f, 0));
    _fireLight->setPowerScale(0.1f);
    _fireLight->setAttenuation(25000, 0.009f, 0.003f, 0);

    auto _fireLightNode = _fireNode->createChildSceneNode({ 0, 20, 0}, Ogre::Quaternion::IDENTITY);

    _fireLightNode->attachObject(_fireLight);
}

void MazeGame::GameScene::addTree(Ogre::SceneNode* parent, Ogre::Vector3f position)
{
    auto tree = createEntity("cube.mesh");
    auto treeNode = parent->createChildSceneNode(position, Ogre::Quaternion::IDENTITY);

    treeNode->attachObject(tree);
    treeNode->scale({ 0.1f, 1, 0.1f});

    _trees.emplace_back(tree, treeNode, _world);
}

Ogre::Bullet::DynamicsWorld* MazeGame::GameScene::getWorld()
{
    return &_world;
}
