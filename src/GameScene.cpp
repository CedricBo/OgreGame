#include "GameScene.hpp"

#include <iostream>
#include <random>

using namespace MazeGame;


std::string const GameScene::typeName = "MazeScene";


GameScene::GameScene(std::string instanceName)
    : Ogre::SceneManager(instanceName),
    _world({0.0f, -9.0f, 0.0f})
{
    std::cout << "Create GameScene" << std::endl;

    setShadowTechnique(Ogre::ShadowTechnique::SHADOWTYPE_STENCIL_ADDITIVE);

    setAmbientLight(Ogre::ColourValue::White * 0.1f);

    _cameraNode = getRootSceneNode()->createChildSceneNode("CameraNode");
    _torchLightNode = _cameraNode->createChildSceneNode("TorchLightNode");

    initTorchLight(_torchLightNode);
    initCamera(_cameraNode);
    // initMap();
    initGound();
    addFire();

    std::random_device rd{};
    std::mt19937 gen{rd()};

    std::uniform_real_distribution<float> angleDistribution{0, 360};
    std::uniform_real_distribution<float> distanceDistribution{100, 500};

    for(int i = 0; i < 50; i++)
    {
        float angle = angleDistribution(gen);
        float distance = distanceDistribution(gen);

        addTree(angle, distance);
    }
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
    _torchLight->setAttenuation(25000, 0.09f, 0.03f, 0);

    auto _torchLightSubNode = parent->createChildSceneNode({10, 0, 0}, Ogre::Quaternion::IDENTITY);

    _torchLightSubNode->attachObject(_torchLight);
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
    groundEntity->setCastShadows(true);

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
    return _fireLight;
}

void MazeGame::GameScene::update()
{

}

void MazeGame::GameScene::addFire()
{
    // _fire = createEntity("cube.mesh");

    // _fire->setMaterialName("SimpleBox");

    _fireNode = getRootSceneNode()->createChildSceneNode({ 0, 20, 0}, Ogre::Quaternion::IDENTITY);

    // _fireNode->attachObject(_fire);

    _fireLight = createLight(Ogre::Light::LightTypes::LT_POINT);
    _fireLight->setSpecularColour(Ogre::ColourValue::Red);
    _fireLight->setDiffuseColour(Ogre::ColourValue::Red);
    _fireLight->setPowerScale(0.1f);
    _fireLight->setAttenuation(25000, 0.009f, 0.003f, 0);

    auto _fireLightNode = _fireNode->createChildSceneNode({ 0, 20, 0}, Ogre::Quaternion::IDENTITY);

    _fireLightNode->attachObject(_fireLight);

}

void MazeGame::GameScene::addTree(float angle, float distance)
{
    auto tree = createEntity("cube.mesh");

    _trees.push_back(tree);

    tree->setMaterialName("SimpleBox");

    float angleRad = Ogre::Math::DegreesToRadians(angle);

    auto treeNode = getRootSceneNode()->createChildSceneNode({ distance * std::sin(angleRad), 20, distance * std::cos(angleRad)}, Ogre::Quaternion::IDENTITY);
    treeNode->attachObject(tree);
    treeNode->scale({ 0.1f, 1, 0.1f});

    _treeNodes.push_back(treeNode);
}

Ogre::Bullet::DynamicsWorld* MazeGame::GameScene::getWorld()
{
    return &_world;
}
