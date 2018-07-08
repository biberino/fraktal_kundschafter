#include <iostream>
#include <thread>
#include <SDL2/SDL.h>

#include "types.hpp"
#include "workload_distributor.hpp"
#include "result_store.hpp"
#include "fractal_worker.hpp"
#include "fractal_functions.hpp"
#include "fractal_functions.hpp"
#include "iterations.hpp"

Resolution_info res;

void wrapper(Fractal_worker *w)
{
    w->start();
}

void draw(Result_store *store)
{
    std::vector<Color_info> vec = *(store->get_vector());

    SDL_Event event;
    SDL_Renderer *renderer;
    SDL_Window *window;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(res.x, res.y, 0, &window, &renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    for (auto el : vec)
    {
        //std::cout << el.pixel.x << " || " << el.pixel.y << '\n';
        SDL_SetRenderDrawColor(renderer, el.color.r, el.color.g, el.color.b, 255);
        SDL_RenderDrawPoint(renderer, el.pixel.x, el.pixel.y);
    }

    /**
    while (1)
    {
        if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
            break;
    }
    **/

    SDL_RenderPresent(renderer);
    SDL_Delay(5000);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(int argc, char const *argv[])
{

    res.x = 1200;
    res.y = 1000;

    Workload_distributor work_dis;
    work_dis.reset(res);
    Result_store store;
    store.reset(res);

    Fractal_params fractal_params;
    fractal_params.store = &store;
    fractal_params.work_dis = &work_dis;
    fractal_params.axis.x_min = -2;
    fractal_params.axis.x_max = 1;
    fractal_params.axis.y_min = -1;
    fractal_params.axis.y_max = 1;
    fractal_params.iteration_function = normal_iter;
    fractal_params.res = res;
    fractal_params.work_size = 2000;

    std::vector<std::thread> threads;
    std::vector<Fractal_worker> workers;

    for (unsigned int i = 0; i < std::thread::hardware_concurrency(); i++)
    {
        workers.push_back(Fractal_worker());
    }

    for (unsigned int i = 0; i < std::thread::hardware_concurrency(); i++)
    {
        workers[i].set_params(fractal_params);
        threads.push_back(std::thread(&Fractal_worker::start, &workers[i]));
    }

    for (unsigned int i = 0; i < std::thread::hardware_concurrency(); i++)
    {
        threads[i].join();
        //store.put(&(workers[i]._col_info_vec));
    }

    draw(&store);

    return 0;
}
