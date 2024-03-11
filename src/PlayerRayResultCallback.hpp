#pragma once

#include <Ogre.h>
#include <OgreBullet.h>

#include "Battery.hpp"

class PlayerRayResultCallback : public Ogre::Bullet::RayResultCallback
{
    public:
        PlayerRayResultCallback(std::vector<Battery>& batteries);

        void addSingleResult(const Ogre::MovableObject* other, float distance) override;

        Battery* getNearestResult();
    private:
        std::vector<Battery>& _batteries;

        // Battery, distance
        std::pair<Battery*, float> _nearest;
};