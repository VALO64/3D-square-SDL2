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
#define FPS 25

void square(SDL_Renderer *render,float x_normal, float y_normal, float x2_normal, float y2_normal, float z_normal){
  float offset = 10; //Offset to senter the square in the middle the square is 20x20 pixels
  SDL_Rect point1_sq;
  /* Normalization x and y cordenates to just set -1 to 1 and x and y */
  point1_sq.x = ((x_normal + 1)*WIDTH/2) - offset;
  point1_sq.y = ((y_normal + 1)*HEIGHT/2) - offset;
  point1_sq.w = 20;
  point1_sq.h = 20;
  /* Z axis added formula */ 
  point1_sq.x = point1_sq.x/z_normal;
  point1_sq.y = point1_sq.y/z_normal;

  SDL_Rect point2_sq;
  /* Normalization x and y cordenates to just set -1 to 1 and x and y */
  point2_sq.x = ((x2_normal + 1)*WIDTH/2) - offset;
  point2_sq.y = ((y2_normal + 1)*HEIGHT/2) - offset;
  point2_sq.w = 20;
  point2_sq.h = 20;
  /* Z axis added formula */ 
  point2_sq.x = point2_sq.x/z_normal;
  point2_sq.y = point2_sq.y/z_normal;
  //SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
  

  /* Point movement animation */
  for(int i = 0;  point1_sq.x>390 && point1_sq.y<390 && point2_sq.x < 390 && point2_sq.y < 390; i++){
    /* Point 1 movement */
    point1_sq.x = point1_sq.x - i;
    point1_sq.y = point1_sq.y + i;
    /* Point 2 movement */
    point2_sq.x = point2_sq.x + i;
    point2_sq.y = point2_sq.y + i;
    SDL_SetRenderDrawColor(render, GRAY);
    SDL_RenderClear(render);
    SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
    SDL_RenderFillRect(render, &point1_sq);
    SDL_RenderFillRect(render, &point2_sq);
    SDL_RenderPresent(render);
    std::cout << "x cordenate: " << point1_sq.x << std::endl;
    std::cout << "y cordenate: " << point1_sq.y << std::endl;
    SDL_Delay(1000/FPS);
  }
  std::cout << "x initial cordenate point1: " << point1_sq.x << std::endl; 
  std::cout << "y initial cordenate point1: " << point1_sq.y << std::endl;
  std::cout << "x initial cordenate point2: " << point2_sq.x << std::endl;
  std::cout << "y initial cordenate point2: " << point2_sq.y << std::endl;
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
      square(render, 0.5 , flip * 0.5, -0.5, flip * 0.5, 1);
      
  }
  SDL_DestroyRenderer(render);
  SDL_DestroyWindow(mainwin);
  SDL_Quit();
  return 0;
}
