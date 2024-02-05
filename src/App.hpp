#pragma once

#include <OgreApplicationContext.h>
#include <Bullet/OgreBullet.h>

#include "Game.hpp"
#include "FrameListener.hpp"
#include "InputListener.hpp"
#include "GameSceneManagerFactory.hpp"
#include "GameScene.hpp"

namespace MazeGame
{
    class App
    {
        public:
            App();
            ~App();

            // Ogre::Root* getRoot();
            OgreBites::ApplicationContext& getContext();
            Game& getGame();

            MazeGame::GameScene* getScene() const;

            void initViewPort(Ogre::Camera* camera);
        private:
            OgreBites::ApplicationContext _context;
            Game _game;
            MazeGame::InputListener _inputListener;
            MazeGame::GameSceneManagerFactory _gameSceneManagerFactory;

            MazeGame::GameScene* _scene;
            Ogre::Bullet::DynamicsWorld _world;

            Ogre::Viewport* _viewport;

            void initRTSShaderGenerator();
    };
}

/*
    Game::Game game{};
    Game::FrameListener frameListener{game};
    Game::InputListener inputListener{game};
    Game::GameSceneManagerFactory gameSceneManagerFactory{};
*/
