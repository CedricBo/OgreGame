#include "GameScene.hpp"

#include <iostream>
#include <random>
#include <btBulletDynamicsCommon.h>

#include "PlayerRayResultCallback.hpp"

using namespace MazeGame;

std::string const GameScene::typeName = "MazeScene";

GameScene::GameScene(std::string instanceName, Game& game)
    : Ogre::SceneManager(instanceName),
    _world({0.0f, 0.0f, 0.0f}),
    _game(game)
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
    createPlayer(playerNode);

    _cameraNode = playerNode->createChildSceneNode("CameraNode");
    createSceneCamera(_cameraNode);

    createGound(root);
    addBattery(root, {200, 0, 100});
    addBattery(root, {250, 0, 100});
    addBattery(root, {300, 0, 100});
}

void GameScene::createSceneCamera(Ogre::SceneNode* parent)
{
    _camera = createCamera("Camera");

    _camera->setNearClipDistance(5);
    _camera->setAutoAspectRatio(true);

    parent->setPosition({0, 55, 0});

    parent->attachObject(_camera);
}

void GameScene::createPlayer(Ogre::SceneNode* parent)
{
    parent->setPosition({0, 0, 110});
    parent->setScale({0.1f, 0.1f, 1});

    _playerSceneNode = std::make_unique<PlayerSceneNode>(
        _game.getPlayer(),
        createEntity("cube.mesh"),
        parent,
        _world
    );
}

void GameScene::createGound(Ogre::SceneNode* parent)
{
    Ogre::Plane ground{0, 0, 1, 0};

    auto groundMesh = Ogre::MeshManager::getSingleton().createPlane("Ground", Ogre::RGN_DEFAULT, ground, 1200, 1200);
    _groundEntity = createEntity(groundMesh);
    _groundEntity->setCastShadows(true);

    _groundEntity->setMaterialName("SimpleGround");

    parent
        ->createChildSceneNode("Ground", {0, 0, 0}, Ogre::Quaternion(Ogre::Degree(0), Ogre::Vector3::NEGATIVE_UNIT_X))
        ->attachObject(_groundEntity);

    _world.addRigidBody(0, _groundEntity, Ogre::Bullet::CT_BOX);
}

void MazeGame::GameScene::addBattery(Ogre::SceneNode *parent, Ogre::Vector3f position)
{
    static int counter = 0;

    auto& battery = _batteries.emplace_back(
        createEntity("Battery.mesh"),
        parent->createChildSceneNode("Battery" + std::to_string(counter++), position, Ogre::Quaternion::IDENTITY),
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

void GameScene::update()
{
    auto* playerBody = _playerSceneNode->getBody();
    auto& player = _game.getPlayer();
    auto& [viewAngleX, viewAngleY] = _game.getViewAngle();

    if(!playerBody->isActive())
    {
        playerBody->activate();
    }

    auto playerBodyQuaternion = Ogre::Quaternion(Ogre::Degree(viewAngleX), -Ogre::Vector3::UNIT_Z);
    auto playerNodeQuaternion = Ogre::Quaternion(Ogre::Degree(viewAngleY), -Ogre::Vector3::UNIT_X);

    playerBody->getWorldTransform().setRotation(Ogre::Bullet::convert(playerBodyQuaternion));
    _cameraNode->setOrientation(playerNodeQuaternion);

    auto& move = _game.move;

    if(move.back || move.front || move.left || move.right)
    {
        auto moveVector = Ogre::Vector3f((float)move.left - move.right, (float)move.back - move.front, 0).normalisedCopy() * 10;
        auto radRy = _playerSceneNode->getNode()->getOrientation().getRoll().valueRadians();

        auto rotatedMoveVector = Ogre::Vector3f{
            std::cos(radRy) * moveVector.x + std::sin(radRy) * moveVector.y,
            std::sin(radRy) * moveVector.x - std::cos(radRy) * moveVector.y,
            0
        };

        playerBody->applyCentralForce(Ogre::Bullet::convert(rotatedMoveVector) * 100);
    }

    auto rayStartPos = _cameraNode->convertLocalToWorldPosition({0, 0, 0});
    auto direction = _camera->getRealDirection();
    Ogre::Ray ray{rayStartPos, direction};

    auto grabbed = player.getGrabbedBattery();
    bool isGrabbed = grabbed != nullptr; 

    if(!isGrabbed)
    {
        PlayerRayResultCallback p{_batteries};

        _world.rayTest(ray, &p, 500);

        auto nearestBattery = p.getNearestResult();

        player.setLookedBattery(nearestBattery);
    }
    else
    {
        auto point = ray.getPoint(50);

        grabbed->getBody()->getWorldTransform().setOrigin(Ogre::Bullet::convert(point));
        grabbed->getBody()->setGravity({0, 0, 0});
        grabbed->getBody()->setAngularFactor(0);
        grabbed->getBody()->activate(true);
    }

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
