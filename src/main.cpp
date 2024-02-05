#include <iostream>
#include <thread>
#include <chrono>
#include <numeric>

#include <Ogre.h>
#include <OgreApplicationContext.h>
#include <OgreCameraMan.h>
#include <Bullet/OgreBullet.h>

#include "InputListener.hpp"
#include "FrameListener.hpp"
#include "Game.hpp"
#include "App.hpp"
#include "GameSceneManagerFactory.hpp"

int main(int, char**)
{
    MazeGame::App app{};
    Ogre::Bullet::DynamicsWorld world({0.0f, -9.0f, 0.0f});

    auto& game = app.getGame();
    auto& context = app.getContext();

    auto root = context.getRoot();
    auto sceneManager = app.getScene();

    auto sceneRoot = sceneManager->getRootSceneNode();

    Ogre::Plane ground{0, 0, 1, 1};

    auto groundMesh = Ogre::MeshManager::getSingleton().createPlane("Ground", Ogre::RGN_DEFAULT, ground, 1200, 1200);
    auto groundEntity = sceneManager->createEntity(groundMesh);

    groundEntity->setMaterialName("SimpleGround");

    sceneRoot
        ->createChildSceneNode("Ground", {0, 0, 0}, Ogre::Quaternion(Ogre::Degree(90), Ogre::Vector3::NEGATIVE_UNIT_X))
        ->attachObject(groundEntity);

    world.addRigidBody(0, groundEntity, Ogre::Bullet::CT_BOX);

    for(int i = 1; i <= 10; i++)
    {
        auto entity = sceneManager->createEntity("cube.mesh");

        entity->setMaterialName("SimpleBox");

        auto meshNode = sceneRoot->createChildSceneNode("EntityNode" + std::to_string(i), {110.0f * i, 0, 0});
        meshNode->attachObject(entity);

        meshNode->scale(1, 1 + (0.1f * i), 1);

        auto body = world.addRigidBody(5, entity, Ogre::Bullet::CT_BOX);

        body->setLinearVelocity({0, 40, 0});
    }

    auto cameraNode = sceneManager->getCameraNode();
    auto light = sceneManager->getTorchLight();

    std::array<long long, 200> times;
    auto timesIt = times.begin();

    bool running = true;
    while(running)
    {
        auto start = std::chrono::steady_clock::now();
        running = root->renderOneFrame() && !game.isEnded();

        sceneRoot->needUpdate(true);

        auto quaternion =
            Ogre::Quaternion(Ogre::Degree(-game.getAngleX()), Ogre::Vector3::UNIT_Y) *
            Ogre::Quaternion(Ogre::Degree(-game.getAngleY()), Ogre::Vector3::UNIT_X);

        cameraNode->setOrientation(quaternion);

        auto& move = game.move;

        cameraNode->translate({(float)move.left - move.right, 0, 0}, Ogre::Node::TS_LOCAL);
        cameraNode->translate({0, 0, (float)move.back - move.front}, Ogre::Node::TS_LOCAL);

        light->setSpotlightRange(Ogre::Degree(game.size), Ogre::Degree(game.size + 35));

        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count();
        context.pollEvents();

        world.getBtWorld()->stepSimulation(1);

        if(game.action)
        {
            game.action = false;

            std::cout << cameraNode->getPosition() << std::endl;
        }

        *timesIt = duration;
        timesIt++;

        if(timesIt == times.end())
        {
            timesIt = times.begin();

            auto average = float(std::accumulate(times.begin(), times.end(), (long long)0) / times.size());

            std::cout << "Average time per frame: " << average << std::endl;
        }
    }

    return 0;
}