#pragma once

#include <Ogre.h>
#include <OgreBullet.h>

class Player;
class PlayerRayResultCallback : public Ogre::Bullet::RayResultCallback
{
    public:
        PlayerRayResultCallback() = default;

        void addSingleResult(const Ogre::MovableObject* other, float distance) override;
    private:
};