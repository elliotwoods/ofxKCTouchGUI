#pragma once
//
//  ButtonImage.h
//  Kimchi and Chips' touch GUI
//
//  Created by Elliot Woods on 12/02/2011.
//  Copyright 2011 Kimchi and Chips. All rights reserved.
//

#include "Button.h"
#include "ofxImageAsset.h"
#include "hasCaption.h"

class ButtonImage : public Button, public ofxImageAsset, hasCaption
{
public:
    ButtonImage(string upStateImageAsset, string downStateImageAsset, float _x, float _y, string _caption, int _iAction=0);
    
    ButtonImage(string upStateImageAsset, string downStateImageAsset, float _x, float _y);
    
	void		draw();

protected:
    ofImage&        upState;
    ofImage&        downState;
};