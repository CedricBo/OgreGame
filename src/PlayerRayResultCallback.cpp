#include "PlayerRayResultCallback.hpp"

#include <algorithm>
#include <iostream>

PlayerRayResultCallback::PlayerRayResultCallback(const std::vector<Battery> &batteries)
    : _batteries(batteries)
{
}

void PlayerRayResultCallback::addSingleResult(const Ogre::MovableObject *other, float distance)
{
    auto a = std::find_if(_batteries.begin(), _batteries.end(), [=] (const Battery& battery) {
        return static_cast<Ogre::MovableObject*>(battery.getEntity()) == other;
    });

    if(a != _batteries.end())
    {
        std::cout << "Hit " << other->getParentNode()->getName() << std::endl;
    }
}
