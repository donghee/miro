#ifndef SUBSCENE_H
#define SUBSCENE_H

#include "ofMain.h"
#include "particle.h"

class SubScene
{
    public:
        SubScene();
        virtual ~SubScene();
        void setup();
        void draw();
    protected:
    private:
        vector <Particle> particles;

        int mic_id;
        int mic_level;
};

#endif // SUBSCENE_H
