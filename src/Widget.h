/*
 * Widget.h
 *
 *  Created on: 15. aug. 2015
 *      Author: larso
 */

#ifndef SRC_WIDGET_H_
#define SRC_WIDGET_H_

#include <SDL2/SDL.h>
#include <stdbool.h>

typedef struct _Widget
{
    struct _Widget* parent;
    struct _Widget* left, * right;
    bool parent_destroy;
    SDL_Rect rect;
    SDL_Color bg, fg;
    void (*update)(struct _Widget*, SDL_Rect*);
    void (*event)(struct _Widget*, SDL_Event*);
    void (*render)(struct _Widget*, SDL_Renderer*);
    void (*destroy)(struct _Widget*);
} Widget;

typedef void (*WidgetUpdateCallback)(Widget*, SDL_Rect*);
typedef void (*WidgetEventCallback)(Widget*, SDL_Event*);
typedef void (*WidgetRenderCallback)(Widget*, SDL_Renderer*);
typedef void (*WidgetDestructor)(Widget*);

#define INHERIT_WIDGET \
    Widget* parent; \
    Widget* left, * right; \
    bool parent_destroy; \
    SDL_Rect rect; \
    SDL_Color bg, fg; \
    WidgetUpdateCallback update; \
    WidgetEventCallback event; \
    WidgetRenderCallback render; \
    WidgetDestructor destroy;

void InitWidget(Widget* widget, Widget* parent, bool parent_destroy,
                SDL_Color* bg, SDL_Color* fg,
                WidgetUpdateCallback update_callback,
                WidgetEventCallback event_callback,
                WidgetRenderCallback render_callback,
                WidgetDestructor destructor);
void QueryWidget(Widget* widget, SDL_Rect* rect, SDL_Color* bg, SDL_Color* fg);

void SetParent(Widget* widget, Widget* parent);
void AddChild(Widget* widget, Widget* child);
void RemoveChild(Widget* widget, Widget* child);

void UpdateWidget(Widget* widget, SDL_Rect* rect);
void HandleEvent(Widget* widget, SDL_Event* e);
void RenderWidget(Widget* widget, SDL_Renderer* ren);
void DestroyWidget(Widget* widget);

#endif /* SRC_WIDGET_H_ */
