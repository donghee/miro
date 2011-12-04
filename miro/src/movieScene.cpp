#include "movieScene.h"

MovieScene::MovieScene()
{
}

MovieScene::~MovieScene()
{
    movie.close();
}


void MovieScene::setup(string movieFile)
{
    if (movieFile.empty()) { // TODO path가 없으면 으로 바꾸기
        cout << "Movie file not founded" << std::endl;
        return;
    }
    movie.loadMovie(movieFile);
    play(OF_LOOP_NORMAL);
}

void MovieScene::play(ofLoopType state)
{
    movie.setLoopState(state);
    movie.play();
    movie.setPosition(0);
}

void MovieScene::stop()
{
    movie.stop();
}

void MovieScene::setPaused(bool bPause)
{
    movie.setPaused(bPause);
}

void MovieScene::update()
{
    movie.idleMovie();
}

ofColor MovieScene::getColor(int x, int y)
{
    if (x ==0 && y ==0) return ofColor(0,0,0);

    unsigned char* pixels = getPixels();
    unsigned char r = pixels[(x+y*1024)*3];
    unsigned char g = pixels[(x+y*1024)*3+1];
    unsigned char b = pixels[(x+y*1024)*3+2];
    //cout << hex << r << std::endl;

    return ofColor(r,g,b);
}

unsigned char* MovieScene::getPixels()
{
    return movie.getPixels();
}

ofTexture& MovieScene::getTextureReference()
{
    return movie.getTextureReference();
}

void MovieScene::draw()
{

    ofPushStyle();
    movie.draw(0,0);

    // default rect
    ofSetColor(0,0,0);
    ofFill();
    ofRect(0,0, 10,10);

    ofPopStyle();
}
