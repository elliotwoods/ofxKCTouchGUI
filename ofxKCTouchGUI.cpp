/*
 *  ofxKCTouchGUI.cpp
 *  Kimchi and Chips' touch GUI
 *
 *  Created by Elliot Woods on 22/07/2010.
 *  Copyright 2010 Kimchi and Chips. All rights reserved.
 *
 */

#include "ofxKCTouchGUI.h"
#define FOREACH_GUI_ELEMENT for (int iGUIelement=0; iGUIelement< _vecGUIelements.size(); iGUIelement++)

ofxKCTouchGUI::~ofxKCTouchGUI()
{
    FOREACH_GUI_ELEMENT
        delete _vecGUIelements[iGUIelement];
}

ofxKCTouchGUI::ofxKCTouchGUI()
{
	nudgeInterface();
	__questionBox = &message;
	
	enableFPSCalming = true;
}

void ofxKCTouchGUI::update()
{
	if (!isSlow && ofGetElapsedTimef() - lastAction > GUI_HIGH_FPS_TIMEOUT && enableFPSCalming)
	{
		ofSetFrameRate(GUI_LOW_FPS);
		isSlow=true;
	}
	
	message.update();
	
    FOREACH_GUI_ELEMENT
        _vecGUIelements[iGUIelement]->update();    
}

void ofxKCTouchGUI::draw()
{
    FOREACH_GUI_ELEMENT
		if (_vecGUIelements[iGUIelement]->enabled)
			_vecGUIelements[iGUIelement]->draw();
	
	message.draw();

}

void ofxKCTouchGUI::touchDown(Touch *_touch)
{
	nudgeInterface();
	
	//question box gets priority
	if (message.isHit(_touch))
	{
		message.touchDown(_touch);
		return;
	} else {
		message.enabled=false;
	}

		
    for (int iGUIelement=_vecGUIelements.size()-1; iGUIelement >=0 ; iGUIelement--) {
        if (_vecGUIelements[iGUIelement]->isHit(_touch))
        {
            _vecGUIelements[iGUIelement]->touchDown(_touch);
			message.enabled=false;
            break;
        }
    }
    
}

void ofxKCTouchGUI::touchUp(Touch *_touch)
{
	nudgeInterface();
	
	if (message._Touches[_touch->ID].isDown)
		message.touchUp(_touch);
		
	FOREACH_GUI_ELEMENT
		if(_vecGUIelements[iGUIelement]->_Touches[_touch->ID].isDown)
			_vecGUIelements[iGUIelement]->touchUp(_touch);
    
}

void ofxKCTouchGUI::touchMoved(Touch *_touch)
{
	nudgeInterface();
	
	message.touchMoved(_touch);
	
	FOREACH_GUI_ELEMENT
	if(_vecGUIelements[iGUIelement]->_Touches[_touch->ID].isDown)
		_vecGUIelements[iGUIelement]->touchMoved(_touch);
    
}

void ofxKCTouchGUI::pushElement(GUI_element *element)
{
    _vecGUIelements.push_back(element);
}

void ofxKCTouchGUI::nudgeInterface()
{
	lastAction = ofGetElapsedTimef();

	if (isSlow)
		ofSetFrameRate(GUI_HIGH_FPS);
	
	isSlow=false;
}