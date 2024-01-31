#pragma once

#include <OgreFrameListener.h>

#include "Game.hpp"

namespace Game
{
    class FrameListener : public Ogre::FrameListener
    {
    public:
        FrameListener(Game& game);
        ~FrameListener();

        bool frameEnded(const Ogre::FrameEvent &evt) override;
    private:
        const std::reference_wrapper<Game> _game;
    };
}