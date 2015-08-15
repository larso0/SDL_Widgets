/*
 * Label.c
 *
 *  Created on: 15. aug. 2015
 *      Author: larso
 */

#include "Label.h"

Label* CreateLabel(Widget* parent, bool parent_destroy,
                   char* text, TTF_Font* font, LabelWrapMode wrap,
                   SDL_Color* bg, SDL_Color* fg)
{
    if(!(text && font)) return NULL;
    Label* label = malloc(sizeof(Label));
    if(!label) return NULL;
    InitWidget((Widget*)label, parent, parent_destroy, bg, fg,
               &UpdateLabel, NULL, &RenderLabel, &DestroyLabel);
    label->text = malloc(sizeof(char)*(strlen(text) + 1));
    if(!label->text)
    {
        free(label);
        return NULL;
    }
    strcpy(label->text, text);
    label->font = font;
    label->surface = NULL;
    label->texture = NULL;
    label->wrap = wrap;
    return label;
}

void UpdateLabel(Widget* widget, SDL_Rect* rect)
{
    if(!(widget && rect)) return;
    Label* label = (Label*)widget;
    label->rect.x = rect->x;
    label->rect.y = rect->y;
    if(label->texture)
    {
        SDL_DestroyTexture(label->texture);
        label->texture = NULL;
    }
    if(label->surface)
    {
        SDL_FreeSurface(label->surface);
        label->surface = NULL;
    }
    switch(label->wrap)
    {
    case LABELWRAP_FIXED:
    case LABELWRAP_AUTOMATIC:
        label->surface = TTF_RenderUTF8_Blended_Wrapped(label->font, label->text, label->fg, rect->w);
        break;
    case LABELWRAP_SINGLE_LINE:
        label->surface = TTF_RenderUTF8_Blended(label->font, label->text, label->fg);
        break;
    }
    if(label->surface)
    {
        label->rect.h = label->surface->h;
        label->rect.w = label->surface->w;
    }
}

void RenderLabel(Widget* widget, SDL_Renderer* ren)
{
    if(!(widget && ren)) return;
    Label* label = (Label*)widget;
    if(!label->texture && label->font && label->surface)
    {
        label->texture = SDL_CreateTextureFromSurface(ren, label->surface);
        if(!label->texture) return;
    }
    SDL_SetRenderDrawColor(ren, label->bg.r, label->bg.g, label->bg.b, label->bg.a);
    SDL_RenderFillRect(ren, &label->rect);
    SDL_RenderCopy(ren, label->texture, NULL, &label->rect);
}

void DestroyLabel(Widget* widget)
{
    if(!widget) return;
    Label* label = (Label*)widget;
    if(label->text) free(label->text);
    if(label->surface) SDL_FreeSurface(label->surface);
    if(label->texture) SDL_DestroyTexture(label->texture);
    free(label);
}
