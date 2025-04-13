#include <iostream>
#include <vector>
#include <SDL3/SDL.h>

using namespace std;

class Screen
{
    SDL_Event e; // defines what to do with the window
    SDL_Window *window;
    SDL_Renderer *renderer;
    std::vector<SDL_FPoint> points;

public:
    // constructors
    Screen()
    {
        if (SDL_Init(SDL_INIT_VIDEO) != 0)
        {
            cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
        }
        // SDL_Init(SDL_INIT_VIDEO);

        window = SDL_CreateWindow(
            "My SDL Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
        // SDL_CreateWindowAndRenderer(
        //(int)640 * 2, 480 * 2, 0, &windows, &renderer);

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        // SDL_RenderSetScale(renderer, 2, 2);

        if (!renderer)
        {
            cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << endl;
        }
    }

    ~Screen()
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    void pixel(float x, float y) void pixel(float x, float y)
    {
        points.emplace_back(x, y);
    }

    void show()
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        for (auto &point : points)
        {
            SDL_RenderDrawPointF(renderer, point.x, point.y);
            SDL_RenderDrawPointF(renderer, point.x, point.y)
        }
        SDL_RenderPresent(renderer);
    }

    void input()
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                exit(0);
            }
        }
    }
};
