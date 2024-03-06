#include <iostream>
#include <thread>
#include <chrono>
#include <numeric>

#include <Ogre.h>
#include <OgreApplicationContext.h>
#include <OgreCameraMan.h>
#include <Bullet/OgreBullet.h>

#include "InputListener.hpp"
#include "Game.hpp"
#include "App.hpp"
#include "GameSceneManagerFactory.hpp"

int main(int, char**)
{
    MazeGame::App app{};

    app.run();

    return 0;
}