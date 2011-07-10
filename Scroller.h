#pragma once
//
//  Scroller.h
//  Kimchi and Chips' touch GUI
//
//  Created by Elliot Woods on 02/08/2010.
//  Copyright (c) 2010 Kimchi and Chips. All rights reserved.
//

// possible extensions:
// event for tap
// constraints action {rubber band, circular, bounce}

#define HIT_TIMEOUT 0.5 // max amount of time in seconds a click can last for before it's ignored

#include "GUI_element.h"

class Scroller : public GUI_element
{
public:
    Scroller(float inx, float iny, float inw, float inh, 
			 float dampTimeX, float dampTimeY, bool hasInterval, float interval,
			 int min, int max, bool wrap,
             bool scroll_x, bool scroll_y);
    
    void		draw();
    void		update();
        
    void		touchMoved(Touch *_touch);
    void        touchUp(Touch *_touch);
    void        touchDown(Touch *_touch);
	
	virtual void	hit(Touch *_touch) = 0;
	
	float       _x, _y;
	
	float		_dampTimeX, _dampTimeY;
	bool		_hasInterval;
	float		_interval;
	
	int			_min, _max;
	bool		_wrap; // should replace this with wrap, clamp, etc
    
    bool        _hasTouchesAttached;
	
protected:
    float       _Vx, _Vy; // velocities
    bool        _scroll_x, _scroll_y;
    void        nudgeTimeStep();
    
    float       _lastTimeStep;
};