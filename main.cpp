#include <SDL2/SDL_events.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <iostream>
#include <math.h>
#include <SDL2/SDL.h>
#define WIDTH 800
#define HEIGHT 800
#define GRAY 92, 94, 93, 255

void layer1(SDL_Renderer *render,float x_normal, float y_normal, float z_normal){
  float offset = 10; //Offset to senter the square in the middle the square is 20x20 pixels
  SDL_Rect rectangle_test;
  /* Normalization x and y cordenates to just set -1 to 1 and x and y */
  rectangle_test.x = ((x_normal + 1)*WIDTH/2) - offset;
  rectangle_test.y = ((y_normal + 1)*HEIGHT/2) - offset;
  rectangle_test.w = 20;
  rectangle_test.h = 20;
  /* Z axis added formula */ 
  rectangle_test.x = rectangle_test.x/z_normal;
  rectangle_test.y = rectangle_test.y/z_normal;
  
  //SDL_SetRenderDrawColor(render, GRAY);
  //SDL_RenderClear(render);
  for(int i = 0;  rectangle_test.x>390; i++){
    rectangle_test.x = rectangle_test.x - i;
    SDL_SetRenderDrawColor(render, GRAY);
    SDL_RenderClear(render);
    SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
    SDL_RenderFillRect(render, &rectangle_test);
    SDL_RenderPresent(render);
    std::cout << "x cordenate: " << rectangle_test.x << std::endl;
    SDL_Delay(1000/60);
  }
  std::cout << "x initial cordenate: " << rectangle_test.x << std::endl; 
  std::cout << "y initial cordenate: " << rectangle_test.y << std::endl;
  std::cout << "variable x: " << x_normal << std::endl;
  std::cout << "variable y: " << y_normal << std::endl;
  std::cout << "variable z: " << z_normal << std::endl;
}


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
  float flip = -1; // Fliper to flip the y cordentates that posetive values goes up and negative goes down 
  
  //layer1(render, 0.5 , flip * 0, 1);
  
  
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

            //if(SDL_PointInRect(&mouse_pos, &rectangle_test)){
              //dragging = true;
            //}

          }

        }
        if (event.type == SDL_MOUSEBUTTONUP){
          if(event.button.button == SDL_BUTTON_LEFT){
            dragging = false;
          }
        }
        if(event.type == SDL_MOUSEMOTION){
          if(dragging){
            //rectangle_test.x = event.motion.x;
            //rectangle_test.y = event.motion.y;
            //std::cout << "Values: " << rectangle_test.x << std::endl;
          }
        }
      }
      /* Background color */
      //SDL_SetRenderDrawColor(render, GRAY);
      //SDL_RenderClear(render);
      /* Square color */
      //SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
      //SDL_RenderFillRect(render, &rectangle_test);
      layer1(render, 0.5 , flip * 0.5, 1);
      
  }
  SDL_DestroyRenderer(render);
  SDL_DestroyWindow(mainwin);
  SDL_Quit();
  return 0;
}
