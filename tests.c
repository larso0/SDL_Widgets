/*
 * tests.c
 *
 *  Created on: 12. aug. 2015
 *      Author: larso
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include "src/Widget.h"
#include "src/Label.h"

int main(int argc, char** argv)
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "%s\n", SDL_GetError());
        return 1;
    }
    SDL_Window* window = SDL_CreateWindow("Tests", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 200, 200, SDL_WINDOW_RESIZABLE);
    if(!window)
    {
        fprintf(stderr, "%s\n", SDL_GetError());
        SDL_Quit();
        return 2;
    }
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(!renderer)
    {
        fprintf(stderr, "%s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 3;
    }
    if(TTF_Init() != 0)
    {
        fprintf(stderr, "%s\n", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 4;
    }
    TTF_Font* font = TTF_OpenFont("freefont/FreeMono.ttf", 14);
    if(!font)
    {
        fprintf(stderr, "%s\n", TTF_GetError());
        TTF_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 5;
    }

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    Label* label = CreateLabel(NULL, false, "This is my awesome label that I am very proud of introducing to you :)", font, LABELWRAP_AUTOMATIC, NULL, NULL);
    Widget* wptr = (Widget*)label;

    SDL_Rect rect;
    rect.x = rect.y = 0;
    SDL_GetWindowSize(window, &rect.w, &rect.h);
    UpdateWidget(wptr, &rect);

    bool running = true;
    while(running)
    {
        SDL_Event e;
        while(SDL_PollEvent(&e))
        {
            switch(e.type)
            {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_WINDOWEVENT:
                if(e.window.event == SDL_WINDOWEVENT_RESIZED)
                {
                    rect.w = e.window.data1;
                    rect.h = e.window.data2;
                    UpdateWidget(wptr, &rect);
                }
                break;
            default:
                break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        RenderWidget(wptr, renderer);
        SDL_RenderPresent(renderer);
    }

    DestroyWidget(wptr);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
