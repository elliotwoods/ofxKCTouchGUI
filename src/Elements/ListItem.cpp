//
//  ListItem.cpp
//  MapTools
//
//  Created by Elliot Woods on 10/03/2011.
//  Copyright 2011 Kimchi and Chips. All rights reserved.
//

#include "ListItem.h"

ListItem::ListItem(float w, float h, bool& grabInteraction) :
GUI_element(0, 0, w, h),
interactionReference(grabInteraction)
{
        
}


void ListItem::grabInteraction()
{
    //this function is called when this
    //item believes that it is being 
    //interacted with
    
    interactionReference = true;
}