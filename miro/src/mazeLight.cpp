#include "mazeLight.h"

void MazeLight::setup() 
{
    int numberOfFixture = 9;
    for (int i=0;i < numberOfFixture; i++) {
        EsignFixture fixture;
        fixture.setup(i);
        fixtures.push_back(fixture);
    }

    mapPath = "map/map.png";
    loadEditMap(mapPath);
    setupMovieRect(1024,768);
    map = false;
    led = false;
}

                     

void MazeLight::setupMovieRect(int w, int h)
{
    movieRect = ofRectangle(0,0,w,h);
}

void MazeLight::loadEditMap(string mapPath)
{
    mapImg.loadImage(mapPath);// TODO: 예외 처리
    if (mapImg.width > movieRect. width || mapImg.height > movieRect.height)
    {
        mapImg.resize(1024,768);
    }
}


void MazeLight::update()
{
    for (int i =0; i< fixtures.size(); i++ ) {
        fixtures[i].update();
    }
}

void MazeLight::showMap(bool on)
{
    map = on;
}

void MazeLight::showLed(bool on)
{
    led = on;
}

void MazeLight::drawEditMap()
{
    if (map == false) {
        mapImg.clear();
        return;
    }
    if(!mapImg.isAllocated())
    {
        loadEditMap(mapPath);
    }
    mapImg.draw(0,0,-5);
}

void MazeLight::draw()
{
    drawEditMap();

    for (int i =0; i< fixtures.size(); i++ ) {
        fixtures[i].draw(led);
    }
}

void MazeLight::save()
{
    for (int i =0; i< fixtures.size(); i++ ) {
        fixtures[i].save();
    }
}

void MazeLight::addLight(int fixtureId, int portId, int x, int y, int size, bool
direction)
{
    fixtures[fixtureId].addColumn(portId, x,y,size, direction);
}

vector <EsignFixture> MazeLight::getEsignFixtures()
{
    return fixtures;
}

void MazeLight::setColor(uint8_t r, uint8_t g, uint8_t b)
{
    red = r;
    green = g;
    blue = b;
    // fixture.setColor(red,green,blue);
    for (int i=0; i <fixtures.size(); i++) { //8개
        fixtures[i].setColor(red,green,blue);
    }
}

void MazeLight::setColor(int fixtureId, int portId, int columnId, uint8_t r, uint8_t g, uint8_t b)
{
    if (fixtureId>fixtures.size()-1)
        throw domain_error("fixture ID over fixtures");
    fixtures[fixtureId].setColor(portId, columnId, r, g, b);
}

void MazeLight::setColor(MovieScene& currentScene)
{
    int _x = 0;
    int _y = 0;

    for (int j=0; j <fixtures.size(); j++) { //8개
       for (int pid=0; pid < PORT_COUNT; pid++) {
           mazeLeds = getEsignFixtures()[j].getEsignPorts()[pid].getEsignLeds();
           for (int i=0; i < CLUSTER_COUNT; i++ ) {
               _x = mazeLeds[i].getX();
               _y = mazeLeds[i].getY();
               ofColor _c = currentScene.getColor(_x,_y);
               mazeLeds[i].setColor(_c.r, _c.g, _c.b);
           }
       }
   }
}

void MazeLight::setColor(EffectScene& currentScene)
{
    int _x = 0;
    int _y = 0;

    for (int j=0; j <fixtures.size(); j++) { //8개
       for (int pid=0; pid < PORT_COUNT; pid++) {
           mazeLeds = getEsignFixtures()[j].getEsignPorts()[pid].getEsignLeds();
           for (int i=0; i < CLUSTER_COUNT; i++ ) {
               _x = mazeLeds[i].getX();
               _y = mazeLeds[i].getY();
               ofColor _c = currentScene.getColor(_x,_y);
               mazeLeds[i].setColor(_c.r, _c.g, _c.b);
           }
       }
   }
}
