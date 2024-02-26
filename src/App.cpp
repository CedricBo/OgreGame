#include "App.hpp"

#include <OgreRoot.h>
#include <iostream>
#include <random>

using namespace MazeGame;

App::App()
    : _context("MazeGame"),
    _game(),
    _inputListener(_game),
    _gameSceneManagerFactory()
{
    _context.initApp();
    _context.addInputListener(&_inputListener);

    _context.setWindowGrab();

    auto root = _context.getRoot();

    root->addSceneManagerFactory(&_gameSceneManagerFactory);

    _scene = static_cast<MazeGame::GameScene*>(root->createSceneManager(MazeGame::GameScene::typeName));

    _scene->init();

    initRTSShaderGenerator();
    initViewPort(_scene->getCamera());
}

App::~App()
{

}

GameScene *App::getScene() const
{
    return _scene;
}

void MazeGame::App::initViewPort(Ogre::Camera* camera)
{
    _viewport = _context.getRenderWindow()->addViewport(camera);

    _viewport->setBackgroundColour(Ogre::ColourValue(0,0,0));

    _viewport->setMaterialScheme(Ogre::RTShader::ShaderGenerator::DEFAULT_SCHEME_NAME);
}

void MazeGame::App::run()
{
    bool running = true;
    auto root = _context.getRoot();
    auto playerNode = _scene->getPlayerNode();
    auto playerBody = _scene->getPlayerBody();
    auto cameraNode = _scene->getCameraNode();
    auto light = _scene->getTorchLight();
    auto world = _scene->getWorld();

    float lightPowerScale = 0.2f;

    std::random_device rd{};
    std::mt19937 gen{rd()};

    std::uniform_real_distribution<float> dist{-0.008f, 0.008f};

    while(running)
    {
        running = root->renderOneFrame() && !_game.isEnded();

        _scene->getRootSceneNode()->needUpdate(true);

        auto playerBodyQuaternion = Ogre::Quaternion(Ogre::Degree(-_game.getAngleX()), Ogre::Vector3::UNIT_Y);
        auto playerNodeQuaternion = Ogre::Quaternion(Ogre::Degree(-_game.getAngleY()), Ogre::Vector3::UNIT_X);

        // playerNode->setOrientation(quaternion);
        playerBody->getWorldTransform().setRotation(Ogre::Bullet::convert(playerBodyQuaternion));
        cameraNode->setOrientation(playerNodeQuaternion);

        auto& move = _game.move;

        if(move.back || move.front || move.left || move.right)
        {
            auto moveVector = Ogre::Vector3f((float)move.left - move.right, 0, (float)move.back - move.front).normalisedCopy() * 10;
            auto radRy = -playerNode->getOrientation().getYaw().valueRadians();

            auto rotatedMoveVector = Ogre::Vector3f{
                std::cos(radRy) * moveVector.x - std::sin(radRy) * moveVector.z,
                0,
                std::sin(radRy) * moveVector.x + std::cos(radRy) * moveVector.z
            };

            playerBody->applyCentralForce(Ogre::Bullet::convert(rotatedMoveVector) * 30);
        }

        lightPowerScale = std::clamp(lightPowerScale + dist(gen), 0.02f, 0.2f);

        if(_game.isLightOn())
        {
            light->setPowerScale(lightPowerScale);
        }
        else
        {
            light->setPowerScale(0);
        }

        _context.pollEvents();

        world->getBtWorld()->stepSimulation(1);
    }

    _scene->update();
}

void MazeGame::App::initRTSShaderGenerator()
{
    auto shaderGenerator = Ogre::RTShader::ShaderGenerator::getSingletonPtr();

    shaderGenerator->addSceneManager(_scene);
}

OgreBites::ApplicationContext& MazeGame::App::getContext()
{
    return _context;
}

MazeGame::Game& App::getGame()
{
    return _game;
}
