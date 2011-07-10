//
//  List.cpp
//  MapTools
//
//  Created by Elliot Woods on 10/03/2011.
//  Copyright 2011 Kimchi and Chips. All rights reserved.
//

#include "List.h"

List::List(float x, float y, float w, float h, string caption) :
GUI_element(x, y, w, h),
scroll(0),
totalHeight(0),
itemHasInteraction(false)
{
    this->caption = caption;
}

void List::draw()
{
    //run update
    update();
    
    //draw caption
    drawCaption(this);
    
    //calculate bounds of List area (-caption)
    ofRectangle scrollableBounds = bounds;
    scrollableBounds.height -= OFXKCTG_CAPTION_LINE_HEIGHT;
    scrollableBounds.y += OFXKCTG_CAPTION_LINE_HEIGHT;
    
    //store old viewport
    GLint oldview[4];
    glGetIntegerv(GL_VIEWPORT, oldview);
    
    //store old matrices
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    
    //apply screenspace transform
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    //
    GLfloat orthoMatrix[16] = {
        0,  2/scrollableBounds.width,  0,  0,
        2/scrollableBounds.height,  0,  0, 0,
        0,  0,  1,  0,
        -1,  -1,  0,  1
    };
    glMultMatrixf(orthoMatrix);
    
    
    //setup viewport
    glViewport(scrollableBounds.y, scrollableBounds.x,
               scrollableBounds.height, scrollableBounds.width);

    //scroll transform
    ofTranslate(0, scroll);
    
    //draw all items
    vector<ListItem*>::iterator it;
    for (it = Items.begin(); it != Items.end(); it++)
        (*it)->draw();
    
    //restore old viewport
    glViewport(oldview[0], oldview[1], oldview[2], oldview[3]);
    
    //restore old matrices
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

ListItem* List::operator[](int &idx){
    return Items[idx];
}

void List::push(ListItem* add)
{
    ofRectangle itemBounds = add->getBounds();
    
    Items.push_back(add);
    
    itemBounds.y = totalHeight;
    totalHeight += itemBounds.height;
    
    add->setBounds(itemBounds);
}

void List::touchDown(Touch *_touch)
{
    GUI_element::touchDown(_touch);
    
    Touch touchTransformed = *_touch;
    
    touchTransformed.x -= bounds.x;
    touchTransformed.y -= bounds.y + OFXKCTG_CAPTION_LINE_HEIGHT + scroll
    ;
    
    vector<ListItem*>::iterator it;
    for (it = Items.begin(); it != Items.end(); it++)
        if ((*it)->isHit(&touchTransformed))
            (*it)->touchDown(&touchTransformed);
}

void List::touchUp(Touch *_touch)
{
    GUI_element::touchUp(_touch);
    
    Touch touchTransformed = *_touch;
    
    touchTransformed.x -= bounds.x;
    touchTransformed.y -= bounds.y + OFXKCTG_CAPTION_LINE_HEIGHT + scroll;
    
    vector<ListItem*>::iterator it;
    for (it = Items.begin(); it != Items.end(); it++)
        if ((*it)->_Touches[_touch->ID].isDown)
            (*it)->touchUp(&touchTransformed);
    
    if (_nTouchesDown == 0)
        itemHasInteraction = false;
    
}

void List::touchMoved(Touch *_touch)
{
    GUI_element::touchMoved(_touch);
    
    scrollVelocity = _touch->dy;
    
    if (itemHasInteraction)
        scrollVelocity = 0;
    
    scroll += scrollVelocity;
}

void List::update()
{
    //this is protected
    //since we're going
    //to call this ourselves
    //from draw
    
    //first check if user has control
    if (_nTouchesDown > 0)
        return;
    
    if (fabs(scrollVelocity) > 200)
        scrollVelocity = (scrollVelocity > 0 ? 200 : - 200);

    scrollVelocity *= (1 - GUI_LIST_DAMPING);    
    
    if (scroll > 0)
        scrollVelocity -= 0.3 * ofGetLastFrameTime() * scroll;
    
    if (scroll < -MAX(totalHeight - bounds.height, 0))
        scrollVelocity -= 0.3 * ofGetLastFrameTime() * (scroll - MAX(totalHeight - bounds.height, 0));
    
    scroll += scrollVelocity;
}
