#include <iostream>
#include <thread>
#include <Ogre.h>
#include <OgreApplicationContext.h>
#include <OgreCameraMan.h>

#include "InputListener.hpp"
#include "FrameListener.hpp"
#include "Game.hpp"
#include "App.hpp"
#include "GameSceneManagerFactory.hpp"

int main(int, char**)
{
    OgreBites::ApplicationContext context{};
    Game::Game game{};
    Game::FrameListener frameListener{game};
    Game::InputListener inputListener{game};
    Game::GameSceneManagerFactory gameSceneManagerFactory{};

    context.initApp();
    auto root = context.getRoot();

    root->addSceneManagerFactory(&gameSceneManagerFactory);

    auto sceneManager = static_cast<Game::GameScene*>(root->createSceneManager(Game::GameScene::typeName));
    auto sceneRoot = sceneManager->getRootSceneNode();

    sceneManager->setAmbientLight(Ogre::ColourValue::White);

    auto camera = sceneManager->createCamera("Camera");
    camera->setNearClipDistance(5);

    auto cameraNode = sceneRoot->createChildSceneNode();
    cameraNode->attachObject(camera);

    auto entity = sceneManager->createEntity("cube.mesh");
    entity->setMaterialName("Examples/BumpMapping/MultiLight");
    auto meshNode = sceneRoot->createChildSceneNode("EntityNode");
    meshNode->attachObject(entity);

    entity->setCastShadows(true);

    root->addFrameListener(&frameListener);
    context.addInputListener(&inputListener);

    camera->setAutoAspectRatio(true);
    auto viewport = context.getRenderWindow()->addViewport(camera);
    viewport->setBackgroundColour(Ogre::ColourValue(0,0,0));

    sceneManager->setShadowTechnique(Ogre::ShadowTechnique::SHADOWDETAILTYPE_ADDITIVE);

    cameraNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TransformSpace::TS_WORLD);

    cameraNode->setPosition({100, 150, 200});
    cameraNode->lookAt({0, 0, 0}, Ogre::Node::TS_WORLD);

    while(root->renderOneFrame())
    {
        auto quaternion =
            Ogre::Quaternion(Ogre::Degree(-game.getAngleX()), Ogre::Vector3::UNIT_Y) *
            Ogre::Quaternion(Ogre::Degree(-game.getAngleY()), Ogre::Vector3::UNIT_X);

        cameraNode->setOrientation(quaternion);

        context.pollEvents();
    }

    return 0;
}

// int main(int, char**)
// {
//     App app{};
//     // Game::Game game{};
//     // Game::FrameListener frameListener{game};
//     // Game::InputListener inputListener{game};

//     app.initApp();

//     Ogre::Root* root = app.getRoot();

//     // auto sceneManager = root->createSceneManager();

//     // auto sceneRoot = sceneManager->createSceneNode();

//     // sceneManager->setAmbientLight(Ogre::ColourValue::White);

//     // auto camera = sceneManager->createCamera("Camera");
//     // camera->setNearClipDistance(1);
//     // camera->setFarClipDistance(0);
//     // camera->setAutoAspectRatio(true);
//     // camera->setFOVy(Ogre::Degree(360));

//     // auto cameraNode = sceneRoot->createChildSceneNode("CameraNode");
//     // cameraNode->attachObject(camera);
//     // cameraNode->setDebugDisplayEnabled(true);

//     // for(auto& mesh : Ogre::MeshManager::getSingleton().getResourceIterator())
//     // {
//     //     std::cout << "[Mesh] name: " << mesh.second->getName() << std::endl;
//     // }

//     // auto entity = sceneManager->createEntity("ogrehead.mesh");
//     // // auto meshObject = sceneManager->createEntity("Entity", mesh);
//     // auto meshNode = sceneRoot->createChildSceneNode("EntityNode");
//     // meshNode->setDebugDisplayEnabled(true);

//     // auto debugDrawer = sceneManager->getDebugDrawer();

//     // debugDrawer->drawBone(meshNode);

//     // root->addFrameListener(&frameListener);
//     // context.addInputListener(&inputListener);

//     // auto viewport = context.getRenderWindow()->addViewport(camera);
//     // viewport->setBackgroundColour(Ogre::ColourValue(0,0,0, 1));

//     // // cameraNode->setPosition({0, 0, 100});
//     // meshNode->setPosition({0, 0, 90});

//     // cameraNode->lookAt(meshNode->getPosition(), Ogre::Node::TS_LOCAL);

//     root->startRendering();

//     return 0;
// }
