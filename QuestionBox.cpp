/*
 *  QuestionBox.cpp
 *  Kimchi and Chips' touch GUI
 *
 *  Created by Elliot Woods on 29/09/2010.
 *  Copyright 2010 Kimchi and Chips. All rights reserved.
 *
 */

#include "QuestionBox.h"

QuestionBox::QuestionBox() :
GUI_element(0,0,OPTION_WIDTH + 2*PADDING,200)
{
	enabled=false;
}

void QuestionBox::update()
{
}

void QuestionBox::draw()
{
	if (enabled)
	{
		//fill 
		ofPushStyle();
		ofFill();
		ofSetLineWidth(1);
		ofSetColor(50, 50, 50, 200);
		drawShape();
		ofPopStyle();
		
		//outline 
		ofPushStyle();
		ofNoFill();
		ofSetLineWidth(1);
		ofSetColor(255, 255, 255);
		drawShape();
		ofPopStyle();
		
		//draw buttons
		for (int iButton=0; iButton<buttons.size(); iButton++)
			buttons[iButton]->draw();
	}
	
}


void QuestionBox::drawShape()
{
	ofSetPolyMode(OF_POLY_WINDING_NONZERO);
	ofBeginShape();
	
	ofVertex(bounds.x, bounds.y);
	if (_arrowPosition==1)
	{
		ofVertex(bounds.x + bounds.width/2-ARROW_SIZE, bounds.y);
		ofVertex(bounds.x + bounds.width/2, bounds.y-ARROW_SIZE);
		ofVertex(bounds.x + bounds.width/2+ARROW_SIZE, bounds.y);
	}
	ofVertex(bounds.x + bounds.width, bounds.y);
	ofVertex(bounds.x + bounds.width, bounds.y + bounds.height);
    
	if (_arrowPosition==0)
	{
		ofVertex(bounds.x + bounds.width/2+ARROW_SIZE,
                 bounds.y + bounds.height);
        
		ofVertex(bounds.x + bounds.width/2,
                 bounds.y+bounds.height+ARROW_SIZE);
        
		ofVertex(bounds.x + bounds.width/2-ARROW_SIZE,
                 bounds.y+bounds.height);
	}
	ofVertex(bounds.x, bounds.y + bounds.height);
	
	ofEndShape();
}

void QuestionBox::clear()
{
	while (buttons.size()>0) {
		delete buttons[buttons.size()-1];
		buttons.erase(buttons.end());
	}
}

void QuestionBox::setWith(vector<string> options)
{
	int nOptions = options.size();
	buttons.resize(0);
	
	bounds.height = options.size() * (OPTION_HEIGHT + PADDING *2);
	setTarget(_targetXY);
	
	for (int iOption=0; iOption<nOptions; iOption++)
	{
		buttons.push_back(new Button(bounds.x+PADDING,bounds.y+PADDING+ iOption*(OPTION_HEIGHT+PADDING),
								 OPTION_WIDTH, OPTION_HEIGHT,
								options[iOption]));
		
		buttons[iOption]->action+= Delegate<QuestionBox, int>(this, &QuestionBox::button_hit);
	}
	
	enabled = true;
}

void QuestionBox::touchDown(Touch *_touch)
{
	GUI_element::touchDown(_touch);
	for (int iButton=0; iButton<buttons.size(); iButton++)
		if (buttons[iButton]->isHit(_touch))
			buttons[iButton]->touchDown(_touch);
}

void QuestionBox::touchUp(Touch *_touch)
{
	GUI_element::touchUp(_touch);
	for (int iButton=0; iButton<buttons.size(); iButton++)
		if (buttons[iButton]->_Touches[_touch->ID].isDown)
			buttons[iButton]->touchUp(_touch);
	
}


void QuestionBox::button_hit(const void* pSender, int &iAction)
{
	ofNotifyEvent(action,iAction,this);
}

void QuestionBox::setTarget(ofPoint targetXY)
{
	_targetXY=targetXY;
	
	//check different conditions for where the arrow should be
	//for now, just above/below
	
	bounds.x = targetXY.x - bounds.width/2;
	
	if (targetXY.y - bounds.height - ARROW_SIZE < 0)
		_arrowPosition=1;
	else
		_arrowPosition=0;
	
	
	if (_arrowPosition==0)
		bounds.y = targetXY.y - bounds.height - ARROW_SIZE;
	else
		bounds.y = targetXY.y + ARROW_SIZE;
}
