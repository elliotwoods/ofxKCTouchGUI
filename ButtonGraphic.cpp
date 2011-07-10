/*
 *  ButtonGraphic.cpp
 *  DKO001 - iPad client
 *
 *  Created by Elliot Woods on 01/12/2010.
 *  Copyright 2010 Kimchi and Chips. All rights reserved.
 *
 */

#include "ButtonGraphic.h"

ButtonGraphic::ButtonGraphic(ofImage* _upState, ofImage* _downState,
							 float _x, float _y, float _iScreen,
							 int _iAction) :
Button(_x, _y, 100, 100, "")
{
	upState = _upState;
	downState = _downState;
	
	xoffset = ofGetScreenWidth()*_iScreen;
	
	//load width/height from images
    //if we don't have an up image, then
    //use the downimage
    //else just let Button(..) deal with it
	if (upState !=0)
	{
		bounds.width = upState->width;
		bounds.height = upState->height;
		
	} else if (downState != 0) {
		
		bounds.width = downState->width;
		bounds.height = downState->height;
	
	}
	
	iAction = _iAction;
}

void ButtonGraphic::draw()
{
	if (_nTouchesDown == 0)
	{
		if (upState != 0)
			upState->draw(bounds.x + xoffset,
                          bounds.y,
                          bounds.width,
                          bounds.height);
	
	} else if (downState != 0)
		downState->draw(bounds.x + xoffset,
                        bounds.y,
                        bounds.width,
                        bounds.height);
}