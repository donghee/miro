#pragma once

#include "ofMain.h"

#include "hEvents.h"
#include "hObject.h"
#include "hGui_all.h"

#include "esignColumn.h"

class ControlGui : public ofBaseApp, public hObject {
	public:
		void setup();
		void update();
		void exit();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);

	// Methods called by the event listeners:
        // (must have the same names, parameters and return value than the methods defined in "hObject.h")

	void start(void);
	void stop(void);
	void clear(void);

	void selectItem(int item);

	// Custom listener:
    void setColors(hEventArgs& args);
    void setFixtureFromGui(hEventArgs& args);
    void setPortFromGui(hEventArgs& args);
    void setLEDNumFromGui(hEventArgs& args);

	// GUI color customization example:
	void setDarkColors(void);
	void setLedColor(int* red, int* green,int* blue);
    void setPortInfo(int* fixtureNumber_ref,int* portNumber_ref,int* columnLEDNumber_ref, bool* direction_ref);


private:

	// Variables used by the widgets (linked to them) :
        bool mouseOnMovie;

        ofRectangle movieRect;
        int movieLEDNumber;
        int portLEDNumber;

        int* fixtureNumber;
        int* portNumber;
        int* columnLEDNumber;
        bool* direction;

	bool drawFlag;

	int red, green, blue;

	float xPct, yPct;

	int curTime;

// Other objects:

	ofTrueTypeFont * font;
	std::string myString;

    hButtonBox * fixtureButtonBox;
    hButtonBox * portButtonBox;
    hSlider * columnSlider;
    hButtonBox * ledButtonBox;
    hCheckBox * upCheckBox;
    hCheckBox * bottomCheckBox;

	hSlider*  slider1;
	hSlider*  slider2;
	hSlider*  slider3;

};

