#ifndef ESIGNFIXTURE_H
#define ESIGNFIXTURE_H

#include "ofMain.h"

#include "esignUdp.h"
#include "esignPort.h"
#include "esignLed.h"

#include "setting.h"

class EsignFixture {
    public:
        void setup(int id);
		void update();
		void draw(bool show);
        void addColumn(int portId, int x, int y, int ledSize, bool direction);
        void save();

        vector <EsignPort> getEsignPorts();
            
        void setColor(uint8_t r, uint8_t g, uint8_t b);
        void setColor(int portId, int columnId, uint8_t r, uint8_t g, uint8_t b);

     protected:
     private:
        void updatePort(int portId);

        string ip;
        int fixtureId;
        
        EsignUdp* e;
        EsignPort port;

        bool all_led_off;
        bool flow;
        float aColor    [4];

        int red;
        int green;
        int blue;
        int i;

        vector <EsignPort> ports;
};

#endif // ESIGNFIXTURE_H
