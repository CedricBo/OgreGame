#pragma once

#include <OgreInput.h>

#include "Game.hpp"

namespace Game
{
    class InputListener : public OgreBites::InputListener
    {
    public:
        InputListener(Game& game);
        ~InputListener();

        bool keyPressed(const OgreBites::KeyboardEvent& evt) override;
        bool keyReleased(const OgreBites::KeyboardEvent& evt) override;
        bool mouseMoved(const OgreBites::MouseMotionEvent& evt) override;
    private:
        std::reference_wrapper<Game> _game;
    };
}