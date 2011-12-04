#pragma once

#include "ofMain.h"

class EsignLed
{
    public:
        void setColor(uint8_t r, uint8_t g, uint8_t b);
        ofColor getColor();

        void setPosition(int x, int y, int z);
        void setX(int x);
        void setY(int y);
        void setZ(int z);
        int getX();
        int getY();
        int getZ();

    protected:
    private:
        ofColor color;

        int x;
        int y;
        int z;
};
