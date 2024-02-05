#pragma once

#include <OgreSceneManager.h>

namespace MazeGame
{
    class GameSceneManagerFactory : public Ogre::SceneManagerFactory
    {
    public:
        GameSceneManagerFactory();
        ~GameSceneManagerFactory();

        const std::string& getTypeName() const;

        Ogre::SceneManager* createInstance(const std::string& instanceName);
    private:
        /* data */
    };
}
