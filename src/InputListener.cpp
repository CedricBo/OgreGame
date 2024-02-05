#include "InputListener.hpp"

#include <iostream>
#include <algorithm>

using namespace MazeGame;

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

    switch (evt.keysym.sym)
    {
    case 103:
        _game.get().end();
        break;
    case 122:
        _game.get().move.front = true;
        break;
    case 113:
        _game.get().move.right = true;
        break;
    case 100:
        _game.get().move.left = true;
        break;
    case 115:
        _game.get().move.back = true;
        break;
    case 32:
        _game.get().action = true;
        break;
    default:
        break;
    }

    return true;
}

bool InputListener::keyReleased(const OgreBites::KeyboardEvent &evt)
{
    std::cout << "Key released " << evt.keysym.sym << std::endl;

    switch (evt.keysym.sym)
    {
    case 122:
        _game.get().move.front = false;
        break;
    case 113:
        _game.get().move.right = false;
        break;
    case 100:
        _game.get().move.left = false;
        break;
    case 115:
        _game.get().move.back = false;
        break;
    default:
        break;
    }

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


bool InputListener::mouseWheelRolled(const OgreBites::MouseWheelEvent& evt)
{
    _game.get().size = std::clamp(_game.get().size + (evt.y / 1.0f), 0.0f, 360.0f);

    std::cout << _game.get().size << std::endl;

    return true;
}