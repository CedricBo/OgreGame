#include "Game.hpp"

#include <iostream>

MazeGame::Game::Game()
    : _end(false),
    _angleX(0),
    _angleY(0),
    move({false, false, false, false}),
    size(5),
    _light(true)
{
}

MazeGame::Game::~Game()
{
}

void MazeGame::Game::end()
{
    _end = true;
}

const bool &MazeGame::Game::isEnded() const
{
    return _end;
}

void MazeGame::Game::switchLight()
{
    _light = !_light;
}

bool MazeGame::Game::isLightOn()
{
    return _light;
}

float MazeGame::Game::getAngleX() const
{
    return _angleX;
}

float MazeGame::Game::rotateX(float angleX)
{
    return _angleX += angleX;
}

float MazeGame::Game::getAngleY() const
{
    return _angleY;
}

float MazeGame::Game::rotateY(float angleY)
{
    return _angleY += angleY;
}
