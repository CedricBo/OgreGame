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
}

App::~App()
{

}

GameScene *App::getScene() const
{
    return _scene;
}

void MazeGame::App::initRTSShaderGenerator()
{
    auto shaderGenerator = Ogre::RTShader::ShaderGenerator::getSingletonPtr();

    shaderGenerator->addSceneManager(_scene);
}

void MazeGame::App::initTorchLight()
{
    auto light = _scene->createLight(Ogre::Light::LightTypes::LT_SPOTLIGHT);

    light->setSpecularColour(Ogre::ColourValue::Green);
    light->setAttenuation(25000, 0.9f, 0.05f, 0);
}

// void App::setup()
// {
//     std::cout << "App Setup" << std::endl;

//     // auto root = getRoot();

//     // root->addSceneManagerFactory(&_gameSceneManagerFactory);
//     // root->addFrameListener(&_frameListener);

//     // addInputListener(&_inputListener);
// }

OgreBites::ApplicationContext& MazeGame::App::getContext()
{
    return _context;
}

MazeGame::Game& App::getGame()
{
    return _game;
}
