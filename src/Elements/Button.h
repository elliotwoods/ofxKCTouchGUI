#pragma once
/*
 *  Button.h
 *  Kimchi and Chips' touch GUI
 *
 *  Created by Elliot Woods on 29/09/2010.
 *  Copyright 2010 Kimchi and Chips. All rights reserved.
 *
 */

#include "GUI_element.h"

//events
#include "Poco/BasicEvent.h"
using Poco::BasicEvent;


class Button : public GUI_element
{
public:
	Button(float x, float y, float w, float h, string caption, int iAction);
	Button(float x, float y, float w, float h, string caption);
	
	virtual void	draw();
	
	void        touchUp(Touch *_touch);
	void        touchDown(Touch *_touch);
	
	int				iAction;
	BasicEvent<int>	action;
	
	bool			enableDraw;
};