#include <SDL.h>
#include <emscripten.h>

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

int centerX = 400;
int centerY = 300;
int radius = 50;

void main_loop()
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
        {
            emscripten_cancel_main_loop();
        }
    }

    // BLUE BACKGROUND
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderClear(renderer);

    // RED BALL
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    for (int y = -radius; y <= radius; y++)
    {
        for (int x = -radius; x <= radius; x++)
        {
            if (x * x + y * y <= radius * radius)
            {
                SDL_RenderDrawPoint(renderer, centerX + x, centerY + y);
            }
        }
    }

    SDL_RenderPresent(renderer);
}

int main()
{
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow(
        "Blue Background + Red Ball",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800, 600,
        0
    );

    renderer = SDL_CreateRenderer(window, -1, 0);

    emscripten_set_main_loop(main_loop, 0, 1);

    return 0;
}
