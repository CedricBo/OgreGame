#include "App.hpp"

#include <OgreRoot.h>
#include <iostream>

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
    auto cameraNode = _scene->getCameraNode();
    auto light = _scene->getTorchLight();
    auto world = _scene->getWorld();

    while(running)
    {
        running = root->renderOneFrame() && !_game.isEnded();

        _scene->getRootSceneNode()->needUpdate(true);

        auto quaternion =
            Ogre::Quaternion(Ogre::Degree(-_game.getAngleX()), Ogre::Vector3::UNIT_Y) *
            Ogre::Quaternion(Ogre::Degree(-_game.getAngleY()), Ogre::Vector3::UNIT_X);

        cameraNode->setOrientation(quaternion);

        auto& move = _game.move;

        cameraNode->translate({(float)move.left - move.right, 0, 0}, Ogre::Node::TS_LOCAL);
        cameraNode->translate({0, 0, (float)move.back - move.front}, Ogre::Node::TS_LOCAL);

        light->setSpotlightRange(Ogre::Degree(_game.size), Ogre::Degree(_game.size + 35));

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
