#include "esignLed.h"

void EsignLed::setColor(uint8_t r, uint8_t g, uint8_t b)
{
    color.r = r;
    color.g = g;
    color.b = b;
}

ofColor EsignLed::getColor()
{
    return color;
}

void EsignLed::setPosition(int x, int y, int z)
{
    setX(x); setY(y); setZ(z);
}

void EsignLed::setX(int _x)
{
    x = _x;
}

void EsignLed::setY(int _y)
{
    y = _y;
}

void EsignLed::setZ(int _z)
{
    z = _z;
}

int EsignLed::getX() {return x;}
int EsignLed::getY() {return y;}
int EsignLed::getZ() {return z;}
