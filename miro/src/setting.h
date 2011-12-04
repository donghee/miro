#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "esignColumn.h"

#define PORT 8001
#define PORT_COUNT 8
#define CLUSTER_COUNT 175
#define DATA_SIZE 1432
#define PIXELS_SIZE 3*PORT_COUNT*CLUSTER_COUNT // 3*8* 125

static const string ip_list[] =
    {"192.168.1.11", "192.168.1.12", "192.168.1.13", "192.168.1.14",
     "192.168.1.15", "192.168.1.16", "192.168.1.17", "192.168.1.18"};

class Setting
{
    public:
        Setting();
        virtual ~Setting();

    	vector <EsignColumn> loadColumns(int fixtureId, int portId);
        void saveColumns(int fixtureId, int portId , const vector <EsignColumn>& EsignColumns);

   protected:
   private:
        string getXmlFileName(int fixtureId, int portId);
        ofxXmlSettings XML;
        string xmlFileName;
        string message;
};

