#pragma once

#include <OgreSceneManager.h>

#include "Game.hpp"

namespace MazeGame
{
    class GameSceneManagerFactory : public Ogre::SceneManagerFactory
    {
    public:
        GameSceneManagerFactory(Game& game);
        ~GameSceneManagerFactory();

        const std::string& getTypeName() const;

        Ogre::SceneManager* createInstance(const std::string& instanceName);
    private:
        Game& _game;
    };
}
