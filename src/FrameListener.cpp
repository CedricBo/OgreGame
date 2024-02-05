#include "FrameListener.hpp"

using namespace MazeGame;

FrameListener::FrameListener(Game& game)
    : _game(game)
{
}

FrameListener::~FrameListener()
{
}

bool FrameListener::frameEnded(const Ogre::FrameEvent &evt)
{
    return !_game.get().isEnded();
}
