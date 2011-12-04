#pragma once

#include "ofMain.h"
#include "esignLed.h"

#define UP true
#define DOWN false

class EsignColumn
{
    public:
        void setup(int x, int y, int size, int direction);
        void setPosition(int x, int y);
        void setColor(uint8_t r, uint8_t g, uint8_t b);
        void setColor(int z, uint8_t r, uint8_t g, uint8_t b);
        void setDirection(bool direction);
        void setSize(int size);
        void setTopChannel(int channel);
        void setBottomChannel(int channel);
        void draw(int columnIndex, ofColor borderColor);
        
        int getX();
        int getY();
        ofColor getColor();

        int getSize();
        bool getDirection();
        int getTopChannel();
        int getBottomChannel();

        void setLedColor(int z, uint8_t r, uint8_t g, uint8_t b);

        void loadEsignLeds(EsignLed* _EsignLeds);
    protected:
    private:
        EsignLed* eSignColumnLeds;

        ofRectangle columnRect;

        int posX, posY;
        int LedNumber;
        bool direction;
        int topChannel;
        int bottomChannel;
        bool isBind;
        
        ofColor color;
};
