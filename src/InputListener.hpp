#pragma once

#include <OgreInput.h>

#include "Game.hpp"

namespace MazeGame
{
    class InputListener : public OgreBites::InputListener
    {
    public:
        InputListener(Game& game);
        ~InputListener();

        bool keyPressed(const OgreBites::KeyboardEvent& evt) override;
        bool keyReleased(const OgreBites::KeyboardEvent& evt) override;
        bool mouseMoved(const OgreBites::MouseMotionEvent& evt) override;
        bool mouseWheelRolled(const OgreBites::MouseWheelEvent& evt) override;
        bool mousePressed(const OgreBites::MouseButtonEvent& evt) override;
        bool mouseReleased(const OgreBites::MouseButtonEvent& evt) override;
    private:
        std::reference_wrapper<Game> _game;

        bool _mainMouseCliked;
    };
}