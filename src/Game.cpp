#include "Game.hpp"

#include <iostream>

MazeGame::Game::Game()
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

void MazeGame::Game::rotateView(float angleX, float angleY)
{
    _viewAngleX += angleX;
    _viewAngleY += angleY;
}

void MazeGame::Game::rotateShip(float angleX, float angleY)
{
    _shipAngleX += angleX;
    _shipAngleY += angleY;
}

std::pair<float, float> MazeGame::Game::getViewAngle()
{
    return {_viewAngleX, _viewAngleY};
}

std::pair<float, float> MazeGame::Game::getShipAngle()
{
    return {_shipAngleX, _shipAngleY};
}

bool MazeGame::Game::hasMove()
{
    return move.back || move.front || move.left || move.right;
}

void MazeGame::Game::requestRelease()
{
    _requestRelease = true;
}

void MazeGame::Game::resetRequestRelease()
{
    _requestRelease = false;
}

bool MazeGame::Game::hasRequestRelease()
{
    return _requestRelease;
}

Player& MazeGame::Game::getPlayer()
{
    return _player;
}
