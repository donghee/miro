#pragma once

#include "ofMain.h"
#include "ofxTuioClient.h"
#include "ofxOsc.h"
#include "sceneManager.h"

#define NUMBER_OF_SHOUT 5

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
        void bindMic(int& mic_id_ref, int& mic_level_ref); // TODO change mic ref to mic list.

		void drawTuioInfo();
		void drawMicInfo();

        int getMicLevel(int mic_id);
         EffectControlType getShoutEffectControl(int channel);

        list<TuioCursor*> getTuioCursorList();

        void setDebug(bool on);
        
    protected:
    private:
        ofxTuioClient myTuio;
        ofxOscReceiver	receiver;

        // binding value
        int mic_id;
        int mic_level;

        vector <int> mic_levels;
        vector <EffectControlType> shout_effect_controls;
        
        SceneType* scene;
        SceneControlType* sceneControl;
        EffectType* effect;
        EffectControlType* effectControl;

        bool debug;

        void setScene(SceneType _scene, SceneControlType _sceneControl);
         /* void setEffect(EffectType _effect, EffectControlType _effectControl); */
         void setShoutEffect(int micId, int micLevel, EffectControlType
                             _effectControl);

         static SceneEvent* instance;                     
};
