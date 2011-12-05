#include "effectSceneShout.h"
#include "testApp.h"

#define EFFECTSCENE_WIDTH 1024
#define EFFECTSCENE_HEIGHT 768

EffectSceneShout *EffectSceneShout::instance = NULL;
//---------------------------------------------------

void EffectSceneShout::setup(){
    instance = this;
    effect_texture.allocate(1920,1080,GL_RGB);
    effect_image.allocate(1920,1080, OF_IMAGE_COLOR_ALPHA);
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
        shouts[channel].x = 500;
        shouts[channel].y = 500;
        cout << "EFFECTON" << std::endl;
        for (int i=0; i<shouts.size(); i++) {
            shout_timer[i] = ofGetElapsedTimef()+5.0f;
        }
    }
    if (effectControl == EFFECTOFF) {
        shout_timer[channel] = 0;
    }
    if (effectControl == EFFECTONCE)  {
        shouts[channel].x = 500;
        shouts[channel].y = 500;
    }
}

unsigned char* EffectSceneShout::getPixels()
{
    return effect_image.getPixels();
}


ofColor EffectSceneShout::getColor(int x, int y)
{
    if (x ==0 && y ==0) return ofColor(0,0,0);

    y = 1080 - y;
    unsigned char* pixels = getPixels();
    unsigned char r = pixels[(x+y*1920)*3];
    unsigned char g = pixels[(x+y*1920)*3+1];
    unsigned char b = pixels[(x+y*1920)*3+2];
    //cout << hex << r << std::endl;

    return ofColor(r,g,b);
}


//---------------------------------------------------
void EffectSceneShout::update(){
    for (int i=0; i < shout_timer.size(); i++) {
        if ( shout_timer[i] < ofGetElapsedTimef()) {
            // shouts[i].x=0; shouts[i].y=0; // TODO: change to hide.
        }
    }
    // effect_texture = effect_image.getTextureReference();
	// effect_texture.loadScreenData(1024,0,1920,768);
	effect_texture.loadScreenData(0,0,1920,1080);
    effect_texture.readToPixels(effect_image.getPixelsRef());
    effect_image.update();
}


//---------------------------------------------------

void EffectSceneShout::draw(float alpha){
    ofPushMatrix();
    ofTranslate(0,0,0);

    ofPushStyle();
    ofFill();
  	ofSetColor(255,255,0);
    for (int i=0; i<shouts.size(); i++) {
        int x = shouts[i].x * EFFECTSCENE_WIDTH;
        int y = shouts[i].y * EFFECTSCENE_HEIGHT;
        // if ((int(ofGetFrameRate()) % 4) == 0) {
        if ( shout_timer[i] < ofGetElapsedTimef()) {            
            ofSetColor(255,255,255,0);
        } else {
            ofSetColor(200,0,255);
            ofCircle(x+ofRandom(10),y+ofRandom(10),80);
            ofCircle(x+ofRandom(10),y+ofRandom(10),80);
            ofCircle(x+ofRandom(10),y+ofRandom(10),80);
        }
    }
    ofPopStyle();    
    ofPopMatrix();
    
    // effect_texture.draw(1024,768);
    // effect_image.draw(1024,768);

    /*
    ofPushMatrix();
    ofTranslate(1024,0);
    ofSetRectMode(OF_RECTMODE_CORNER);
    
    ofColor c;
    for (int x1=0; x1< 1024; x1=x1+10) {
        for (int y1=0 ;y1<1080; y1=y1+10) {
            c=getColor(x1, y1);
            ofPushStyle();
            ofSetColor(c);            
            ofFill();
            ofRect(x1,y1,10,10);
            ofPopStyle();            
        }
    }
    ofPopMatrix();
    */

    
    // ofPushMatrix();
    // ofTranslate(1024,768,0);

    // ofPushStyle();
    // // // ofSetColor(255);
    // ofColor c;
    // for (int x1=0; x1< 1024; x1=x1+1) {
    //     for (int y1=0 ;y1<768; y1=y1+1) {
    //         c=effect_image.getColor(1024+x1, y1);
    //         ofSetColor(255,255,255);            
    //         ofFill();
    //         ofRect(x1,y1,80,80);
    //     }
    // }
    
    // ofPopStyle();
    // ofPopMatrix();
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
