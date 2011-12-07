#include "esignLed.h"

void EsignLed::setColor(uint8_t r, uint8_t g, uint8_t b, float  easing)
{
    r = MAX(r-110,0);
    g = MAX(r-120,0);
    b = MAX(r-170,0);
    color.r += (r-color.r)*0.6;
    color.g += (g-color.g)*0.6;
    color.b += (b-color.b)*0.6;      
}

void EsignLed::setColor(uint8_t r, uint8_t g, uint8_t b)
{
    setColor(r,g,b,1);
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
