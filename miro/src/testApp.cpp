#include "testApp.h"

#define DEFAULT_COLUMN_LED_NUMBER 8

testApp *testApp::instance = NULL;

void testApp::setup(){
    instance = this;
	ofSetVerticalSync(true);
	ofSetFrameRate(30);

    // Gui binding
    controlGui.setup();
    controlGui_bind();

    sceneManager.setup();
    mazeLight.setup();

    // Scene event binding
    sceneEvent.setup();
    sceneEvent.setDebug(true);
    sceneEvent.bindScene(&scene, &sceneControl);
    sceneEvent.bindEffect(&effect, &effectControl);
}

void testApp::controlGui_bind()
{
    // if test mode. manually set color
    controlGui.setLedColor(&mazeLight.red,&mazeLight.green,&mazeLight.blue);

    // Edit mode info
    controlGui.setPortInfo(&fixtureNumber, &portNumber, &columnLEDNumber,&direction);

    // init
    fixtureNumber = 0;
    portNumber = 0;
    columnLEDNumber = DEFAULT_COLUMN_LED_NUMBER;
    direction = true; // true is up.
}

void testApp::update(){
    sceneEvent.update();
    controlGui.update();
    sceneManager.update(scene, sceneControl, effect, effectControl);
    currentScene = sceneManager.getScene();
    // update effect, effectcontrol
    mazeLight.update();
}

void testApp::draw(){
    sceneManager.draw();
    mazeLight.setColor(*currentScene);
    // mazeLight.setColor(*currentEffect);
    mazeLight.draw();
    sceneEvent.draw();
}

void testApp::keyPressed(int key){
    if (key == 's') mazeLight.save();

    if (key == '1') portNumber = 0;
    if (key == '2') portNumber = 1;
    if (key == '3') portNumber = 2;
    if (key == '4') portNumber = 3;
    if (key == '5') portNumber = 4;
    if (key == '6') portNumber = 5;
    if (key == '7') portNumber = 6;
    if (key == '8') portNumber = 7;

    if (key == 'q') direction = UP;
    if (key == 'w') direction = DOWN;

    if (key == 'o') scene = INTRO;
    if (key == 'p') scene = MOVIEA;
    if (key == '[') scene = MOVIEB;
    if (key == ']') scene = OUTRO;

    if (key == 'j') sceneControl = SCENEPLAY;
    if (key == 'k') sceneControl = SCENEONCE;
    if (key == 'l') sceneControl = SCENESTOP;

    if (key == '.') mazeLight.showMap(true);
    if (key == ',') mazeLight.showMap(false);

    // 이벤트 발생할때 업데이트
    sceneManager.update(scene, sceneControl,effect,effectControl);
}

void testApp::keyReleased(int key){
}

void testApp::mouseMoved(int x, int y ){

}

void testApp::mouseDragged(int x, int y, int button){
 }

void testApp::mousePressed(int x, int y, int button){
    if (x < 1024 && y <768) {
        mazeLight.addLight(fixtureNumber,portNumber ,x,y,columnLEDNumber, direction);
        cout << "Fixture Number: ";
        cout << fixtureNumber << " Port Number: " << portNumber<< " LED Number: " << columnLEDNumber << std::endl;
    }
}


void testApp::mouseReleased(int x, int y, int button){

}

void testApp::windowResized(int w, int h){

}


void testApp::gotMessage(ofMessage msg){

}


void testApp::dragEvent(ofDragInfo dragInfo){

}
