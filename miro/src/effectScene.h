#pragma once
#include "ofMain.h"
#include "sceneType.h"

class EffectScene {
 public:
    virtual void setup();
    virtual void update();
    virtual void addEffect(int channel, float x, float y);
    virtual void setEffect(int channel, EffectType effect, EffectControlType effectControl);

    virtual ofColor getColor(int x, int y);
    virtual void draw(float alpha);
    virtual void keyPressed(int key);
    virtual void mouseMoved(int x, int y);
    virtual void mouseDragged(int x, int y, int button);
    virtual void mousePressed(int x, int y, int button);
    virtual void mouseReleased(int x, int y, int button);    
    virtual void reset();
};
