//
//  ButtonImage.cpp
//  Kimchi and Chips' touch GUI
//
//  Created by Elliot Woods on 12/02/2011.
//  Copyright 2011 Kimchi and Chips. All rights reserved.
//

#include "ButtonImage.h"

ButtonImage::ButtonImage(string upStateImageAsset, string downStateImageAsset, float x, float y, string caption, int iAction) :

Button(x, y, 100, 100, caption, iAction),
upState(getImage(upStateImageAsset)),
downState(getImage(downStateImageAsset))

{
    bounds.width = upState.getWidth();
    bounds.height = upState.getHeight();
}

ButtonImage::ButtonImage(string upStateImageAsset, string downStateImageAsset, float x, float y) :

Button(x, y, 100, 100, "ButtonImage", 0),
upState(getImage(upStateImageAsset)),
downState(getImage(downStateImageAsset))

{
    bounds.width = upState.getWidth();
    bounds.height = upState.getHeight();
}

void ButtonImage::draw()
{
    if (_nTouchesDown == 0)
        upState.draw(bounds.x, bounds.y);
    else
		downState.draw(bounds.x, bounds.y);
}