//
//  hasCaption.cpp
//  MapTools
//
//  Created by Elliot Woods on 28/02/2011.
//  Copyright 2011 Kimchi and Chips. All rights reserved.
//

#include "hasCaption.h"

hasCaption::hasCaption() : 
fontCaption(getFont("Helvetica_10"))
{
    
}

void hasCaption::drawCaption(GUI_element *element)
{
    ofPushStyle();
    
    //get bounds
    ofRectangle bounds = element->getBounds();
    
    /////////////////////////
    // DRAW BACKGROUND
    /////////////////////////
    //
    ofSetLineWidth(0);
    ofFill();
    ofSetColor(0,0,0);
    
    ofRect(bounds.x, bounds.y, bounds.width, OFXKCTG_CAPTION_LINE_HEIGHT);
    //
    /////////////////////////

    
    /////////////////////////
    // DRAW TEXT
    /////////////////////////
    //
    ofSetColor(255,255,255);
    
    fontCaption.drawString(element->getCaption(),
                           bounds.x + OFXKCTG_CAPTION_OFFSET_X,
                           bounds.y + OFXKCTG_CAPTION_OFFSET_Y);
    //
    /////////////////////////
    
    ofPopStyle();    
}