#include "Player.hpp"

Player::Player(){}

Player::~Player()
{
}

void Player::setLookedBattery(Battery *battery)
{
    _lookedBattery = battery;
}

void Player::grabLookedBattery()
{
    _grabbedBattery = _lookedBattery;
}

void Player::releaseBattery()
{
    if(_grabbedBattery == nullptr)
    {
        return;
    }

    _grabbedBattery->applyGravitySettings();

    _grabbedBattery = nullptr;
}

Battery *Player::getGrabbedBattery()
{
    return _grabbedBattery;
}
