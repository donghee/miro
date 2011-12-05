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

/*
unsigned char* EffectSceneShout::getPixels()
{
    return img.getPixels();
}


ofColor EffectSceneShout::getColor(int x, int y)
{
    if (x ==0 && y ==0) return ofColor(0,0,0);

    unsigned char* pixels = getPixels();
    unsigned char r = pixels[(x+y*1024)*3];
    unsigned char g = pixels[(x+y*1024)*3+1];
    unsigned char b = pixels[(x+y*1024)*3+2];
    //cout << hex << r << std::endl;

    return ofColor(r,g,b);
}
*/


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

  
    /*
     .h
     ofTexture effect_canvas;
     ofImage effect_img;

     // setup
     effect_canvas.allocate(1024,768,GL_RGB);
     effect_image.allocate(1024,768, OF_IMAGE_COLOR_ALPHA);
     
     //draw
     effect_canvas = effect_image.getTextureReference();
     effect_canvas.loadScreenData(0,0,1024,768);

    ofPushStyle();
    ofSetColor(5);
    ofColor c;
    for (int x1=0; x1< 1024; x1=x1+80) {
      for (int y1=0 ;y1<768; y1=y1+80) {
        c=effect_image.getColor(x1+40, y1+40);
        ofNoFill();
        if ((int)c.r > 0) {
        cout << "test" << std::endl;
        }
        ofRect(x1,y1,80,80);
      }
   }
 ofPopStyle();
 */

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
