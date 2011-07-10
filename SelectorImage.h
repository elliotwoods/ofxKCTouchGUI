//
//  SelectorImage.h
//  KCTouchGUI
//
//  Created by Elliot Woods on 12/02/2011.
//  Copyright 2011 Kimchi and Chips. All rights reserved.
//

#include "Selector.h"
#include "ofxImageAsset.h"
#include "ofxFontAsset.h"
#include "hasCaption.h"

class SelectorImage : public Selector, ofxImageAsset, ofxFontAsset, hasCaption
{
public:
    SelectorImage(float _x, float _y, float _w,
             int &selection, int nItems, string caption, string upStateImageAsset, string downStateImageAsset,
                  string fontAsset);
    
    virtual void draw();
    
protected:
    ofImage&        upState;
    ofImage&        downState;
    ofTrueTypeFont& font;
    
    float   imgWidth;
    float   imgHeight;

};