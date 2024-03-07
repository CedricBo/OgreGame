#include "GameScene.hpp"

#include <iostream>
#include <random>
#include <btBulletDynamicsCommon.h>

#include "PlayerRayResultCallback.hpp"

using namespace MazeGame;

std::string const GameScene::typeName = "MazeScene";

GameScene::GameScene(std::string instanceName)
    : Ogre::SceneManager(instanceName),
    _world({0.0f, 0.0f, 0.0f})
{
    std::cout << "Create GameScene" << std::endl;

    setShadowTechnique(Ogre::ShadowTechnique::SHADOWTYPE_STENCIL_ADDITIVE);

    setAmbientLight(Ogre::ColourValue::White * 0.5f);
}

GameScene::~GameScene()
{
}

const std::string& GameScene::getTypeName() const
{
    return GameScene::typeName;
}

void GameScene::init()
{
    Ogre::SceneNode* root = getRootSceneNode();

    auto playerNode = root->createChildSceneNode("PlayerNode");
    initPlayer(playerNode);

    // _cameraNode = playerNode->createChildSceneNode("CameraNode");
    initCamera(playerNode);

    initGound(root);
    addBattery(root, {200, 200, 0});
    addBattery(root, {250, 200, 0});
    addBattery(root, {300, 200, 0});
}

void GameScene::initCamera(Ogre::SceneNode* parent)
{
    _camera = createCamera("Camera");

    _camera->setNearClipDistance(5);
    _camera->setAutoAspectRatio(true);

    parent->setPosition({ 0, 100, 0});

    parent->attachObject(_camera);
}

void GameScene::initPlayer(Ogre::SceneNode* parent)
{
    parent->setPosition({0, 300, 0});
    parent->setScale({0.1f, 1, 0.1f});

    _player = std::make_unique<Player>(
        createEntity("cube.mesh"),
        parent,
        _world
    );
}

void GameScene::initGound(Ogre::SceneNode* parent)
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

void MazeGame::GameScene::addBattery(Ogre::SceneNode *parent, Ogre::Vector3f position)
{
    auto& battery = _batteries.emplace_back(
        createEntity("cube.mesh"),
        parent->createChildSceneNode(position, Ogre::Quaternion::IDENTITY),
        _world
    );
}

Ogre::Camera* GameScene::getCamera() const
{
    return _camera;
}

Ogre::SceneNode* GameScene::getCameraNode() const
{
    return _cameraNode;
}

Player* GameScene::getPlayer() const
{
    return _player.get();
}

void GameScene::update(MazeGame::Game& game)
{
    auto* playerBody = _player->getBody();
    auto& [viewAngleX, viewAngleY] = game.getViewAngle();

    if(!playerBody->isActive())
    {
        playerBody->activate();
    }

    auto playerBodyQuaternion = Ogre::Quaternion(Ogre::Degree(viewAngleX), -Ogre::Vector3::UNIT_Y);
    auto playerNodeQuaternion = Ogre::Quaternion(Ogre::Degree(viewAngleY), -Ogre::Vector3::UNIT_X);

    playerBody->getWorldTransform().setRotation(Ogre::Bullet::convert(playerBodyQuaternion));
    // _cameraNode->setOrientation(playerNodeQuaternion);
    _player->getNode()->setOrientation(playerNodeQuaternion);

    auto& move = game.move;

    if(move.back || move.front || move.left || move.right)
    {
        auto moveVector = Ogre::Vector3f((float)move.left - move.right, 0, (float)move.back - move.front).normalisedCopy() * 10;
        auto radRy = -_player->getNode()->getOrientation().getYaw().valueRadians();

        auto rotatedMoveVector = Ogre::Vector3f{
            std::cos(radRy) * moveVector.x - std::sin(radRy) * moveVector.z,
            0,
            std::sin(radRy) * moveVector.x + std::cos(radRy) * moveVector.z
        };

        playerBody->applyCentralForce(Ogre::Bullet::convert(rotatedMoveVector) * 100);
    }

    PlayerRayResultCallback p{};

    std::cout << _player->getNode()->getPosition() << std::endl;

    Ogre::Ray ray{_player->getNode()->getPosition(), {0, -1, 0}};
    _world.rayTest(ray, &p, 100);

    // Player Max Speed
    auto playerLinearVelocity = playerBody->getLinearVelocity();
    auto speed = std::clamp((double)playerLinearVelocity.norm(), 0.0, 30.0);

    playerLinearVelocity.safeNormalize();
    playerLinearVelocity *= speed;
    playerBody->setLinearVelocity(playerLinearVelocity);
}

Ogre::Bullet::DynamicsWorld* GameScene::getWorld()
{
    return &_world;
}
