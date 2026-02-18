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
#define FPS 15

void square(SDL_Renderer *render,
            float x_normal,  float y_normal,
            float x2_normal, float y2_normal,
            float x3_normal, float y3_normal,
            float x4_normal, float y4_normal,
            float x_5normal, float y_5normal,
            float x_6normal, float y_6normal,
            float x_7normal, float y_7normal,
            float x_8normal, float y_8normal,
            float z_normal,  float z_2normal,
            bool *quit)
{
  float offset = 10; //Offset to senter the square in the middle the square is 20x20 pixels
  //bool quit = false;
  // Screen center for perspective scaling around the center (added)
  const float cx = WIDTH * 0.5f;
  const float cy = HEIGHT * 0.5f;

  // Use magnitude of z so negative z still projects (added)
  float zn = fabsf(z_normal);   if (zn < 0.001f) zn = 0.001f; // avoid division by zero
  float z5 = fabsf(z_2normal);  if (z5 < 0.001f) z5 = 0.001f; // avoid division by zero

  SDL_Rect point1_sq;
  /* Normalization x and y cordenates to just set -1 to 1 and x and y */
  point1_sq.x = ((x_normal + 1)*WIDTH/2) - offset;
  point1_sq.y = ((y_normal + 1)*HEIGHT/2) - offset;
  point1_sq.w = 20;
  point1_sq.h = 20;
  /* Z axis added formula */ 
  point1_sq.x = (int)((point1_sq.x - cx) / zn + cx);
  point1_sq.y = (int)((point1_sq.y - cy) / zn + cy);

  SDL_Rect point2_sq;
  /* Normalization x and y cordenates to just set -1 to 1 and x and y */
  point2_sq.x = ((x2_normal + 1)*WIDTH/2) - offset;
  point2_sq.y = ((y2_normal + 1)*HEIGHT/2) - offset;
  point2_sq.w = 20;
  point2_sq.h = 20;
  /* Z axis added formula */ 
  point2_sq.x = (int)((point2_sq.x - cx) / zn + cx);
  point2_sq.y = (int)((point2_sq.y - cy) / zn + cy);

  SDL_Rect point3_sq;
  /* Normalization x and y cordenates to just set -1 to 1 and x and y */
  point3_sq.x = ((x3_normal + 1)*WIDTH/2) - offset;
  point3_sq.y = ((y3_normal + 1)*HEIGHT/2) - offset;
  point3_sq.w = 20;
  point3_sq.h = 20;
  /* Z axis added formula */ 
  point3_sq.x = (int)((point3_sq.x - cx) / zn + cx);
  point3_sq.y = (int)((point3_sq.y - cy) / zn + cy);

  SDL_Rect point4_sq;
  /* Normalization x and y cordenates to just set -1 to 1 and x and y */
  point4_sq.x = ((x4_normal + 1)*WIDTH/2) - offset;
  point4_sq.y = ((y4_normal + 1)*HEIGHT/2) - offset;
  point4_sq.w = 20;
  point4_sq.h = 20;
  /* Z axis added formula */ 
  point4_sq.x = (int)((point4_sq.x - cx) / zn + cx);
  point4_sq.y = (int)((point4_sq.y - cy) / zn + cy);

  SDL_Rect point5_sq;
  /* Normalization x and y cordenates to just set -1 to 1 and x and y */
  point5_sq.x = ((x_5normal + 1)*WIDTH/2) - offset;
  point5_sq.y = ((y_5normal + 1)*HEIGHT/2) - offset;
  point5_sq.w = 20;
  point5_sq.h = 20;
  /* Z axis added formula */ 
  point5_sq.x = (int)((point5_sq.x - cx) / z5 + cx); // uses |z_2normal|
  point5_sq.y = (int)((point5_sq.y - cy) / z5 + cy);

  SDL_Rect point6_sq;
  /* Normalization x and y cordenates to just set -1 to 1 and x and y */
  point6_sq.x = ((x_6normal + 1)*WIDTH/2) - offset;
  point6_sq.y = ((y_6normal + 1)*HEIGHT/2) - offset;
  point6_sq.w = 20;
  point6_sq.h = 20;
  /* Z axis added formula */ 
  point6_sq.x = (int)((point6_sq.x - cx) / z5 + cx); // back face uses |z_2normal|
  point6_sq.y = (int)((point6_sq.y - cy) / z5 + cy);

  SDL_Rect point7_sq;
  /* Normalization x and y cordenates to just set -1 to 1 and x and y */
  point7_sq.x = ((x_7normal + 1)*WIDTH/2) - offset;
  point7_sq.y = ((y_7normal + 1)*HEIGHT/2) - offset;
  point7_sq.w = 20;
  point7_sq.h = 20;
  /* Z axis added formula */ 
  point7_sq.x = (int)((point7_sq.x - cx) / z5 + cx); // back face uses |z_2normal|
  point7_sq.y = (int)((point7_sq.y - cy) / z5 + cy);

  SDL_Rect point8_sq;
  /* Normalization x and y cordenates to just set -1 to 1 and x and y */
  point8_sq.x = ((x_8normal + 1)*WIDTH/2) - offset;
  point8_sq.y = ((y_8normal + 1)*HEIGHT/2) - offset;
  point8_sq.w = 20;
  point8_sq.h = 20;
  /* Z axis added formula */ 
  point8_sq.x = (int)((point8_sq.x - cx) / z5 + cx); // back face uses |z_2normal|
  point8_sq.y = (int)((point8_sq.y - cy) / z5 + cy);

  /* Point movement animation */
  // Use a fixed number of frames so changing z doesn’t break the loop immediately (keeps your per-point movement)

  for(int i = 0; i < 200; i++){
    SDL_Event event;
      while(SDL_PollEvent(&event)){
        if(event.type == SDL_QUIT){
          *quit = true;
        }
      }
      if(*quit) return;
    /* Point 1 movement */
    point1_sq.x = point1_sq.x - i;
    point1_sq.y = point1_sq.y + i;
    /* Point 2 movement */
    point2_sq.x = point2_sq.x + i;
    point2_sq.y = point2_sq.y + i;
    /* Point 3 movement */
    point3_sq.x = point3_sq.x - i;
    point3_sq.y = point3_sq.y - i;
    /* Point 4 movement */
    point4_sq.x = point4_sq.x + i;
    point4_sq.y = point4_sq.y - i;

    /* Point 5 movement (same as point 1) */
    point5_sq.x = point5_sq.x - i;
    point5_sq.y = point5_sq.y + i;

    /* Point 6 movement (same as point 2) */
    point6_sq.x = point6_sq.x + i;
    point6_sq.y = point6_sq.y + i;
    /* Point 7 movement (same as point 3) */
    point7_sq.x = point7_sq.x - i;
    point7_sq.y = point7_sq.y - i;
    /* Point 8 movement (same as point 4) */
    point8_sq.x = point8_sq.x + i;
    point8_sq.y = point8_sq.y - i;

    SDL_SetRenderDrawColor(render, GRAY);
    SDL_RenderClear(render);
    SDL_SetRenderDrawColor(render, 255, 255, 255, 255); // Points color
    SDL_RenderFillRect(render, &point1_sq);
    SDL_RenderFillRect(render, &point2_sq);
    SDL_RenderFillRect(render, &point3_sq);
    SDL_RenderFillRect(render, &point4_sq);
    SDL_RenderFillRect(render, &point5_sq);
    SDL_RenderFillRect(render, &point6_sq);
    SDL_RenderFillRect(render, &point7_sq);
    SDL_RenderFillRect(render, &point8_sq);
    SDL_RenderPresent(render);

    SDL_Delay(1000/FPS);
  }
  std::cout << "x initial cordenate point1: " << point1_sq.x << std::endl; 
  std::cout << "y initial cordenate point1: " << point1_sq.y << std::endl;
  std::cout << "x initial cordenate point2: " << point2_sq.x << std::endl;
  std::cout << "y initial cordenate point2: " << point2_sq.y << std::endl;
  std::cout << "x initial cordenate point3: " << point3_sq.x << std::endl;
  std::cout << "y initial cordenate point3: " << point3_sq.y << std::endl;
  std::cout << "x initial cordenate point4: " << point4_sq.x << std::endl;
  std::cout << "y initial cordenate point4: " << point4_sq.y << std::endl;
  std::cout << "x initial cordenate point5: " << point5_sq.x << std::endl;
  std::cout << "y initial cordenate point5: " << point5_sq.y << std::endl;
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
  float flip = -1; // Fliper to flip the y cordentates that posetive values goes up 
  
  bool quit = false;

  while(!quit){
    SDL_Event event;
      while(SDL_PollEvent(&event)){
        if(event.type == SDL_QUIT){
          quit = true;
        }
      }
      // Front face (z_normal): 4 points at z > 0
      // Back face (z_2normal): 4 points at z < 0 (but still projected using |z| so they are visible)
      square(render,
             /* front face */  0.5f , flip * 0.5f,
                               -0.5f, flip * 0.5f,
                                0.5f, flip * -0.5f,
                               -0.5f, flip * -0.5f,
             /* back face  */  0.5f , flip * 0.5f,   // point5: back of point1
                               -0.5f, flip * 0.5f,   // point6: back of point2
                                0.5f, flip * -0.5f,  // point7: back of point3
                               -0.5f, flip * -0.5f,  // point8: back of point4
             /* z values   */  1.0f,  -0.5f,
                                &quit);
      
  }
  SDL_DestroyRenderer(render);
  SDL_DestroyWindow(mainwin);
  SDL_Quit();
  return 0;
}
