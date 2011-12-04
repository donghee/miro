#include "setting.h"

Setting::Setting()
{
    //ctor
}

Setting::~Setting()
{
    //dtor
}

vector <EsignColumn> Setting::loadColumns(int fixtureId, int portId)
{
    string xmlFileName = getXmlFileName(fixtureId, portId);    
    vector <EsignColumn> EsignColumns;
        
    // XML
    if( XML.loadFile(xmlFileName) ){
		message = xmlFileName + " loaded!";
	} else {
		message = "unable to load " + xmlFileName + " check data/ folder";
	}
    cout << message << std::endl;

	int numberOfColumns = XML.getNumTags("COLUMN");
	// int numberOfPorts = XML.getNumTags("PORT");    

    for(int i = 0; i < numberOfColumns; i++){
        //the last argument of getValue can be used to specify
        //which tag out of multiple tags you are refering to.
        int x = XML.getValue("COLUMN:X", 0, i);
        int y = XML.getValue("COLUMN:Y", 0, i);
        int size = XML.getValue("COLUMN:SIZE", 0, i);
        int red = XML.getValue("COLUMN:RED",255,i);
        int green = XML.getValue("COLUMN:GREEN",255,i);
        int blue = XML.getValue("COLUMN:BLUE",255,i);
        bool direction = XML.getValue("COLUMN:DIRECTION",true,i);
        int topChannel = XML.getValue("COLUMN:TOPCHANNEL",0,i);
        EsignColumn column;
        column.setup(x,y,size,1);
        column.setPosition(x,y);
        column.setColor(red,green,blue);
        column.setTopChannel(topChannel);
        EsignColumns.push_back(column);
    }
    
    return EsignColumns;
}

void Setting::saveColumns(int fixtureId, int portId , const vector <EsignColumn>& EsignColumns)
{
    cout << "Column size: ";
    cout << ofToString(EsignColumns.size()) <<std::endl;

    string xmlFileName = getXmlFileName(fixtureId, portId);

    // XML
    if( XML.loadFile(xmlFileName) ){
		message = xmlFileName+ " loaded!";
	} else {
		message = "Unable to load " + xmlFileName + " check data/ folder";
	}
    
    XML.clear();
    cout << xmlFileName << std::endl;
        
    for (int i=0; i < EsignColumns.size(); i++) {
        EsignColumn e = EsignColumns[i];
        XML.addTag("COLUMN");
        XML.setValue("COLUMN:ID", i, i);
        XML.setValue("COLUMN:TOPCHANNEL", e.getTopChannel(), i);        
        XML.setValue("COLUMN:SIZE", e.getSize(), i);
        XML.setValue("COLUMN:X", e.getX(), i);
        XML.setValue("COLUMN:Y", e.getY(), i);
        XML.setValue("COLUMN:DIRECTION", e.getDirection(), i); // upward.
        XML.setValue("COLUMN:RED", e.getColor().r, i );
        XML.setValue("COLUMN:GREEN", e.getColor().g, i );
        XML.setValue("COLUMN:BLUE", e.getColor().b, i );
    }
    XML.saveFile(xmlFileName);
}


string Setting::getXmlFileName(int fixtureId, int portId)
{
    return string("column_fixture"+ofToString(fixtureId)+"_port"+ofToString(portId)+".xml");
}
