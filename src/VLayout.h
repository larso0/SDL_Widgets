/*
 * VLayout.h
 *
 *  Created on: 15. aug. 2015
 *      Author: larso
 */

#ifndef SRC_VLAYOUT_H_
#define SRC_VLAYOUT_H_

#include "Widget.h"

typedef struct
{
    INHERIT_WIDGET
} VLayout;

VLayout* CreateVLayout(Widget* parent, bool parent_destroy, SDL_Color* bg, SDL_Color* fg);

void UpdateVLayout(Widget* widget, SDL_Rect* rect);
void VLayoutEvent(Widget* widget, SDL_Event* e);
void RenderVLayout(Widget* widget, SDL_Renderer* ren);
void DestroyVLayout(Widget* widget);

#endif /* SRC_VLAYOUT_H_ */
