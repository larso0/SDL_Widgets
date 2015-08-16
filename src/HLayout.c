/*
 * HLayout.c
 *
 *  Created on: 16. aug. 2015
 *      Author: larso
 */

#include "HLayout.h"

HLayout* CreateHLayout(Widget* parent, bool parent_destroy, SDL_Color* bg, SDL_Color* fg)
{
    HLayout* layout = malloc(sizeof(HLayout));
    if(!layout) return NULL;
    InitWidget((Widget*)layout, parent, parent_destroy, bg, fg,
               &UpdateHLayout, &HLayoutEvent, &RenderHLayout, &DestroyHLayout);
    return layout;
}

void UpdateHLayout(Widget* widget, SDL_Rect* rect)
{
    if(!(widget && rect)) return;
    widget->rect.x = rect->x;
    widget->rect.y = rect->y;
    widget->rect.w = rect->w;
    widget->rect.h = rect->h;
    int widget_count = 0;
    Widget* tmp = widget->left;
    for(; tmp; tmp = tmp->right) widget_count++;
    if(widget_count > 0)
    {
        int width = 0;
        int layout_size = rect->w;
        int widget_size = layout_size / widget_count;
        SDL_Rect widget_rect;
        widget_rect.x = rect->x;
        widget_rect.y = rect->y;
        widget_rect.h = rect->h;
        widget_rect.w = widget_size;
        tmp = widget->left;
        for(; tmp; tmp = tmp->right)
        {
            UpdateWidget(tmp, &widget_rect);
            QueryWidget(tmp, &widget_rect, NULL, NULL);
            width += widget_rect.w;
            layout_size -= widget_rect.w;
            widget_count--;
            if(widget_rect.w != widget_size && layout_size > 0 && widget_count > 0) widget_size = layout_size / widget_count;
            widget_rect.x += widget_rect.w;
            widget_rect.w = widget_size;
        }
    }
}

void HLayoutEvent(Widget* widget, SDL_Event* e)
{

}

void RenderHLayout(Widget* widget, SDL_Renderer* ren)
{
    if(!(widget && ren)) return;
    SDL_SetRenderDrawColor(ren, widget->bg.r, widget->bg.g, widget->bg.b, widget->bg.a);
    SDL_RenderFillRect(ren, &widget->rect);
    Widget* tmp = widget->left;
    for(; tmp; tmp = tmp->right)
    {
        RenderWidget(tmp, ren);
    }
}

void DestroyHLayout(Widget* widget)
{
    if(widget)
    {
        HLayout* layout = (HLayout*)widget;
        free(layout);
    }
}
