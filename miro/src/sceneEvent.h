#pragma once

#include "ofMain.h"
#include "ofxTuioClient.h"
#include "ofxOsc.h"
#include "sceneManager.h"

class SceneEvent
{
    public:
        SceneEvent();
        virtual ~SceneEvent();

    	void setup();
		void update();
		void draw();

        void bindScene(SceneType* scene_ref, SceneControlType* sceneControl_ref);
        void bindEffect(EffectType* effect_ref, EffectControlType* effectControl_ref);

		void drawTuioInfo();
		void drawMicInfo();

        void setMic(int& mic_id_ref, int& mic_level_ref); // TODO change mic ref to mic list.
        int getMicLevel(int mic_id);

        list<TuioCursor*> getTuioCursorList();

        void setDebug(bool on);
    protected:
    private:
        ofxTuioClient myTuio;
        ofxOscReceiver	receiver;

        // binding value
        int mic_id;
        int mic_level;

        SceneType* scene;
        SceneControlType* sceneControl;
        EffectType* effect;
        EffectControlType* effectControl;

        bool debug;

        void setScene(SceneType _scene, SceneControlType _sceneControl);
        void setEffect(EffectType _effect, EffectControlType _effectControl);
};
