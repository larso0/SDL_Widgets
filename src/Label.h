/*
 * Label.h
 *
 *  Created on: 15. aug. 2015
 *      Author: larso
 */

#ifndef SRC_LABEL_H_
#define SRC_LABEL_H_

#include "Widget.h"
#include <SDL2/SDL_ttf.h>

typedef enum
{
    LABELWRAP_FIXED,
    LABELWRAP_SINGLE_LINE,
    LABELWRAP_AUTOMATIC
} LabelWrapMode;

typedef struct
{
    INHERIT_WIDGET

    char* text;
    TTF_Font* font;
    SDL_Texture* texture;
    LabelWrapMode wrap;
} Label;

Label* CreateLabel(Widget* parent, bool parent_destroy,
                   char* text, TTF_Font* font, LabelWrapMode wrap,
                   SDL_Color* bg, SDL_Color* fg);

void UpdateLabel(Widget* widget, SDL_Rect* rect);
void RenderLabel(Widget* widget, SDL_Renderer* ren);
void DestroyLabel(Widget* widget);


#endif /* SRC_LABEL_H_ */
