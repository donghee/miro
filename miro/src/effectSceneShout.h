#pragma once

#include "ofMain.h"
#include "effectScene.h"
#include <vector>

using namespace std;

class EffectSceneShout:public EffectScene{
public:
    void setup();
    void addEffect(int channel, float x, float y);
    void setEffect(int channel, EffectType effect, EffectControlType effectControl);

    unsigned char* getPixels();
    ofColor getColor(int x, int y);
    
    void update();
    void draw(float alpha);
    void keyPressed(int key);
    void mouseMoved(int x,int y);
    void mouseDragged(int x,int y,int button);
    void mousePressed(int x,int y,int button);
    void mouseReleased(int x,int y,int button);
    void reset();
    ofVec2f screen2lores(ofVec2f in);
        
	ofImage loresScreen;
	unsigned char*pixels;

    ofTexture effect_texture;
    ofImage effect_image;
    
    vector <ofVec2f> shouts;
    vector <float> shout_timer;

    
    static EffectSceneShout* instance;
};
