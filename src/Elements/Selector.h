#pragma once
/*
 *  Selector.h
 *  Kimchi and Chips' touch GUI
 *
 *  Created by Elliot Woods on 28/09/2010.
 *  Copyright 2010 Kimchi and Chips. All rights reserved.
 *
 */

#include "GUI_element.h"

#include "Poco/BasicEvent.h"
using Poco::BasicEvent;

class Selector : public GUI_element
{
	public:
		Selector(float inx, float iny, float inw, float inh,
			  int &selection, int nItems,
			  string caption, int _nRows=1);
    
		void		draw();
		void		update();
		
		void		touchMoved(Touch *_touch);
		void        touchUp(Touch *_touch);
		void        touchDown(Touch *_touch);
	
        string&     operator[](const int &idx);
		vector<string>	_items;
		
		BasicEvent<int>	action;
	
	protected:
		int			&_selection;
		int			nRows;
		int			nColumns;
	
};