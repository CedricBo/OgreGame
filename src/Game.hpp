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

        float getAngleX() const;
        float rotateX(float angle);

        float getAngleY() const;
        float rotateY(float angle);

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

        float _angleX;
        float _angleY;

        bool _light;
    };
}
