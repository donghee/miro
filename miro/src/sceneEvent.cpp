#include "sceneEvent.h"

SceneEvent *SceneEvent::instance = NULL;

SceneEvent::SceneEvent()
{
}

SceneEvent::~SceneEvent()
{
}

void SceneEvent::setup()
{
    // TUIO
	myTuio.connect(3333);
    // OSC for mic
	receiver.setup(9000);

    debug = false;

    for (int i =0 ; i < NUMBER_OF_SHOUT; i++) {
        mic_levels.push_back(0);
        shout_effect_controls.push_back(EFFECTOFF);        
    }
}

void SceneEvent::setDebug(bool on)
{
    debug = on;
}

void SceneEvent::bindScene(SceneType* scene_ref, SceneControlType* sceneControl_ref)
{
    scene = scene_ref;
    sceneControl = sceneControl_ref;
}

void SceneEvent::bindEffect(EffectType* effect_ref, EffectControlType* effectControl_ref)
{
    effect = effect_ref;
    effectControl = effectControl_ref;
}

void SceneEvent::bindMic(int& mic_id_ref, int& mic_level_ref)
{
    mic_id = mic_id_ref;
    mic_level = mic_level_ref;
}

int SceneEvent::getMicLevel(int mic_id)
{
    // vector로 주 수정.
    if (mic_id > mic_levels.size()) {
            throw domain_error("mic id over mic index");
     }
    return mic_levels[mic_id];
}
EffectControlType SceneEvent::getShoutEffectControl(int channel)
{
    if (channel > shout_effect_controls.size()) {
            throw domain_error("channel is over shouts");
     }
    return shout_effect_controls[channel];
}

list<TuioCursor*> SceneEvent::getTuioCursorList()
{
    return myTuio.client->getTuioCursors();
}

void SceneEvent::setScene(SceneType _scene, SceneControlType _sceneControl)
{
    // Out of bound of Scene
    if (_scene >= SceneType_End || _sceneControl >= SceneControlType_End) return;

    *scene = _scene;
    *sceneControl = _sceneControl;

    if (debug) {
        cout << "Scene: ";
        cout << (* scene) << std::endl;
        cout << "Scene control: ";
        cout << (* sceneControl) << std::endl;
    }
}

void SceneEvent::setShoutEffect(int micId, int micLevel, EffectControlType _effectControl)
{
    // Out of bound of Scene
    if (micId <0 || _effectControl >= EffectControlType_End) return;

        if (micId > mic_levels.size()) {
            throw domain_error("mic id over mic index");
        }
        mic_levels[micId] = micLevel;

        // vector로 주 수정.
        if (micId > shout_effect_controls.size()) {
            throw domain_error("mic id over mic index");
        }
        
        shout_effect_controls[micId] = _effectControl;
        
    if (debug) {
        cout << "Mic Id: ";
        cout << micId << std::endl;
        cout << "Mic Level: ";
        cout << micLevel << std::endl;        
        cout << "Effect control: ";
        cout << _effectControl << std::endl;
    }
}


void SceneEvent::update()
{
    // Mic update
    while( receiver.hasWaitingMessages() )
	{
		ofxOscMessage m;
		receiver.getNextMessage( &m );
        cout << "Received OSC" << std::endl;
		// check for mouse moved message
		if ( m.getAddress() == "/effect/shout" )
		{
            setShoutEffect(
                           ofToInt(m.getArgAsString(0)),
                           ofToInt(m.getArgAsString(1)),
                           (EffectControlType)ofToInt(m.getArgAsString(2)));
		}

		if ( m.getAddress() == "/scene")
		{
            setScene((SceneType)ofToInt(m.getArgAsString(0)),
                     (SceneControlType)ofToInt(m.getArgAsString(1)));
		}

		// if ( m.getAddress() == "/effect")
		// {
		//     setEffect((EffectType)ofToInt(m.getArgAsString(0)),
        //               (EffectControlType)ofToInt(m.getArgAsString(1)));
		// }
	}
}

void SceneEvent::draw()
{
    ofPushStyle();
    ofPushMatrix();
    //effect canvas에 그림 그리기.
    ofTranslate(1024,0,0);
    drawTuioInfo();
    drawMicInfo();
    ofPopMatrix();
    ofPopStyle();
}

void SceneEvent::drawTuioInfo()
{
    ////////////////////
    int canvas_width = 1000;
    int canvas_height = 760;
    int x=0;
    int y=0;
    std::list<TuioCursor*> cursorList = getTuioCursorList();
	std::list<TuioCursor*>::iterator tit;
	myTuio.client->lockCursorList();
	for (tit=cursorList.begin(); tit != cursorList.end(); tit++) {
		TuioCursor * cur = (*tit);
		//if(tcur!=0){
			//TuioCursor cur = *tcur;
			glColor3f(0.0,0.0,0.0);
			ofEllipse(cur->getX()*canvas_width, cur->getY()*canvas_height, 10.0, 10.0);
			string str = "SessionId: "+ofToString((int)(cur->getSessionID()));
			ofDrawBitmapString(str, cur->getX()*canvas_width-10.0, cur->getY()*canvas_height+25.0);
			str = "CursorId: "+ofToString((int)(cur->getCursorID()));
			ofDrawBitmapString(str, cur->getX()*canvas_width-10.0, cur->getY()*canvas_height+40.0);

            //// Kinect X,Y
            x = cur->getX()*canvas_width;
            y = cur->getY()*canvas_height;

		//}
	}
	myTuio.client->unlockCursorList();

    ofDrawBitmapString("Kinect X:", 100, 90);
    ofDrawBitmapString( ofToString(x), 190, 90 );
    ofDrawBitmapString("Kinect Y:", 100, 110);
    ofDrawBitmapString( ofToString(y), 190, 110);

    ////////////////////
	//myTuio.drawCursors();
	///////////////////////
	myTuio.drawObjects();

	ofDrawBitmapString("Scene:", -200, 50);
    ofDrawBitmapString( ofToString((* scene)), -80, 50 );
    ofDrawBitmapString("Scene Control:", -200, 70);
    ofDrawBitmapString( ofToString((* sceneControl)), -80, 70 );


}

void SceneEvent::drawMicInfo()
{
    ofDrawBitmapString("Mic ID:", 100, 50);
    ofDrawBitmapString( ofToString(mic_id), 190, 50 );
    ofDrawBitmapString("Mic level:", 100, 70);
    ofDrawBitmapString( ofToString(mic_level), 190, 70 );

	ofDrawBitmapString("Effect:", 100, 130);
    ofDrawBitmapString( ofToString((* effect)), 190, 130 );
    ofDrawBitmapString("E..Control:", 100, 150);
    ofDrawBitmapString( ofToString((* effectControl)), 190, 150);

}
