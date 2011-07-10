/*
 *  Button.cpp
 *  Kimchi and Chips' touch GUI
 *
 *  Created by Elliot Woods on 29/09/2010.
 *  Copyright 2010 Kimchi and Chips. All rights reserved.
 *
 */

#include "Button.h"

Button::Button(float x, float y, float w, float h, string caption, int iAction) :
GUI_element(x, y, w, h)
{
	this->caption = caption;
	this->iAction = iAction;
	
	enableDraw = true;
}

Button::Button(float x, float y, float w, float h, string caption) :
GUI_element(x, y, w, h)
{
	this->caption = caption;
	this->iAction = 0;
	
	enableDraw = true;
}


void Button::draw()
{
	if (!enableDraw)
		return;
	
    GUI_element::draw();
    
	ofDrawBitmapString(caption, bounds.x + (bounds.width - 8*caption.length()) / 2, bounds.y + bounds.height/2);
}

void Button::touchUp(Touch *_touch)
{
	GUI_element::touchUp(_touch);
	
	if (isHit(_touch))
		action.notify(this,iAction);
}

void Button::touchDown(Touch *_touch)
{
	GUI_element::touchDown(_touch);
}
