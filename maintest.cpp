#include <SDL2/SDL_events.h>
#include <SDL2/SDL2_gfxPrimitives.h> // Library to change the thiknes of the lines
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <iostream>
#include <math.h>
#include <SDL2/SDL.h>
#include "squareautorotation.h"
#define WIDTH 800
#define HEIGHT 800
int main(){
  std::cout << "This is a 3D square in C++!" << std::endl;
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
  float flip = -1; // Fliper to flip the y cordentates that posetive values goes up 
  
  bool quit = false;

  // Base normalized XY for the cube corners
  const float p1x =  0.5f, p1y =  0.5f;  //Point 1 
  const float p2x = -0.5f, p2y =  0.5f;  //Point 2
  const float p3x =  0.5f, p3y = -0.5f;  //Point 3
  const float p4x = -0.5f, p4y = -0.5f;  //Point 4
  // Back face points correspond 1:1 in XY
  const float p5x =  p1x,   p5y =  p1y;  // point5: back of point1
  const float p6x =  p2x,   p6y =  p2y;  // point6: back of point2
  const float p7x =  p3x,   p7y =  p3y;  // point7: back of point3
  const float p8x =  p4x,   p8y =  p4y;  // point8: back of point4

  float angle0 = 0.0f;            // starting angle
  const float ang_speed = 0.05f;  // radians per frame inside square

  while(!quit){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
      if(event.type == SDL_QUIT){
        quit = true;
      }
    }
    if (quit) break;

    square(render,
           /* front face */  p1x , p1y,
                             p2x , p2y,
                             p3x , p3y,
                             p4x , p4y,
           /* back face  */  p5x , p5y,
                             p6x , p6y,
                             p7x , p7y,
                             p8x , p8y,
           /* z values   */  0.6f,  -0.6f,  
           /* flip  */       flip,
           /* rotation */    angle0, ang_speed,
           &quit);

    angle0 += ang_speed * 200.0f; // 200 frames inside square()
    if (angle0 > 6.2831853f) angle0 -= 6.2831853f;
  }

  SDL_DestroyRenderer(render);
  SDL_DestroyWindow(mainwin);
  SDL_Quit();
  return 0;
}
