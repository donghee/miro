#pragma once

#include "ofMain.h"
#include "sceneType.h"

#include "movieScene.h"
#include "effectScene.h"
#include "effectSceneShout.h"
/* #include "effectSceneKinect.h" */

class SceneManager
{
    public:
        void setup();
        bool sceneIsChanged(SceneType _scene, SceneControlType _sceneControl) ;

        void setScene(SceneType scene, SceneControlType sceneControl);
        void setEffect(EffectType effect, EffectControlType effectControl);
        void setShoutEffect(int mic_id, int mic_level, EffectControlType _effectControl);
            
        void addScene(SceneType _scene, string movieFile);

        ofRectangle getMovieRect();
        ofRectangle getEffectRect();

        MovieScene* getScene();
        EffectScene* getEffect();            

        void update(SceneType scene, SceneControlType sceneControl, EffectType effect, EffectControlType effectControl);
        void draw();

        unsigned char * getScenePixels();
        unsigned char * getEffectPixels();
    private:

        SceneType currentScene;
        SceneControlType currentSceneControl;

        MovieScene* currentMovieScene;
        EffectScene* currentEffectScene;

        /* EffectType currentEffect; */
        /* EffectControlType currentEffectControl; */

        ofRectangle movieRect;
        ofRectangle effectRect;

        MovieScene intro;
        MovieScene moviea;
        MovieScene movieb;
        MovieScene outro;

        EffectScene* shout;

        SceneType scene;
        SceneControlType sceneControl;
        SceneType beforeScene;
        SceneControlType beforeSceneControl;

        EffectType effect;
        EffectControlType effectControl;
};

