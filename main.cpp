#include <SDL2/SDL_events.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <iostream>
#include <math.h>
#include <SDL2/SDL.h>
#define WIDTH 900
#define HEIGHT 800
#define GRAY 92, 94, 93, 255

int main(){
  std::cout << "Hello world!" << std::endl;
  SDL_Init(SDL_INIT_VIDEO);
  /* Creation of the main window */
  SDL_Window * mainwin = SDL_CreateWindow("3D Square", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,WIDTH,HEIGHT,0);
  /* Render creation for square movement */
  SDL_Renderer *render = SDL_CreateRenderer(mainwin,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!render) { // Check if the render is working
        std::cout << "Renderer creation failed: " << SDL_GetError() << "\n";
        SDL_DestroyWindow(mainwin);
        SDL_Quit();
        return -1;
    }
  SDL_Rect rectangle_test;
  rectangle_test.x = 200;
  rectangle_test.y = 200;
  rectangle_test.w = 200;
  rectangle_test.h = 200;
  
  bool quit = false;
  bool dragging = false;

  while(!quit){
    SDL_Event event;
      while(SDL_PollEvent(&event)){
        if(event.type == SDL_QUIT){
          quit = true;
        }
        if(event.type == SDL_MOUSEBUTTONDOWN){

          if(event.button.button == SDL_BUTTON_LEFT){

            SDL_Point mouse_pos = {event.button.x, event.button.y};

            if(SDL_PointInRect(&mouse_pos, &rectangle_test)){
              dragging = true;
            }

          }

        }
        if (event.type == SDL_MOUSEBUTTONUP){
          if(event.button.button == SDL_BUTTON_LEFT){
            dragging = false;
          }
        }
        if(event.type == SDL_MOUSEMOTION){
          if(dragging){
            rectangle_test.x = event.motion.x;
            rectangle_test.y = event.motion.y;
            std::cout << "Values: " << rectangle_test.x << std::endl;
          }
        }
      }
      /* Background color */
      SDL_SetRenderDrawColor(render, GRAY);
      SDL_RenderClear(render);
      /* Square color */
      SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
      SDL_RenderFillRect(render, &rectangle_test);
           
      SDL_RenderPresent(render);
  }
  SDL_DestroyRenderer(render);
  SDL_DestroyWindow(mainwin);
  SDL_Quit();
  return 0;
}
