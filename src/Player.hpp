#pragma once

#include "Battery.hpp"

class Player
{
    public:
        Player();
        ~Player();

        void setLookedBattery(Battery* battery);
        void grabLookedBattery();
        void releaseBattery();

        Battery* getGrabbedBattery();
    private:
        Battery* _lookedBattery = nullptr;
        Battery* _grabbedBattery = nullptr;
};