#include "PlayerRayResultCallback.hpp"

#include <algorithm>
#include <iostream>

PlayerRayResultCallback::PlayerRayResultCallback(std::vector<Battery> &batteries)
    : _batteries(batteries),
    _nearest(nullptr, 0.0f)
{
}

void PlayerRayResultCallback::addSingleResult(const Ogre::MovableObject *other, float distance)
{
    auto batteryIt = std::find_if(_batteries.begin(), _batteries.end(), [=] (const Battery& battery) {
        return static_cast<Ogre::MovableObject*>(battery.getEntity()) == other;
    });

    if(batteryIt == _batteries.end())
    {
        return;
    }

    if(_nearest.first == nullptr || distance < _nearest.second)
    {
        _nearest = { &(*batteryIt), distance };
    }
}

Battery *PlayerRayResultCallback::getNearestResult()
{
    return _nearest.first;
}
