#pragma once

#include "esignFixture.h"
#include "movieScene.h"
#include "effectScene.h"

class MazeLight
{
    public:
        void setup();
        void update();
        void draw();
        void drawEditMap();

        void setColor(uint8_t r, uint8_t g, uint8_t b);
        void setColor(int fixtureId, int portId, int columnId, uint8_t r, uint8_t g, uint8_t b);
        void setColor(MovieScene& currentScene);
        void setColor(EffectScene& currentScene);
        void showMap(bool on);
        void showLed(bool on);

        void addLight(int fixtureId, int portId, int x, int y, int size, bool direction);
        void save();

        vector <EsignFixture> getEsignFixtures();
        int red;
        int green;
        int blue;
    protected:
    private:
        vector <EsignFixture> fixtures;
        EsignLed* mazeLeds;

        ofRectangle movieRect;
        ofImage mapImg;
        void loadEditMap(string mapPath);
        void setupMovieRect(int w, int h);

        string mapPath;
        bool map;
        bool led;            
};

