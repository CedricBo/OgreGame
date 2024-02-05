#include "App.hpp"

#include <OgreRoot.h>
#include <iostream>

using namespace MazeGame;

App::App()
    : _context("MazeGame"),
    _game(),
    _inputListener(_game),
    _gameSceneManagerFactory(),
    _world({0.0f, -9.0f, 0.0f})
{
    _context.initApp();
    _context.addInputListener(&_inputListener);

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
