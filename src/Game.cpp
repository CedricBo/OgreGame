#include "Game.hpp"

#include <iostream>

Game::Game::Game()
    : _end(false),
    _angleX(0),
    _angleY(0)
{
}

Game::Game::~Game()
{
}

void Game::Game::end()
{
    _end = true;
}

const bool &Game::Game::isEnded() const
{
    return _end;
}

float Game::Game::getAngleX() const
{
    return _angleX;
}

float Game::Game::rotateX(float angleX)
{
    return _angleX += angleX;
}

float Game::Game::getAngleY() const
{
    return _angleY;
}

float Game::Game::rotateY(float angleY)
{
    return _angleY += angleY;
}
