#include "subscene.h"

ofTexture wallTexture;
ofImage wallImage;

SubScene::SubScene()
{
    //ctor
}

SubScene::~SubScene()
{
    //dtor
}

void SubScene::setup()
{
    // subscene.update();
    if (particles.size() < mic_level*40) {
        Particle newParticle;
        newParticle.setup();
        newParticle.p.set(ofGetWidth()/2,ofGetHeight()/2,0);
        particles.push_back(newParticle);
    }

    for (int i=0; i< particles.size(); i++) {
        particles[i].update();
    }

    particles.erase(particles.begin(), partition(particles.begin(), particles.end(), Particle::removeMe));


    wallTexture.allocate(1024,768,GL_RGB);
    wallImage.allocate(1024,768, OF_IMAGE_COLOR_ALPHA);
}


void SubScene::draw()
{

    // subscene.draw()
    for(int i=0; i< particles.size(); i++) {
        particles[i].draw();
    }

    //mic_id=mic_level=0;

    //wallImage.getTextureReference();
    wallTexture.loadScreenData(0,0,1024,768);
    wallTexture.readToPixels(wallImage.getPixelsRef());
    wallImage.update();

    ofPushStyle();
    ofSetColor(5);
    ofColor c;
    for (int x1=0; x1< 1024; x1=x1+80) {
        for (int y1=0 ;y1<768; y1=y1+80) {
            c=wallImage.getColor(x1+40, y1+40);
            ofPushStyle();
             ofSetColor(c);
            ofRect(x1,y1,80,80);
            ofPopStyle();
        }
    }

    ofPopStyle();
}
