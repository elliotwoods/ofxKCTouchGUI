#pragma once
/*
 *  QuestionBox.h
 *  Kimchi and Chips' touch GUI
 *
 *  Created by Elliot Woods on 29/09/2010.
 *  Copyright 2010 Kimchi and Chips. All rights reserved.
 *
 */

#include "GUI_element.h"
#include "Button.h"

//events
#include "Poco/BasicEvent.h"
#include "Poco/Delegate.h"
using Poco::BasicEvent;
using Poco::Delegate;

#define ARROW_SIZE 10
#define PADDING 5
#define OPTION_HEIGHT 75
#define OPTION_WIDTH 200

class QuestionBox : public GUI_element, public ofBaseApp
{
public:
	QuestionBox();
	void	draw();
	void	update();
	
	void	clear();
	void	setWith(vector<string> options);
	ofEvent<int>	action;
	
	void        touchUp(Touch *_touch);
	void        touchDown(Touch *_touch);
	
	void		setTarget(ofPoint targetXY);
	
protected:
	void	drawShape();
	void	button_hit(const void* pSender, int &iAction);
	
	vector<Button*>	buttons;
	
	ofPoint			_targetXY;
	int				_arrowPosition; //=0 top, 1=bottom
	
};