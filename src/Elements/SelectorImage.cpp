//
//  SelectorImage.cpp
//  Kimchi and Chips' touch GUI
//
//  Created by Elliot Woods on 12/02/2011.
//  Copyright 2011 Kimchi and Chips. All rights reserved.
//

#include "SelectorImage.h"

SelectorImage::SelectorImage(float _x, float _y, float _w,int &selection, int nItems, string caption,   string upStateImageAsset, string downStateImageAsset, string fontAsset) :

Selector(_x, _y, _w, 100, selection, nItems, caption, 2),
upState(getImage(upStateImageAsset)),
downState(getImage(downStateImageAsset)),
font(getFont(fontAsset))

{
    
    imgWidth = upState.getWidth();
    imgHeight = upState.getHeight();
    
    nColumns = floor(_w / imgWidth);
    nRows = ceil(float(nItems) / float(nColumns));
    
    //we reset width incase rounding occured
    bounds.width = imgWidth * nColumns;
    bounds.height = imgHeight * nRows + OFXKCTG_CAPTION_LINE_HEIGHT;
}

void SelectorImage::draw()
{
    drawCaption(this);
    
    //check we have anything to draw
    //this also avoids div(0)
    int nItems = _items.size();
    if (nItems == 0)
        return;
	
	float xStep = bounds.width / nColumns;
	float yStep = bounds.height / nRows;
	
	ofPushStyle();
	ofEnableAlphaBlending();
	
	int iRow, iColumn;
    bool selected;
    float offsetX, offsetY;
    offsetY = -font.getLineHeight() / 3;
    
    ofRectangle itemBounds;
    
	for (int i=0; i<nItems; i++)
	{
		iColumn = i % nColumns;
		iRow = i / nColumns;
        
        selected = (_selection==i);
		
        ofSetColor(255, 255, 255);
		
        //calc bounds
        itemBounds = ofRectangle(bounds.x + xStep*iColumn,
                                 bounds.y + yStep*iRow
                                 +OFXKCTG_CAPTION_LINE_HEIGHT,
                                 imgWidth, imgHeight);
        
        //background
        if (selected)
            downState.draw(itemBounds);
        else
            upState.draw(itemBounds);
				
		//text colour
		if (selected)
			ofSetColor(0x92, 0xFF, 0x00);
		else
			ofSetColor(0x89, 0x89, 0x89);

        //text
        offsetX = - font.stringWidth(_items[i]) / 2;
        
        font.drawString(_items[i],
                        itemBounds.x + xStep*0.5 + offsetX,
                        itemBounds.y + yStep*0.5 + offsetY);
	}
    
    //fill out row with
    //blank buttons
    while (++iColumn < nColumns)
    {
        itemBounds = ofRectangle(bounds.x + xStep*iColumn,
                                 bounds.y + yStep*iRow,
                                 imgWidth, imgHeight);
        
        upState.draw(itemBounds);
    }

	ofPopStyle();
	
	
}