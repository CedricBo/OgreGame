#pragma once

#include <OgreFrameListener.h>

namespace Game
{
    class Game
    {
    public:
        Game();
        ~Game();

        void end();
        const bool& isEnded() const;

        float getAngleX() const;
        float rotateX(float angle);

        float getAngleY() const;
        float rotateY(float angle);

        struct Move {
            bool left;
            bool right;
            bool front;
            bool back;
        } move;

        float size;

        bool detach;
    private:
        bool _end;

        float _angleX;
        float _angleY;
    };
}
