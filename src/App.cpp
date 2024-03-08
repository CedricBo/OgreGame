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
    auto world = _scene->getWorld();

    while(running)
    {
        running = root->renderOneFrame() && !_game.isEnded();

        _scene->getRootSceneNode()->needUpdate(true);

        _scene->update(_game);

        _context.pollEvents();

        world->getBtWorld()->stepSimulation(0.16f);
    }
}

void MazeGame::App::initRTSShaderGenerator()
{
    Ogre::RTShader::ShaderGenerator::initialize();

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
