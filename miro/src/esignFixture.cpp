#include "esignFixture.h"


void EsignFixture::setup(int id)
{
    fixtureId = id;
    ip= ip_list[id];
    e = new EsignUdp(ip, PORT, PORT_COUNT, CLUSTER_COUNT, DATA_SIZE);
    e->setDebug(false);
    
    // 8개 port setup
    for (int i =0 ; i <PORT_COUNT; i++)  {
        EsignPort port;
        port.setup(id,i); // 0 is fuxture id
        ports.push_back(port);
    }
}

void EsignFixture::update()
{
    for (int i=0; i< ports.size(); i++) {            
        updatePort(i);
    }
}

void EsignFixture::updatePort(int id)
{
    uint8_t r,g,b;
    EsignPort port = ports[id];
    
    for (int j=0; j< CLUSTER_COUNT; j++) {
        r = port.getEsignLeds()[j].getColor().r;
        g = port.getEsignLeds()[j].getColor().g;
        b = port.getEsignLeds()[j].getColor().b;
        e->setPixel(id*CLUSTER_COUNT+j,r,g,b);
    }
}

void EsignFixture::draw(bool show)
{
    e->sendto();

    if (show == false)
        return;
    
    for (int i=0; i< ports.size(); i++) {        
        ports[i].draw();
    }
}

vector <EsignPort> EsignFixture::getEsignPorts()
{
    return ports;
}

void EsignFixture::setColor(uint8_t r, uint8_t g, uint8_t b)
{
    red = r;
    green = g;
    blue = b;
    for (int i=0; i< ports.size(); i++) {    
        ports[i].setColor(r,g,b);
    }
}

void EsignFixture::setColor(int portId, int columnId, uint8_t r, uint8_t g, uint8_t b)
{
    ports[portId].setColor(columnId, r,g,b);
}

void EsignFixture::save()
{
    for (int i=0; i< ports.size(); i++) {
        ports[i].saveColumns();
    }
}

void EsignFixture::addColumn(int portId, int x, int y, int ledSize, bool direction)
{
    ports[portId].addColumn(x,y, ledSize, direction);
}
