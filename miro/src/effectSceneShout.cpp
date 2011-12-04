#include "effectSceneShout.h"
#include "testApp.h"

#define EFFECTSCENE_WIDTH 1024
#define EFFECTSCENE_HEIGHT 768

EffectSceneShout *EffectSceneShout::instance = NULL;
//---------------------------------------------------

void EffectSceneShout::setup(){
    instance = this;
}

//---------------------------------------------------
void EffectSceneShout::addEffect(int channel, float x, float y) {
    shouts.push_back(ofVec2f(x,y));
    shout_timer.push_back(ofGetElapsedTimef()+5.0f);
}

//---------------------------------------------------
void EffectSceneShout::setEffect(int channel, EffectType effect, EffectControlType effectControl) {
    if (channel > shout_timer.size())
        throw domain_error("out of bound in shout timer");

    if (effectControl == EFFECTON) {
        shout_timer[channel] = 1000;
        shouts[channel].x = 100;
        shouts[channel].y = 100;        
    }
    if (effectControl == EFFECTOFF) {
        shout_timer[channel] = 0;
    }
    if (effectControl == EFFECTONCE) 
        shout_timer[channel] = ofGetElapsedTimef() + 5.0f;
}

//---------------------------------------------------
void EffectSceneShout::update(){
    for (int i=0; i < shout_timer.size(); i++) {
        if ( shout_timer[i] < ofGetElapsedTimef()) {
            shouts[i].x=0; shouts[i].y=0; // TODO: change to hide.
        }
    }
}

//---------------------------------------------------

void EffectSceneShout::draw(float alpha){

    ofPushMatrix();
    ofTranslate(1024,0,0);
    
	// ofBackground(0,0,0);
    ofSetRectMode(OF_RECTMODE_CORNER);
	ofSetColor(255,255,255,alpha*255);
    ofFill();

    for (int i=0; i<shouts.size(); i++) {
        int x = shouts[i].x * EFFECTSCENE_WIDTH;
        int y = shouts[i].y * EFFECTSCENE_HEIGHT;        
        ofCircle(x+ofRandom(10),y+ofRandom(10),10);
        ofCircle(x+ofRandom(10),y+ofRandom(10),10);
        ofCircle(x+ofRandom(10),y+ofRandom(10),10);
    }

	// ofScale(RESOLUTION_RATIO,RESOLUTION_RATIO , 1);
	// loresScreen.draw(0,0);
    ofPopMatrix();
}

//---------------------------------------------------

void EffectSceneShout::keyPressed(int key){
    
}

//---------------------------------------------------

void EffectSceneShout::mouseMoved(int x,int y){
    
}

//---------------------------------------------------

void EffectSceneShout::mouseDragged(int x,int y,int button){
}

//---------------------------------------------------

void EffectSceneShout::mousePressed(int x,int y,int button){
}

//---------------------------------------------------

void EffectSceneShout::mouseReleased(int x,int y,int button){
    
}

//---------------------------------------------------

void EffectSceneShout::reset(){
}


//--------------------------------------------------------------
ofVec2f EffectSceneShout::screen2lores(ofVec2f in){
	ofVec2f out;
	// out.x = in.x / RESOLUTION_RATIO;
	// out.y = in.y / RESOLUTION_RATIO;
	return out;
}
