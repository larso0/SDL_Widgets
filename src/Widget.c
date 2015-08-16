/*
 * Widget.c
 *
 *  Created on: 15. aug. 2015
 *      Author: larso
 */

#include "Widget.h"

void InitWidget(Widget* widget, Widget* parent, bool parent_destroy,
                SDL_Color* bg, SDL_Color* fg,
                WidgetUpdateCallback update_callback,
                WidgetEventCallback event_callback,
                WidgetRenderCallback render_callback,
                WidgetDestructor destructor)
{
    if(!(widget && destructor && render_callback)) return;
    if(parent) AddChild(parent, widget);
    else widget->parent = NULL;
    widget->left = NULL;
    widget->right = NULL;
    widget->parent_destroy = parent_destroy;
    widget->rect.x = 0;
    widget->rect.y = 0;
    widget->rect.w = 0;
    widget->rect.h = 0;
    if(bg)
    {
        widget->bg.r = bg->r;
        widget->bg.g = bg->g;
        widget->bg.b = bg->b;
        widget->bg.a = bg->a;
    }
    else
    {
        widget->bg.r = 255;
        widget->bg.g = 255;
        widget->bg.b = 255;
        widget->bg.a = 0;
    }
    if(fg)
    {
        widget->fg.r = bg->r;
        widget->fg.g = bg->g;
        widget->fg.b = bg->b;
        widget->fg.a = bg->a;
    }
    else
    {
        widget->fg.r = 0;
        widget->fg.g = 0;
        widget->fg.b = 0;
        widget->fg.a = 255;
    }
    widget->update = update_callback;
    widget->event = event_callback;
    widget->render = render_callback;
    widget->destroy = destructor;
}

void QueryWidget(Widget* widget, SDL_Rect* rect, SDL_Color* bg, SDL_Color* fg)
{
    if(!widget) return;
    if(rect)
    {
        rect->x = widget->rect.x;
        rect->y = widget->rect.y;
        rect->w = widget->rect.w;
        rect->h = widget->rect.h;
    }
    if(bg)
    {
        bg->r = widget->bg.r;
        bg->g = widget->bg.g;
        bg->b = widget->bg.b;
        bg->a = widget->bg.a;
    }
    if(fg)
    {
        fg->r = widget->fg.r;
        fg->g = widget->fg.g;
        fg->b = widget->fg.b;
        fg->a = widget->fg.a;
    }
}

void SetParent(Widget* widget, Widget* parent)
{
    if(widget)
    {
        widget->parent = parent;
    }
}

void AddChild(Widget* widget, Widget* child)
{
    if(!(widget && child)) return;
    child->parent = widget;
    if(widget->left == NULL) widget->left = child;
    else
    {
        Widget* sibling = widget->left;
        while(sibling->right) sibling = sibling->right;
        sibling->right = child;
    }
}

void UpdateWidget(Widget* widget, SDL_Rect* rect)
{
    if(widget && widget->update) widget->update(widget, rect);
}

void HandleEvent(Widget* widget, SDL_Event* e)
{
    if(widget && e && widget->event) widget->event(widget, e);
}

void RenderWidget(Widget* widget, SDL_Renderer* ren)
{
    if(widget && ren) widget->render(widget, ren);
}

void DestroyWidgetTree(Widget* root)
{
    if(root)
    {
        DestroyWidgetTree(root->left);
        DestroyWidgetTree(root->right);
        if(root->parent_destroy)
        {
            root->destroy(root);
        }
    }
}

void DestroyWidget(Widget* widget)
{
    if(widget)
    {
        DestroyWidgetTree(widget->left);
        if(widget->parent)
        {
            Widget* tmp = widget->parent->left;
            if(tmp != widget)
            {
                for(; tmp->right != widget; tmp = tmp->right);
                tmp->right = widget->right;
            }
            else
            {
                widget->parent->left = widget->right;
            }
        }
        widget->destroy(widget);
    }
}
