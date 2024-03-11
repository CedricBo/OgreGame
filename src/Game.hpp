#pragma once

#include "Player.hpp"

namespace MazeGame
{
    class Game
    {
    public:
        Game();
        ~Game();

        void end();
        const bool& isEnded() const;

        void switchLight();
        bool isLightOn();

        void rotateView(float angleX, float angleY);
        void rotateShip(float angleX, float angleY);

        std::pair<float, float> getViewAngle();
        std::pair<float, float> getShipAngle();

        bool hasMove();

        void requestRelease();
        void resetRequestRelease();

        bool hasRequestRelease();

        Player& getPlayer();

        struct Move {
            bool left = false;
            bool right = false;
            bool front = false;
            bool back = false;
        } move;

        float size = 0;
    private:
        bool _end = false;
        bool _requestRelease = false;

        float _viewAngleX = 90;
        float _viewAngleY = -90;

        float _shipAngleX = 0;
        float _shipAngleY = 0;

        bool _light = true;

        Player _player;
    };
}
