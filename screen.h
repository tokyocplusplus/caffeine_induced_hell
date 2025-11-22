#include <stdio.h>
#include <iostream>
#include <vector>
#include <SDL.h>

class screen
{
public:
    SDL_Event e;
    SDL_Window* w;
    SDL_Renderer* r;
    std::vector<SDL_FPoint> pixels;

    screen()
    {
        SDL_Init(SDL_INIT_VIDEO);
        w = SDL_CreateWindow("",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,1280,720,0);
        r = SDL_CreateRenderer(w,-1,SDL_RENDERER_SOFTWARE);

        SDL_RendererInfo info;
        SDL_GetRendererInfo(r,&info);
        printf("RENDERER_INFO: %s\n", info.name);
    }

    void pixel(float x, float y)
    {
        pixels.emplace_back(SDL_FPoint{x,y});
    }

    void clear()
    {
        pixels.clear();
    }

    void show()
    {
        SDL_SetRenderDrawColor(r,0,0,0,255);
        SDL_RenderClear(r);

        SDL_SetRenderDrawColor(r,255,0,255,255);
        for (auto& pixel : pixels)
        {
            SDL_RenderDrawPointF(r,pixel.x,pixel.y);
        }

        SDL_RenderPresent(r);
    }

    void input()
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                SDL_Quit();
                exit(0);
            }
        }
    }
};