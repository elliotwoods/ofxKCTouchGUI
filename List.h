#pragma once
//
//  List.h
//  MapTools
//
//  Created by Elliot Woods on 10/03/2011.
//  Copyright 2011 Kimchi and Chips. All rights reserved.
//

#include "GUI_element.h"
#include "hasCaption.h"

#include "ListItem.h"


#define GUI_LIST_DAMPING 0.1

class List : public GUI_element, hasCaption
{
public:
    List(float x, float y, float w, float h, string caption);
    
    void            draw();
    
    void            touchDown(Touch *_touch);
    void            touchUp(Touch *_touch);
    void            touchMoved(Touch *_touch);
    
    ListItem*       operator[](int &idx);
    void            push(ListItem* add);
    
protected:
    void    update();
    
    float   scroll;
    float   scrollVelocity;
    
    void    drawBackground() {}
    
    vector<ListItem*>   Items;
    float               totalHeight;
    
    bool                itemHasInteraction;
    
};