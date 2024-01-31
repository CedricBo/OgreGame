#pragma once

#include <OgreSceneManager.h>

namespace Game
{
    class GameScene : public Ogre::SceneManager
    {
    public:
        static std::string typeName;

        GameScene(std::string instanceName);
        ~GameScene();

        const std::string& getTypeName(void) const;
    };

    class GameSceneManagerFactory : public Ogre::SceneManagerFactory
    {
    public:
        GameSceneManagerFactory();
        ~GameSceneManagerFactory();

        const std::string& getTypeName(void) const;

        Ogre::SceneManager* createInstance(const std::string& instanceName);
    private:
        /* data */
    };
}
