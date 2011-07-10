#pragma once
/*
 *  GUI_element.h
 *  Kimchi and Chips' touch GUI
 *
 *  Created by Elliot Woods on 22/07/2010.
 *  Copyright 2010 Kimchi and Chips. All rights reserved.
 *
 */

#include "ofMain.h"
#include "Touch.h"
#include "GUI_constants.h"

class GUI_element
{
public:
	GUI_element(float x, float y, float w, float h);
	ofPoint				transformTouch(ofPoint touch);
	
	virtual void        draw();
    
	virtual void		update() { };
	
	virtual void		touchDown(Touch *_touch);
	virtual void		touchUp(Touch *_touch);
	virtual void		touchMoved(Touch *_touch);
	
	virtual bool		isHit(Touch *_touch);
	void				nudgeInterface();
    
    ofRectangle         getBounds() const;
    void                setBounds(ofRectangle& rect);
    void                setPosition(ofPoint& point);
    
    string              getCaption() const;
	
	Touch				_Touches[MAX_TOUCHES];
	Touch				*_downTouches[MAX_TOUCHES];
	int					_nTouchesDown;
	
	bool				enabled;
    
protected:
	void				countTouches(); 
    virtual void        boundsChanged() {};
    
    ofRectangle         bounds;
	float				_lastTouch;
    string              caption;

};