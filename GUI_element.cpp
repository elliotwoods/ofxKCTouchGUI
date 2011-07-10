/*
 *  GUI_element.cpp
 *  Kimchi and Chips' touch GUI
 *
 *  Created by Elliot Woods on 22/07/2010.
 *  Copyright 2010 Kimchi and Chips. All rights reserved.
 *
 */

#include "GUI_element.h"

GUI_element::GUI_element(float x, float y, float w, float h)
{
	nudgeInterface();
    bounds.x = x;
    bounds.y = y;
    bounds.width = w;
    bounds.height = h;
	
	enabled = true;
	
	//setup some blank touches
	for (int iTouch=0; iTouch<MAX_TOUCHES; iTouch++)
		_Touches[iTouch].ID = iTouch;
	_nTouchesDown = 0;
}

ofPoint GUI_element::transformTouch(ofPoint touch)
{
	return ofPoint(ofMap(touch.x,
                         bounds.x, bounds.x+bounds.width,
                         -1, 1,
                         true),
				   ofMap(touch.y,
                         bounds.y, bounds.y+bounds.height,
                         -1, 1,
                         true));
}

bool GUI_element::isHit(Touch *_touch)
{
	bool output =	(_touch->x >= bounds.x) &&
                    (_touch->y >= bounds.y) &&
					(_touch->x <= bounds.x + bounds.width) &&
                    (_touch->y <= bounds.y + bounds.height);
	
	output &= enabled;
	
	if (output)
		nudgeInterface();
	
	return output;
}

void GUI_element::draw()
{
	if (ofGetElapsedTimef()-_lastTouch < GUI_OUTLINE_DECAY)
	{
		ofPushStyle();
		ofSetLineWidth(2);
		ofEnableAlphaBlending();
		ofSetColor(255, 255, 255, ofMap(ofGetElapsedTimef()-_lastTouch, 0, GUI_OUTLINE_DECAY, 255, 0, true));
		ofNoFill();
		
		ofRect(bounds);
		
		ofPopStyle();
	}
    
    bool isDown = _nTouchesDown > 0;
	
	float fcol = (isDown ? 255 : 50);
	float lcol = (isDown ? 0 : 255);
	
	ofPushStyle();
	
	//fill
	ofSetColor(fcol, fcol, fcol, 200);
	ofFill();
	ofSetLineWidth(0);
	ofRect(bounds);
	
	//outline
	ofNoFill();
	ofSetColor(lcol, lcol, lcol, 255);
	ofSetLineWidth(2);
	ofRect(bounds);
	
	ofPopStyle();
}

void GUI_element::nudgeInterface()
{
	_lastTouch = ofGetElapsedTimef();
}

void GUI_element::touchDown(Touch *_touch)
{
	_Touches[_touch->ID].isDown = true;
	_downTouches[_nTouchesDown++] = &_Touches[_touch->ID];
	countTouches();
	
	_Touches[_touch->ID].setXY(_touch->x, _touch->y);
	
	nudgeInterface();
}

void GUI_element::touchUp(Touch *_touch)
{
	_Touches[_touch->ID].isDown=false;
	countTouches();
}

void GUI_element::touchMoved(Touch *_touch)
{
	if (_Touches[_touch->ID].isDown)
		nudgeInterface();
	
	_Touches[_touch->ID].moveXY(_touch->x, _touch->y);
	
}

void GUI_element::countTouches()
{
	_nTouchesDown=0;
	
	for (int i=0; i<MAX_TOUCHES; i++)
		if (_Touches[i].isDown)
			_downTouches[_nTouchesDown++] = &_Touches[i];
}

ofRectangle GUI_element::getBounds() const
{
    return bounds;
}

void GUI_element::setBounds(ofRectangle& rect)
{
    bounds = rect;
    boundsChanged();
}

void GUI_element::setPosition(ofPoint& point)
{
    bounds.x = point.x;
    bounds.y = point.y;
    boundsChanged();
}

string GUI_element::getCaption() const
{
    return caption;
}