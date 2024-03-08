#pragma once

#include <Ogre.h>
#include <OgreBullet.h>

#include "Battery.hpp"

class PlayerRayResultCallback : public Ogre::Bullet::RayResultCallback
{
    public:
        PlayerRayResultCallback(const std::vector<Battery>& batteries);

        void addSingleResult(const Ogre::MovableObject* other, float distance) override;
    private:
        const std::vector<Battery>& _batteries;
};