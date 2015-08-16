/*
 * HLayout.h
 *
 *  Created on: 16. aug. 2015
 *      Author: larso
 */

#ifndef SRC_HLAYOUT_H_
#define SRC_HLAYOUT_H_

#include "Widget.h"

typedef struct
{
    INHERIT_WIDGET
} HLayout;

HLayout* CreateHLayout(Widget* parent, bool parent_destroy, SDL_Color* bg, SDL_Color* fg);

void UpdateHLayout(Widget* widget, SDL_Rect* rect);
void HLayoutEvent(Widget* widget, SDL_Event* e);
void RenderHLayout(Widget* widget, SDL_Renderer* ren);
void DestroyHLayout(Widget* widget);

#endif /* SRC_HLAYOUT_H_ */
