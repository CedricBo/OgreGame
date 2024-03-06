#pragma once

#include <OgreFrameListener.h>

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

        struct Move {
            bool left;
            bool right;
            bool front;
            bool back;
        } move;

        float size;
    private:
        bool _end;

        float _viewAngleX;
        float _viewAngleY;

        float _shipAngleX;
        float _shipAngleY;

        bool _light;
    };
}
