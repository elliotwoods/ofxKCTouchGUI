/*
 *  ButtonGraphic.h
 *  DKO001 - iPad client
 *
 *  Created by Elliot Woods on 01/12/2010.
 *  Copyright 2010 Kimchi and Chips. All rights reserved.
 *
 */

//graphical button
//send pointers with value 0 for states that aren't drawn

#include "Button.h"

class ButtonGraphic : public Button
{
public:
	ButtonGraphic(ofImage* _upState, ofImage* _downState,
				  float _x, float _y, float _iScreen,
				  int _iAction=0);
	
	void		draw();
	
	ofImage		*upState;
	ofImage		*downState;
	
	float		xoffset;
	
};