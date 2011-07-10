#pragma once
//
//  hasCaption.h
//  MapTools
//
//  Created by Elliot Woods on 28/02/2011.
//  Copyright 2011 Kimchi and Chips. All rights reserved.
//

#define OFXKCTG_CAPTION_LINE_HEIGHT 21
#define OFXKCTG_CAPTION_OFFSET_X 20
#define OFXKCTG_CAPTION_OFFSET_Y 13


#include "ofMain.h"
#include "ofxFontAsset.h"
#include "GUI_element.h"

class hasCaption : ofxFontAsset
{
public:
    hasCaption();
    void drawCaption(GUI_element *element);

    ofTrueTypeFont  &fontCaption;
};