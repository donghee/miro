#pragma once

#include "ofMain.h"
#include "sceneEvent.h"
#include "sceneManager.h"

#include "controlGui.h"
#include "movieScene.h"
#include "mazeLight.h"

#include <stdexcept>

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

     private:
        // Esign Led
        EsignLed* mazeLeds;
        MazeLight mazeLight;
        int fixtureNumber, portNumber, columnLEDNumber;
        bool direction;

        // Scene
        SceneEvent sceneEvent;
        ControlGui controlGui;

        SceneManager sceneManager;
        MovieScene* currentScene;

        // current Scene status
        SceneType scene;
        SceneControlType sceneControl;

        // current Effect status
        EffectType effect;
        EffectControlType effectControl;

        // VIDEO
        void controlGui_bind();

        static testApp* instance;            
};

