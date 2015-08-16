/*
 * VLayout.c
 *
 *  Created on: 15. aug. 2015
 *      Author: larso
 */

#include "VLayout.h"

VLayout* CreateVLayout(Widget* parent, bool parent_destroy, SDL_Color* bg, SDL_Color* fg)
{
    VLayout* layout = malloc(sizeof(VLayout));
    if(!layout) return NULL;
    InitWidget((Widget*)layout, parent, parent_destroy, bg, fg,
               &UpdateVLayout, &VLayoutEvent, &RenderVLayout, &DestroyVLayout);
    return layout;
}

void UpdateVLayout(Widget* widget, SDL_Rect* rect)
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
        int height = 0;
        int layout_size = rect->h;
        int widget_size = rect->h / widget_count;
        SDL_Rect widget_rect;
        widget_size = rect->h;
        widget_rect.x = rect->x;
        widget_rect.y = rect->y;
        widget_rect.w = rect->w;
        tmp = widget->left;
        for(; tmp; tmp = tmp->right)
        {
            UpdateWidget(tmp, &widget_rect);
            QueryWidget(tmp, &widget_rect, NULL, NULL);
            height += widget_rect.h;
            layout_size -= widget_rect.h;
            widget_count--;
            if(widget_rect.h != widget_size && layout_size > 0 && widget_count > 0) widget_size = layout_size / widget_count;
            widget_rect.y += widget_rect.h;
            widget_rect.h = widget_size;
        }
        widget->rect.h = height;
    }
    else
    {
        widget->rect.h = 0;
    }
}

void VLayoutEvent(Widget* widget, SDL_Event* e)
{

}

void RenderVLayout(Widget* widget, SDL_Renderer* ren)
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

void DestroyVLayout(Widget* widget)
{
    if(widget)
    {
        VLayout* layout = (VLayout*)widget;
        free(layout);
    }
}
