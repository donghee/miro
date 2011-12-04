#ifndef MOVIESCENE_H
#define MOVIESCENE_H

#include "ofMain.h"

class MovieScene
{
    public:
        MovieScene();
        virtual ~MovieScene();

		void setup(string movieFile);
		void update();
		void draw();
		ofColor getColor(int x, int y);
        unsigned char* getPixels();
        ofTexture& getTextureReference();

        void play(ofLoopType state);
        void stop();
        void setPaused(bool bPause);

    protected:
    private:
        ofVideoPlayer   movie;
};

#endif // MOVIESCENE_H
