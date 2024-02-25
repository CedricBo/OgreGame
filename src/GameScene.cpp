#include "GameScene.hpp"

#include <iostream>
#include <random>

using namespace MazeGame;


std::string const GameScene::typeName = "MazeScene";

Ogre::SceneNode* GameScene::createSceneNodeImpl(void)
{
    return new Ogre::SceneNode(this);
}

Ogre::SceneNode* GameScene::createSceneNodeImpl(const std::string& name)
{
    return new Ogre::SceneNode(this);
}


GameScene::GameScene(std::string instanceName)
    : Ogre::SceneManager(instanceName),
    _world({0.0f, -9.0f, 0.0f})
{
    std::cout << "Create GameScene" << std::endl;

    setShadowTechnique(Ogre::ShadowTechnique::SHADOWTYPE_STENCIL_ADDITIVE);

    setAmbientLight(Ogre::ColourValue::White * 0.1f);
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
    // auto* root = createSceneNode("Root");
    Ogre::SceneNode* root = getRootSceneNode();

    auto name = getRootSceneNode()->getName();

    _playerNode = root->createChildSceneNode("PlayerNode");
    _cameraNode = _playerNode->createChildSceneNode("CameraNode");
    _torchLightNode = _cameraNode->createChildSceneNode("TorchLightNode");

    initTorchLight(_torchLightNode);
    initCamera(_cameraNode);
    initPlayer(_playerNode);
    // initMap();
    initGound(getRootSceneNode());
    addFire(getRootSceneNode());

    std::random_device rd{};
    std::mt19937 gen{rd()};

    std::uniform_real_distribution<float> angleDistribution{0, 360};
    std::uniform_real_distribution<float> distanceDistribution{100, 500};

    for(int i = 0; i < 50; i++)
    {
        float angle = angleDistribution(gen);
        float distance = distanceDistribution(gen);

        addTree(root, angle, distance);
    }
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

    parent->setPosition({ 0, 400, 400});
    parent->lookAt({0, 0, 0}, Ogre::Node::TS_WORLD);

    parent->attachObject(_camera);
}

void MazeGame::GameScene::initPlayer(Ogre::SceneNode* parent)
{
    _player = createEntity("cube.mesh");

    _player->setMaterialName("SimpleBox");

    parent->attachObject(_player);
    parent->setPosition({0, 200, 0});

    parent->scale({0.1f, 0.1f, 0.1f});

    _playerBody = _world.addRigidBody(5, _player, Ogre::Bullet::CT_BOX);

    _playerBody->setAngularFactor({0, 0, 0});

    _playerBody->setFriction(0);
}

void MazeGame::GameScene::initMap(Ogre::SceneNode* parent)
{
    for(int i = 1; i <= 10; i++)
    {
        auto entity = createEntity("cube.mesh");

        entity->setMaterialName("SimpleBox");

        auto meshNode = parent->createChildSceneNode("EntityNode" + std::to_string(i), {60.0f * i, 130.0f * i, 0});
        meshNode->attachObject(entity);

        meshNode->scale(1, (0.1f * i), 1);

        auto body = _world.addRigidBody(5, entity, Ogre::Bullet::CT_BOX);

        // body->setLinearVelocity({0, 40, 0});
    }
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

Ogre::Camera *MazeGame::GameScene::getCamera() const
{
    return _camera;
}

Ogre::SceneNode *MazeGame::GameScene::getCameraNode() const
{
    return _cameraNode;
}

Ogre::SceneNode *MazeGame::GameScene::getPlayerNode() const
{
    return _playerNode;
}

btRigidBody *MazeGame::GameScene::getPlayerBody() const
{
    return _playerBody;
}

Ogre::Light *MazeGame::GameScene::getTorchLight() const
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
    _fireLight->setSpecularColour(Ogre::ColourValue::Red);
    _fireLight->setDiffuseColour(Ogre::ColourValue::Red);
    _fireLight->setPowerScale(0.1f);
    _fireLight->setAttenuation(25000, 0.009f, 0.003f, 0);

    auto _fireLightNode = _fireNode->createChildSceneNode({ 0, 20, 0}, Ogre::Quaternion::IDENTITY);

    _fireLightNode->attachObject(_fireLight);
}

void MazeGame::GameScene::addTree(Ogre::SceneNode* parent, float angle, float distance)
{
    auto tree = createEntity("cube.mesh");

    _trees.push_back(tree);

    tree->setMaterialName("SimpleBox");

    float angleRad = Ogre::Math::DegreesToRadians(angle);

    auto treeNode = parent->createChildSceneNode({ distance * std::sin(angleRad), 20, distance * std::cos(angleRad)}, Ogre::Quaternion::IDENTITY);
    treeNode->attachObject(tree);
    treeNode->scale({ 0.1f, 1, 0.1f});

    _world.addRigidBody(0, tree, Ogre::Bullet::CT_BOX);

    _treeNodes.push_back(treeNode);
}

Ogre::Bullet::DynamicsWorld* MazeGame::GameScene::getWorld()
{
    return &_world;
}
