/*
 *  Selector.cpp
 *  Kimchi and Chips' touch GUI
 *
 *  Created by Elliot Woods on 28/09/2010.
 *  Copyright 2010 Kimchi and Chips. All rights reserved.
 *
 */

#include "Selector.h"

Selector::Selector(float inx, float iny, float inw, float inh,
		int &selection, int nItems,
		string caption,
		int _nRows)
:  GUI_element(inx,iny,inw,inh),
_selection(selection)
{
	this->caption = caption;
	nRows = _nRows;
	nColumns = ceil(float(nItems)/float(_nRows));
	
    _items.resize(nItems);
	for (int i=0; i< nItems; i++)
		_items[i] = ofToString(i, 0);
}

void Selector::draw()
{
	GUI_element::draw();
	
	float xStep = bounds.width / nColumns;
	float yStep = bounds.height / nRows;
	
	ofPushStyle();
	ofEnableAlphaBlending();
	
	int iRow, iColumn;
    int nItems = _items.size();
    
    ofRectangle itemBounds;
    
	for (int i=0; i<nItems; i++)
	{
		iColumn = i % nColumns;
		iRow = i / nColumns;
		
		if (_selection==i)
			ofSetColor(255, 255, 255, 200);
		else
			ofSetColor(50, 50, 50, 200);
		
        //calc item bounds
        itemBounds = ofRectangle(bounds.x + xStep*iColumn, bounds.y + yStep*iRow, xStep, yStep);

		//fill
		ofFill();
		ofSetLineWidth(0);
		
		ofRect(itemBounds);
		
		//outline
		ofNoFill();
		ofSetColor(255, 255, 255);
		ofSetLineWidth(2);
		ofRect(itemBounds);
		
		//text
		if (_selection==i)
			ofSetColor(0, 0, 0);
		else
			ofSetColor(255, 255, 255);
		ofDrawBitmapString(_items[i],
                           itemBounds.x + xStep*0.5 - (8*_items[i].length()/2),
                           itemBounds.y+yStep*0.5);
	}
	
	ofSetColor(255, 255, 255);
	ofDrawBitmapString(caption, bounds.x, bounds.y-6);
	ofPopStyle();
	
	
}

void Selector::update()
{
}

void Selector::touchMoved(Touch *_touch)
{
    GUI_element::touchMoved(_touch);
}

void Selector::touchUp(Touch *_touch)
{
    GUI_element::touchUp(_touch);
	
}

void Selector::touchDown(Touch *_touch)
{
    GUI_element::touchDown(_touch);
	
	int iCol = nColumns * (_touch->x - bounds.x) / bounds.width;
	int iRow = nRows * (_touch->y - bounds.y) / bounds.height;
	
	_selection = iCol + iRow*nColumns;
	
	action.notify(this,_selection);
}

string& Selector::operator[](const int &idx)
{
    //allow an error to happen here
    //if index doesn't exist
    return _items[idx];
}
