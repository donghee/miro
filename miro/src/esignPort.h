#pragma once

#include "ofMain.h"

#include "esignColumn.h"
#include "esignLed.h"
#include "ofxXmlSettings.h"
#include "esignUdp.h"

class EsignPort
{
    public:
        void setup(int fixtureId, int portId);
        void update();
        void draw();

        void addColumn(int x,int y, int ledSize, bool direction);
        void saveColumns();

        void setColor(int columnIndex, uint8_t r, uint8_t g, uint8_t b);
        void setColor(uint8_t r, uint8_t g, uint8_t b);

        int getBindedLedSize();
        EsignLed* getEsignLeds();
        vector <EsignColumn> getEsignColumns();
    protected:

    private:
        int fixtureId;
        int portId;
        EsignLed* EsignLeds;
        void bindColumnWithLed();
        int numberOfColumns;
        vector <EsignColumn> EsignColumns;
};
