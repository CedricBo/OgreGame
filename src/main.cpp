#include <iostream>
#include <thread>
#include <Ogre.h>
#include <OgreApplicationContext.h>
#include <OgreCameraMan.h>
#include <Bullet/OgreBullet.h>
#include <chrono>
#include <numeric>

#include "InputListener.hpp"
#include "FrameListener.hpp"
#include "Game.hpp"
#include "GameSceneManagerFactory.hpp"

int main(int, char**)
{
    OgreBites::ApplicationContext context{};
    Game::Game game{};
    Game::FrameListener frameListener{game};
    Game::InputListener inputListener{game};
    Game::GameSceneManagerFactory gameSceneManagerFactory{};
    Ogre::Bullet::DynamicsWorld world({0.0f, -9.0f, 0.0f});

    context.initApp();
    auto root = context.getRoot();

    root->addSceneManagerFactory(&gameSceneManagerFactory);

    auto sceneManager = static_cast<Game::GameScene*>(root->createSceneManager(Game::GameScene::typeName));
    auto shaderGenerator = Ogre::RTShader::ShaderGenerator::getSingletonPtr();

    shaderGenerator->addSceneManager(sceneManager);

    auto sceneRoot = sceneManager->getRootSceneNode();

    sceneManager->setAmbientLight(Ogre::ColourValue{0.1, 0.1, 0.1});

    auto camera = sceneManager->createCamera("Camera");
    camera->setNearClipDistance(5);

    auto light = sceneManager->createLight(Ogre::Light::LightTypes::LT_SPOTLIGHT);
    light->setSpecularColour(Ogre::ColourValue::Green);

    sceneManager->setShadowTechnique(Ogre::ShadowTechnique::SHADOWTYPE_TEXTURE_ADDITIVE);

    auto light2 = sceneManager->createLight(Ogre::Light::LightTypes::LT_SPOTLIGHT);
    light2->setSpecularColour(Ogre::ColourValue::Red);
    auto light2Node = sceneRoot->createChildSceneNode({ 0, 30, 0}, Ogre::Quaternion(Ogre::Degree(-90), Ogre::Vector3::UNIT_Y));
    light2Node->attachObject(light2);

    auto cameraNode = sceneRoot->createChildSceneNode();
    cameraNode->attachObject(camera);
    cameraNode->attachObject(light);

    Ogre::Plane ground{0, 0, 1, 1};

    auto groundMesh = Ogre::MeshManager::getSingleton().createPlane("Ground", Ogre::RGN_DEFAULT, ground, 1200, 1200);
    auto groundEntity = sceneManager->createEntity(groundMesh);

    groundEntity->setMaterialName("RTSS/PerPixel_SinglePass");

    sceneRoot
        ->createChildSceneNode("Ground", {0, 0, 0}, Ogre::Quaternion(Ogre::Degree(90), Ogre::Vector3::NEGATIVE_UNIT_X))
        ->attachObject(groundEntity);

    world.addRigidBody(0, groundEntity, Ogre::Bullet::CT_BOX);


    for(int i = 1; i <= 10; i++)
    {
        auto entity = sceneManager->createEntity("cube.mesh");

        entity->setMaterialName("RTSS/PerPixel_SinglePass");

        auto meshNode = sceneRoot->createChildSceneNode("EntityNode" + std::to_string(i), {110.0f * i, 0, 0});
        meshNode->attachObject(entity);

        meshNode->scale(1, 1 + (0.1f * i), 1);

        world.addRigidBody(5, entity, Ogre::Bullet::CT_BOX);
    }

    root->addFrameListener(&frameListener);
    context.addInputListener(&inputListener);

    camera->setAutoAspectRatio(true);
    auto viewport = context.getRenderWindow()->addViewport(camera);
    viewport->setBackgroundColour(Ogre::ColourValue(0,0,0));

    viewport->setMaterialScheme(Ogre::RTShader::ShaderGenerator::DEFAULT_SCHEME_NAME);

    cameraNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TransformSpace::TS_WORLD);

    cameraNode->setPosition({100, 150, 200});
    cameraNode->lookAt({0, 0, 0}, Ogre::Node::TS_WORLD);

    std::array<long long, 200> times;
    auto timesIt = times.begin();

    bool running = true;
    while(running)
    {
        auto start = std::chrono::steady_clock::now();
        running = root->renderOneFrame();
        sceneRoot->needUpdate(true);

        world.getBtWorld()->stepSimulation(1);

        auto quaternion =
            Ogre::Quaternion(Ogre::Degree(-game.getAngleX()), Ogre::Vector3::UNIT_Y) *
            Ogre::Quaternion(Ogre::Degree(-game.getAngleY()), Ogre::Vector3::UNIT_X);

        cameraNode->setOrientation(quaternion);

        auto& move = game.move;

        cameraNode->translate({(float)move.left - move.right, 0, 0}, Ogre::Node::TS_LOCAL);
        cameraNode->translate({0, 0, (float)move.back - move.front}, Ogre::Node::TS_LOCAL);

        light->setSpotlightRange(Ogre::Degree(game.size), Ogre::Degree(game.size + 5));

        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count();
        context.pollEvents();

        *timesIt = duration;
        timesIt++;

        if(timesIt == times.end())
        {
            timesIt = times.begin();

            auto total = std::accumulate(times.begin(), times.end(), (long long)0);

            std::cout << "Average time per frame: " << total / times.size() << std::endl;
        }
    }

    return 0;
}