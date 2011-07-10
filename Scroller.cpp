//
//  Scroller.cpp
//  Kimchi and Chips' touch GUI
//
//  Created by Elliot Woods on 02/08/2010.
//  Copyright (c) 2010 Kimchi and Chips. All rights reserved.
//

#include "Scroller.h"


Scroller::Scroller(float inx, float iny, float inw, float inh,
				   float dampTimeX, float dampTimeY, bool hasInterval, float interval,
					 int min, int max, bool wrap,
                   bool scroll_x, bool scroll_y)
: GUI_element(inx,iny,inw,inh)
{
    _x=0;
    _y=0;
    _Vx=0;
    _Vy=0;
    
    _scroll_x = scroll_x;
    _scroll_y = scroll_y;
    
	_dampTimeX=dampTimeX;
	_dampTimeY=dampTimeY;
	_hasInterval=hasInterval;
	_interval=interval;
	
	_min = min;
	_max = max;
	_wrap = wrap;
	
    nudgeTimeStep();
    
}

void Scroller::draw()
{
    GUI_element::draw();
    
    // draw debug
    // when we inherit this class, we dont call Scroller's draw
    // its purely for debug purposes
    
    ofPushStyle();
    ofSetColor(255,255,255);
    ofSetLineWidth(2);
    ofNoFill();
    ofRect(bounds);
    
    ofDrawBitmapString("_x="+ofToString(_x)+", y="+ofToString(_y)+
                       "\n_Vx="+ofToString(_Vx)+", Vy="+ofToString(_Vy),
                       bounds.x, bounds.y + bounds.height - 20);

    ofPopStyle();
	
	ofCircle(bounds.x + bounds.width*(_x  - floor(_x)),
             bounds.y + bounds.height*(_y  - floor(_y)), 5);
    
    
}

void Scroller::update()
{
    
    if (!_hasTouchesAttached) //force momentum off until sort out Vx for touches (when stationary they should lose Vx)
    {
        if (_scroll_x)
            _x+=_Vx;
        if (_scroll_y)
            _y+=_Vy;        
    }
	
	if (_wrap)
	{
		while (_x>_max)
			_x-=_max-_min;
		while (_x<_min)
			_x+=_max-_min;
		
		while (_y>_max)
			_y-=_max-_min;
		while (_y<_min)
			_y+=_max-_min;
	}
		
	_Vx *= exp(-5*(ofGetElapsedTimef() - _lastTimeStep)/_dampTimeX);
	_Vy *= exp(-5*(ofGetElapsedTimef() - _lastTimeStep)/_dampTimeY);
    
	float k=0.1;
	if (_hasInterval)
	{
		_Vx -= k*(((_x-0.5)/_interval)-floor((_x-0.5)/_interval)-0.5);
		_Vy -= k*(((_y-0.5)/_interval)-floor((_y-0.5)/_interval)-0.5);
	}
    nudgeTimeStep();
    
    
}


void Scroller::touchMoved(Touch *_touch)
{
    GUI_element::touchMoved(_touch);
    _Vx = _touch->dx / bounds.width;
    _Vy = _touch->dy / bounds.height;
    
    
    if (_scroll_x)
        _x+=_Vx;
    if (_scroll_y)
        _y+=_Vy; 
}

void Scroller::touchUp(Touch *_touch)
{
    GUI_element::touchUp(_touch);
    
	_Vx = _touch->dx / bounds.width;
    _Vy = _touch->dy / bounds.height;
	
    _hasTouchesAttached=false;

    for (int iTouch=0; iTouch<MAX_TOUCHES; iTouch++)
        if (_Touches[iTouch].isDown)
            _hasTouchesAttached=true;
	
	if (!_touch->_hasMoved && _touch->getLifetime()<HIT_TIMEOUT)
		hit(_touch);
    
    nudgeTimeStep();

}

void Scroller::touchDown(Touch *_touch)
{
    GUI_element::touchDown(_touch);
	_Vx=0;
	_Vy=0;
    
    _hasTouchesAttached=true;
}

void Scroller::nudgeTimeStep()
{
    _lastTimeStep=ofGetElapsedTimef();
}
