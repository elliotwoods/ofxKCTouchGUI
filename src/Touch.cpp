/*
 *  Touch.cpp
 *  Kimchi and Chips' touch GUI
 *
 *  Created by Elliot Woods on 22/07/2010.
 *  Copyright 2010 Kimchi and Chips. All rights reserved.
 *
 */

#include "Touch.h"



Touch::Touch()
{
	x=0;
	y=0;
	isDown=false;
}

void Touch::draw()
{
	if (isDown)
	{
		ofPushStyle();
		ofNoFill();
		ofSetLineWidth(2);
		ofEnableSmoothing();
		
		unsigned char charColour = 	ofGetElapsedTimeMillis()/10;
		charColour += 128;
		
		ofSetColor(charColour,charColour,charColour);
		
		ofCircle(x, y, TOUCH_RADIUS);
		ofCircle(x, y, 2);
		
		ofPopStyle();
		
		ofDrawBitmapString(ofToString(ID, 0), x-TOUCH_RADIUS, y-TOUCH_RADIUS);
	}
}

ofPoint Touch::getOfPoint()
{
	return ofPoint(x,y);
}

void Touch::setXY(float _x, float _y)
{
    dx = 0;
    dy = 0;
    x=_x;
    y=_y;
	
	_hasMoved=false;
	_timeBorn=ofGetElapsedTimef();
}

void Touch::moveXY(float _x, float _y)
{
    dx = _x-x;
    dy = _y-y;
    x=_x;
    y=_y;
	
	_hasMoved=true;
}

float Touch::getLifetime()
{
	return ofGetElapsedTimef() - _timeBorn;
}

float Touch::lastx()
{
	return x - dx;
}

float Touch::lasty()
{
	return y - dy;
}