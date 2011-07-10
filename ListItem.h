#pragma once
//
//  ListItem.h
//  MapTools
//
//  Created by Elliot Woods on 10/03/2011.
//  Copyright 2011 Kimchi and Chips. All rights reserved.
//

#include "GUI_element.h"

class ListItem: public GUI_element
{
public:
    ListItem(float w, float h, bool& grabInteraction);
    
protected:
    void    grabInteraction();
    bool&   interactionReference;
};