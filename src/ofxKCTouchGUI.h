#pragma once
/*
 *  ofxKCTouchGUI.cpp
 *  Kimchi and Chips' touch GUI
 *
 *  Created by Elliot Woods on 22/07/2010.
 *  Copyright 2010 Kimchi and Chips. All rights reserved.
 *
 */

#include "ofMain.h"

#include "elementsinc.h"
#include "GUI_element.h"
#include "Touch.h"
#include "ofxKCTouchGUI_statics.h"

#include "QuestionBox.h"

class ofxKCTouchGUI : ofxKCTouchGUI_statics
{
public:
	ofxKCTouchGUI();
    ~ofxKCTouchGUI();
    
    void        update();
    void        draw();
    
    void		touchDown(Touch *_touch);
	void		touchUp(Touch *_touch);
	void		touchMoved(Touch *_touch);
	
    void        pushElement(GUI_element *element);
	
	QuestionBox	message;
	bool		enableFPSCalming;
protected:
	void		nudgeInterface();
	
	vector<GUI_element*>     _vecGUIelements;
	float		lastAction;
	bool		isSlow;
};