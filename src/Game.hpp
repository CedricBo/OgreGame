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
    private:
        bool _end;

        float _angleX;
        float _angleY;
    };
}
