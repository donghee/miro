#include "controlGui.h"


void ControlGui::setup() {
    hGui * gui = hGui::getInstance();

    // gui->setup("fonts/frabk.ttf", 15); // In each version of OF there is another font that looks better ...
    gui->setup("fonts/DIN.otf", 15); // In each version of OF there is another font that looks better ...
    int gui_width = 400;
    int gui_height = 400;

    int xx= gui->margin1;
    int yy= 768 + gui->margin1;

    // Main Panel
	hPanel * mainPanel =
        gui->addPanel("mainPanel", NULL, HGUI_ABSOLUTE_POSITION, xx, yy, gui_width, gui_height, true);

	mainPanel->setVisibleBackground(true);
	gui->setRootWidget(mainPanel);

	gui->addListeners();

    hEvents * events = hEvents::getInstance();

	events->setup();
	events->addObject("ControlGui", this);

    hLabel * fixtureLabel = gui->addLabel("", mainPanel, HGUI_TOP_LEFT, gui->margin2, 5, "Fixture");
    fixtureButtonBox = gui->addButtonBox("fixtureButtonBox", mainPanel, HGUI_NEXT_ROW, gui->margin2, gui->margin2, 32, 20);
    fixtureButtonBox->displayIndexes(true);
    fixtureButtonBox->addItems(9, 1);
  	fixtureButtonBox->selectItem(1); // preselect an item (first item is 1)
  	events->addListener("setFixtureFromGui", this, &ControlGui::setFixtureFromGui);
  	fixtureButtonBox->setMessage("ControlGui.setFixtureFromGui");

    hLabel * portLabel = gui->addLabel("", mainPanel, HGUI_NEXT_ROW,
                                       gui->margin2, 5, "Port: Set Key (1-8)");
    portButtonBox = gui->addButtonBox("portButtonBox", mainPanel, HGUI_NEXT_ROW, gui->margin2, gui->margin2, 32, 20);
    portButtonBox->displayIndexes(true);
    portButtonBox->addItems(8, 1);
  	portButtonBox->selectItem(1); // preselect an item (first item is 1)
  	events->addListener("setPortFromGui", this, &ControlGui::setPortFromGui);
  	portButtonBox->setMessage("ControlGui.setPortFromGui");


    hLabel * ledLabel = gui->addLabel("", mainPanel, HGUI_NEXT_ROW, gui->margin2, 5, "LED Size");
    ledButtonBox = gui->addButtonBox("ledButtonBox", mainPanel, HGUI_NEXT_ROW, gui->margin2, gui->margin2, 32, 20);
    ledButtonBox->displayIndexes(true);
    ledButtonBox->addItems(10, 1);
  	ledButtonBox->selectItem(1); // preselect an item (first item is 1)
  	events->addListener("setLEDNumFromGui", this, &ControlGui::setLEDNumFromGui);
  	ledButtonBox->setMessage("ControlGui.setLEDNumFromGui");
        
    hLabel * directionLabel = gui->addLabel("", mainPanel, HGUI_NEXT_ROW,
    gui->margin2, 5, "Direction: Set Key (Q,W)");        
    upCheckBox = gui->addCheckBox("upCheckBox", mainPanel, HGUI_NEXT_ROW, gui->margin2, gui->margin1);
    upCheckBox->setRadioEnabled(true);
    upCheckBox->setSelected(true);
    upCheckBox->setSelectColor(0xFF0000);
    hLabel * label0 = gui->addLabel("", mainPanel, HGUI_RIGHT, gui->margin2 ,0, "UP");

    bottomCheckBox = gui->addCheckBox("bottomCheckBox", mainPanel, HGUI_RIGHT, gui->margin3, 0);
    bottomCheckBox->setRadioEnabled(true);
    bottomCheckBox->setSelectColor(0x00FF00);
    hLabel * label1 = gui->addLabel("", mainPanel, HGUI_RIGHT, gui->margin2 ,0, "DOWN");


    upCheckBox->setMessage("ControlGui.selectItem");
	bottomCheckBox->setMessage("ControlGui.selectItem");

	upCheckBox->setIndex(1);
	bottomCheckBox->setIndex(2);


	mainPanel->adaptPanelSize(gui->margin2, gui->margin2);

        ////

    // Edit Panel
	hPanel * editPanel =
        gui->addPanel("editPanel", NULL, HGUI_ABSOLUTE_POSITION, xx+500, yy, gui_width, gui_height, true);

	editPanel->setVisibleBackground(true);
    hLabel * editLabel = gui->addLabel("", editPanel, HGUI_NEXT_COL, gui->margin2, 5, "Fixture");
    editPanel->adaptPanelSize(gui->margin2, gui->margin2);
	//gui->setRootWidget(editPanel);

        

	gui->loadSettings("settings.xml");

    setDarkColors();
}

// -------------------------------------------------------------------------------------

void ControlGui::exit()
{
	hGui * gui = hGui::getInstance();
	gui->saveSettings("settings.xml");
}

//--------------------------------------------------------------
//					Methods called by widgets
//					(using prototypes defined in hObject.h)
//--------------------------------------------------------------

void ControlGui::start(void){
	myString = "start";
}

void ControlGui::stop(void){
	myString = "stop";
}

void ControlGui::clear(void){
	myString = "";
}

void ControlGui::setLedColor(int* red, int* green,int* blue)
{
    // 조도, 채도, 수정
	//slider1->setIntVar(red);
	//slider2->setIntVar(green);
	//slider3->setIntVar(blue);
}

void ControlGui::setPortInfo(int* fixtureNumber_ref,int* portNumber_ref,int* columnLEDNumber_ref ,bool* direction_ref)
{
    fixtureNumber = fixtureNumber_ref;
    portNumber = portNumber_ref;
    columnLEDNumber = columnLEDNumber_ref;
    direction = direction_ref;

//    fixtureButtonBox- >selectItem(*fixtureNumber);
//    portButtonBox->selectItem(*portNumber);
    ledButtonBox->selectItem(8);

}

//--------------------------------------------------------------

void ControlGui::selectItem(int item)
{
	switch(item){
        case 1:
            (*direction) = UP;
                upCheckBox->setSelected(true);                
        break;
        case 2:
            (*direction) = DOWN;
                bottomCheckBox->setSelected(true);                                
        break;
	}
}

//--------------------------------------------------------------
					// Example of custom listener
//--------------------------------------------------------------
void ControlGui::setFixtureFromGui(hEventArgs& args)
{
    if(args.values.size() > 0) {
		hEvents * events = hEvents::getInstance(); // We need access to our event engine
        hObject * object = events->getObject(args.objectName);
		if(object == this) {

			hGui * gui = hGui::getInstance(); // We need access to our gui engine
			(*fixtureNumber) = (int)args.values[0];
			(*fixtureNumber) = (*fixtureNumber)-1;

		}
	}
}

void ControlGui::setPortFromGui(hEventArgs& args)
{
    if(args.values.size() > 0) {
		hEvents * events = hEvents::getInstance(); // We need access to our event engine
        hObject * object = events->getObject(args.objectName);
		if(object == this) {

			hGui * gui = hGui::getInstance(); // We need access to our gui engine

			 (*portNumber) = (int)args.values[0];
			 (*portNumber) =  (*portNumber)-1;

		}
	}
}

void ControlGui::setLEDNumFromGui(hEventArgs& args)
{
    if(args.values.size() > 0) {
		hEvents * events = hEvents::getInstance(); // We need access to our event engine
        hObject * object = events->getObject(args.objectName);
		if(object == this) {

			hGui * gui = hGui::getInstance(); // We need access to our gui engine

			(*columnLEDNumber) = (int)args.values[0];
		}
	}
}

//--------------------------------------------------------------

void ControlGui::setDarkColors(void)
// Example of changing the colors of the GUI
{
	hGui * gui = hGui::getInstance();

	gui->setBackgroundColor	(0x333333);
	gui->setBorderColor		(0xCCCCCC);
	gui->setFillColor		(0x555555);
	gui->setAltFillColor	(0x557766);
	gui->setButtonShadowColor(0x999999);

	gui->setScrollHandleColor(0xDDDDDD);
	gui->setScrollButtonColor(0xDDDDDD);
	gui->setTextColor		(0xFFFFFF);
	gui->setTextColor2		(0x000000);
	gui->setAlertTextColor	(0xCCCCCC);

	gui->setDisableColor	(0x999999);
	gui->setEditTextColor	(0x113388);
	gui->setEditTextColor2	(0x113388);
	gui->setEditBackColor	(0xCCDDEE);
	gui->setCaretColor		(0x000000);

	gui->setLabelSelColor	(0xBBBBFF);
	gui->setItemSelColor	(0xBBBBBB);
	gui->setItemSelTextColor(0x333333);
	gui->setTabBoxSelColor	(0x4477CC);
	gui->setButtonBoxSelColor(0x44CC77);

	gui->setCheckBoxColor	(0x44CC77);
	gui->setSliderColor		(0x999999);
	gui->setTwoDSliderColor	(0x33BB66);
	gui->setCounterColor	(0x33BB66);

	gui->setDialogColor		(0xE5E5E5);
	gui->setMessageBoxColor	(0x77FFAA);
	gui->setAlertColor		(0xFF7777);
}

//--------------------------------------------------------------

void ControlGui::update()
{
  	fixtureButtonBox->selectItem((*fixtureNumber)+1);
    portButtonBox->selectItem((*portNumber)+1);
    ledButtonBox->selectItem(*columnLEDNumber);
    if ((*direction) == UP) {
        selectItem(1); //UP DOWN
    } else {
        selectItem(2); //UP DOWN        
    }
    
    hEvents::getInstance()->sendEvent("statusBar.setLabel", "FPS: " + ofToString(ofGetFrameRate(), 2));
}

//--------------------------------------------------------------

void ControlGui::draw()
{
// the following variables are controlled by widgets:
// backColor, drawFlag, xPct, yPct, myString



	ofBackground(red, green, blue);

	if(drawFlag == false) return;

	//------(c)--------------------------------------
	// (from polygonExample)
	//       draw a star dynamically

	int nTips = 5 + xPct * 60;
	int nStarPts = nTips * 2;
	float angleChangePerPt = TWO_PI / (float)nStarPts;
	float innerRadius = 0 + yPct*80;
	float outerRadius = 80;
	float origx = 525;
	float origy = 200;
	float angle = 0;

#if OF_VERSION < 7
	ofSetColor(0xa16bca);
#else
	ofSetHexColor(0xa16bca);
#endif

	ofBeginShape();
	for (int i = 0; i < nStarPts; i++){
		if (i % 2 == 0) {
			// inside point:
			float x = origx + innerRadius * cos(angle);
			float y = origy + innerRadius * sin(angle);
			ofVertex(x,y);
		} else {
			// outside point
			float x = origx + outerRadius * cos(angle);
			float y = origy + outerRadius * sin(angle);
			ofVertex(x,y);
		}
		angle += angleChangePerPt;
	}
	ofEndShape();

	//---------------------------------

	ofSetColor(0, 0, 0);
	font->drawString(myString, 440, 20);
}

//--------------------------------------------------------------
void ControlGui::keyPressed(int key){
    hGui * gui = hGui::getInstance();

    if (key==' ') gui->hide();
}

//--------------------------------------------------------------
void ControlGui::keyReleased(int key){

}

//--------------------------------------------------------------
void ControlGui::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ControlGui::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ControlGui::mousePressed(int x, int y, int button){
 	// cout << x << " " << y << endl;

}

//--------------------------------------------------------------
void ControlGui::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ControlGui::windowResized(int w, int h){

}
