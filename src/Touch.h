#pragma once
/*
 *  Touch.h
 *  Kimchi and Chips' touch GUI
 *
 *  Created by Elliot Woods on 22/07/2010.
 *  Copyright 2010 Kimchi and Chips. All rights reserved.
 *
 */

#include "ofMain.h"

#define TOUCH_RADIUS 50
#define MAX_TOUCHES 20

class Touch
{
public:
	//methods
	Touch();

	void draw();
	
	ofPoint getOfPoint();
    void    setXY(float x, float y);
    void    moveXY(float x, float y);
	float	getLifetime();
	float	lastx();
	float	lasty();
	
	
	//variables
	int		ID;
	float	x, y;
    float   dx, dy;
	bool	isDown;
    bool    isAttached;
	bool	_hasMoved;
	
	float	_timeBorn;
};