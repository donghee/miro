#include "esignColumn.h"

void EsignColumn::setup(int x, int y, int size, int _direction)
{
    //1. save column x,y postion
    //2. instantiate LEDNumber of eSign objects
    //3. assign z postion and network Postion of eSign based on direction
    //4. push eSign
    setPosition(x,y);
    LedNumber = size;
    direction = _direction;

    // 각 LED와 연결하지 않음. loadEsignLeds로 각 LED와 연결한다.
    isBind = false;

    // 그림 그릴때 사용
    columnRect = ofRectangle();
    columnRect.set(0,0,10,10);
}

void EsignColumn::loadEsignLeds(EsignLed* _EsignLeds)
{
    eSignColumnLeds = _EsignLeds;
    isBind = true;
}

void EsignColumn::setPosition(int x, int y)
{
    posX = x;
    posY = y;
}

int EsignColumn::getX()
{
    return posX;
}


int EsignColumn::getY()
{
    return posY;
}

int EsignColumn::getSize()
{
    return LedNumber;
}

ofColor EsignColumn::getColor()
{
    if (isBind) {
        return eSignColumnLeds[0].getColor(); // TODO: change to Top channel color
    } else {
        return color;
    }
}

int EsignColumn::getTopChannel()
{
    return topChannel;
}

int EsignColumn::getBottomChannel()
{
    return bottomChannel;
}

bool EsignColumn::getDirection()
{
    return direction;
}

void EsignColumn::setDirection(bool _direction)
{
    direction = _direction;
}

void EsignColumn::setColor(uint8_t r, uint8_t g, uint8_t b)
{
    color.r = r;
    color.g = g;
    color.b = b;

    if (isBind) {
        for(int i=0; i<LedNumber;i++)
            {
                eSignColumnLeds[i].setColor(r,g,b);
            }
    }
}

void EsignColumn::setColor(int z, uint8_t r, uint8_t g, uint8_t b)
{
    if (isBind) {
        domain_error("This Column is not binded to LEDs.");
    }

    for(int i=0; i<LedNumber;i++)
    {
        if (eSignColumnLeds[i].getZ() == z)
        {
            eSignColumnLeds[i].setColor(r,g,b);
         }
    }
}


void EsignColumn::setTopChannel(int channel)
{
    topChannel = channel;
}

void EsignColumn::setBottomChannel(int channel)
{
    bottomChannel = channel;
}

void EsignColumn::draw(int columnIndex, ofColor borderColor)
{
    ofColor color;
    color = getColor();
    ofPushMatrix();
    ofPushStyle();

    ofTranslate(posX, posY);
    ofSetColor(color);
    ofFill();
    // 내부
    // ofRect(columnRect);
    ofCircle(0,0,5);

    // ofBeginShape();
    // ofVertex(2,2);
    // ofVertex(0,5);
    // ofVertex(2,8);
    // ofVertex(5,9);
    // ofVertex(8,7);
    // ofVertex(9,10);
    // ofVertex(11,10);
    // ofVertex(12,6);
    // ofVertex(14,6);
    // ofVertex(14,4);
    // ofVertex(11,3);
    // ofVertex(10,1);
    // ofVertex(8,3);
    // ofVertex(7,0);
    // ofVertex(6,0);
    // ofVertex(4,2);
    // ofVertex(2,2);
    // ofEndShape();


    // 테두리
    ofNoFill();
    ofSetColor(borderColor); //border color
    ofCircle(0,0,6);

    // ofBeginShape();
    // ofVertex(2,2);
    // ofVertex(0,5);
    // ofVertex(2,8);
    // ofVertex(5,9);
    // ofVertex(8,7);
    // ofVertex(9,8);
    // ofVertex(11,9);
    // ofVertex(12,7);
    // ofVertex(14,6);
    // ofVertex(14,4);
    // ofVertex(11,3);
    // ofVertex(10,1);
    // ofVertex(8,3);
    // ofVertex(7,0);
    // ofVertex(6,0);
    // ofVertex(4,2);
    // ofVertex(2,2);
    // ofEndShape();

    // 컬럼 번호
    ofSetColor(255);
    // ofDrawBitmapString(ofToString(columnIndex), -5, 5);
    // TOP channel
    ofDrawBitmapString(ofToString(topChannel+1), -5, 5); // map start at 1 not 0.
    ofPopStyle();
    ofPopMatrix();
}

