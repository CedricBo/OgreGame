#include "InputListener.hpp"

#include <iostream>
#include <algorithm>

using namespace MazeGame;

InputListener::InputListener(Game& game)
    : _game(game),
    _mainMouseCliked(false)
{
}

InputListener::~InputListener()
{
}

bool InputListener::keyPressed(const OgreBites::KeyboardEvent &evt)
{
    auto& game = _game.get();

    switch (evt.keysym.sym)
    {
    case 102:
        game.switchLight();
        break;
    case 27:
        game.end();
        break;
    case 122:
        game.move.front = true;
        break;
    case 113:
        game.move.right = true;
        break;
    case 100:
        game.move.left = true;
        break;
    case 115:
        game.move.back = true;
        break;
    case 103:
        game.requestRelease();
    default:
        std::cout << evt.keysym.sym << std::endl;
        break;
    }

    return true;
}

bool InputListener::keyReleased(const OgreBites::KeyboardEvent &evt)
{
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

    auto& game = _game.get();

    if(_mainMouseCliked)
    {
        game.rotateShip(angleX, angleY);
    }
    else
    {
        game.rotateView(angleX, angleY);
    }


    return true;
}


bool InputListener::mouseWheelRolled(const OgreBites::MouseWheelEvent& evt)
{
    _game.get().size = std::clamp(_game.get().size + (evt.y / 1.0f), 0.0f, 360.0f);

    return true;
}

bool InputListener::mousePressed(const OgreBites::MouseButtonEvent& evt)
{
    if(evt.button == 1)
    {
        _mainMouseCliked = true;
    }

    return true;
}

bool InputListener::mouseReleased(const OgreBites::MouseButtonEvent& evt)
{
    if(evt.button == 1)
    {
        _mainMouseCliked = false;
    }

    return true;
}