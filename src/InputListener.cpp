#include "InputListener.hpp"

#include <iostream>

using namespace Game;

InputListener::InputListener(Game& game)
    : _game(game)
{
}

InputListener::~InputListener()
{
}

bool InputListener::keyPressed(const OgreBites::KeyboardEvent &evt)
{
    std::cout << "Key pressed " << evt.keysym.sym << std::endl;

    if(evt.keysym.sym == 103)
    {
        _game.get().end();
    }

    return true;
}

bool InputListener::keyReleased(const OgreBites::KeyboardEvent &evt)
{
    std::cout << "Key released " << evt.keysym.sym << std::endl;

    return true;
}

bool InputListener::mouseMoved(const OgreBites::MouseMotionEvent& evt)
{
    float angleX = evt.xrel / 2.0f;
    float angleY = evt.yrel / 2.0f;

    _game.get().rotateX(angleX);
    _game.get().rotateY(angleY);

    return true;
}