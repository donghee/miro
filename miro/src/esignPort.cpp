#include "esignPort.h"
#include "setting.h"


void EsignPort::bindColumnWithLed()
{
    //  loadEsignLeds()
    for (int i=0; i< EsignColumns.size(); i++){
        uint8_t r = EsignColumns[i].getColor().r;
        uint8_t g = EsignColumns[i].getColor().g;
        uint8_t b = EsignColumns[i].getColor().b;
        int x = EsignColumns[i].getX();
        int y = EsignColumns[i].getY();
        int size = EsignColumns[i].getSize();
        bool direction = EsignColumns[i].getDirection();        // top is ture

        
        for (int j=0; j < size; j++ ) {
            EsignLed e;
            e.setColor(r,g,b);

            if (direction == UP ) // if top, one brick has 2 led, so j/2 
            {
                e.setPosition(x,y,j/2);
            }
            else //if bottom
            {
                e.setPosition(x,y,((size-1)-j)/2);
            }                
            EsignLeds[(i*size)+j] =e;
        }
        EsignColumns[i].loadEsignLeds(&EsignLeds[(i*size)]);
    }
}

void EsignPort::setup(int _fixtureId, int _portId)
{
    fixtureId = _fixtureId;
    portId = _portId;

    EsignLeds = new EsignLed[CLUSTER_COUNT];  // 한 포트당 붙는 LED 갯수

    for (int i=0; i<CLUSTER_COUNT; i++)
    {
        EsignLed e;
        e.setColor(0,0,0);
        e.setX(0);  // DEFAULT 
        e.setY(0);
        EsignLeds[i] = e;
    }

    Setting config;
    EsignColumns = config.loadColumns(fixtureId,portId);
    bindColumnWithLed(); 
}

void EsignPort::draw()
{
    for(int i=0; i < EsignColumns.size(); i++) {
        ofColor borderColor = ofColor(255,portId*100,0);
        EsignColumns[i].draw(i,borderColor);
    }
}

//--------------------------------------------------------------
void EsignPort::saveColumns( )
{
    Setting config;
    config.saveColumns(fixtureId,portId,EsignColumns);
}

//--------------------------------------------------------------
void EsignPort::addColumn(int x, int y, int ledSize, bool direction)
{
    if (getBindedLedSize() + ledSize > CLUSTER_COUNT)
        {
            ofLog(OF_LOG_ERROR, "Can't add column, since leds over the cluster  counts.");
            return;
        }
    
    // eSignFixture
    // 메뉴에서 Fixture 와 ADD 를 선택했을때만 추가 되도록 한다.
    cout << "column added, size: ";
	EsignColumn es;
	es.setup(x,y,ledSize,direction);
    es.setColor(255,255,255);
    
    // set top channel
    if (direction == DOWN) {
        es.setTopChannel(getBindedLedSize());
    } else { // if UP
        es.setTopChannel(getBindedLedSize()+ledSize-1);
    }
    
    // TODO: 현재 등록된 컬럼의 LED 갯수를 세서 넘는지 않넘는지 안다.
    EsignColumns.push_back(es);
    cout << EsignColumns.size() << std::endl;
    // binding column and leds;
    bindColumnWithLed();
}

int EsignPort::getBindedLedSize()
{
    int ledCount = 0;
    for (int i=0; i< EsignColumns.size(); i++){
        ledCount += EsignColumns[i].getSize();
    }
    return ledCount;
}

EsignLed* EsignPort::getEsignLeds()
{
    return  EsignLeds;
}

void EsignPort::setColor(uint8_t r, uint8_t g, uint8_t b)
{
    for (int i=0; i < EsignColumns.size(); i++) {
        setColor(i,r,g,b);
    }
}

void EsignPort::setColor(int columnId, uint8_t r, uint8_t g, uint8_t b)
{
    if (columnId > EsignColumns.size()-1) { 
        throw domain_error("column Id is over in EsignColumns");
    }
    EsignColumns[columnId].setColor(r, g, b);
}
