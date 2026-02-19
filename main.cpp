/* Formula to tralate the 3d square: x = x/z
 *                                   y = y/z
 * Formula to rotate a vector: x' = xcos(angle) - ysin(angle)
 *                             y' = xsin(angle) + ycos(angle)
 */
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
#define FPS 30

static inline void rotateY(float x, float y, float z, float angle_rad,
                           float &x_out, float &y_out, float &z_out) {
 /* Rotate around Y axis so y_out keeps static with the modification of the formula:
 * x' = xcos(angle) - zsin(angle)
 * y' = y
 * z' = xsin(angle) + zcos(angle)
 */
  float c = cosf(angle_rad);
  float s = sinf(angle_rad);
  x_out = x * c - z * s;
  y_out = y; // y_out keep static
  z_out = x * s + z * c; // NOTE: uses z here (not y)

}

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
            float flip,      // keep your Y inversion
            float angle_start, float angle_speed, // rotation parameters
            bool *quit)
{
  float offset = 10; //Offset to senter the square in the middle the square is 20x20 pixels
  // Screen center for perspective scaling around the center
  const float cx = WIDTH * 0.5f;
  const float cy = HEIGHT * 0.5f;

  const float cam_dist = 2.5f;  // Camera distance along increse the number to see the cube far
  const int pt_size = 15; // Point size in pixels
  const float model_scale = 1.0f; // Extra shrink (<1.0) or grow (>1.0) in normalized XY

  /* Point movement animation */
  for(int i = 0; i < 200; i++){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
      if(event.type == SDL_QUIT){
        *quit = true;
      }
    }
    if(*quit) return;

    // current angle for this frame
    float angle = angle_start + i * angle_speed;

    // Front face uses z_normal, back face uses z_2normal
    float r1x, r1y, r1z, r2x, r2y, r2z, r3x, r3y, r3z, r4x, r4y, r4z;
    float r5x, r5y, r5z, r6x, r6y, r6z, r7x, r7y, r7z, r8x, r8y, r8z;

    rotateY(x_normal,  y_normal,  z_normal,  angle, r1x, r1y, r1z);
    rotateY(x2_normal, y2_normal, z_normal,  angle, r2x, r2y, r2z);
    rotateY(x3_normal, y3_normal, z_normal,  angle, r3x, r3y, r3z);
    rotateY(x4_normal, y4_normal, z_normal,  angle, r4x, r4y, r4z);

    rotateY(x_5normal, y_5normal, z_2normal, angle, r5x, r5y, r5z);
    rotateY(x_6normal, y_6normal, z_2normal, angle, r6x, r6y, r6z);
    rotateY(x_7normal, y_7normal, z_2normal, angle, r7x, r7y, r7z);
    rotateY(x_8normal, y_8normal, z_2normal, angle, r8x, r8y, r8z);

    // Convertion to flip the values of y axis
    r1y *= flip; r2y *= flip; r3y *= flip; r4y *= flip;
    r5y *= flip; r6y *= flip; r7y *= flip; r8y *= flip;

    // Growing of the model in normalized space
    r1x *= model_scale; r1y *= model_scale;
    r2x *= model_scale; r2y *= model_scale;
    r3x *= model_scale; r3y *= model_scale;
    r4x *= model_scale; r4y *= model_scale;
    r5x *= model_scale; r5y *= model_scale;
    r6x *= model_scale; r6y *= model_scale;
    r7x *= model_scale; r7y *= model_scale;
    r8x *= model_scale; r8y *= model_scale;

    SDL_Rect point1_sq;
    /* Normalization x and y cordenates to just set -1 to 1 and x and y */
    point1_sq.x = ((r1x + 1)*WIDTH/2) - offset;
    point1_sq.y = ((r1y + 1)*HEIGHT/2) - offset;
    point1_sq.w = pt_size;
    point1_sq.h = pt_size;
    /* Z axis added formula */ 
    { float denom = fabsf(cam_dist + r1z); if (denom < 0.001f) denom = 0.001f;
      point1_sq.x = (int)((point1_sq.x - cx) / denom + cx);
      point1_sq.y = (int)((point1_sq.y - cy) / denom + cy);
    }

    SDL_Rect point2_sq;
    /* Normalization x and y cordenates to just set -1 to 1 and x and y */
    point2_sq.x = ((r2x + 1)*WIDTH/2) - offset;
    point2_sq.y = ((r2y + 1)*HEIGHT/2) - offset;
    point2_sq.w = pt_size;
    point2_sq.h = pt_size;
    /* Z axis added formula */ 
    { float denom = fabsf(cam_dist + r2z); if (denom < 0.001f) denom = 0.001f;
      point2_sq.x = (int)((point2_sq.x - cx) / denom + cx);
      point2_sq.y = (int)((point2_sq.y - cy) / denom + cy);
    }

    SDL_Rect point3_sq;
    /* Normalization x and y cordenates to just set -1 to 1 and x and y */
    point3_sq.x = ((r3x + 1)*WIDTH/2) - offset;
    point3_sq.y = ((r3y + 1)*HEIGHT/2) - offset;
    point3_sq.w = pt_size;
    point3_sq.h = pt_size;
    /* Z axis added formula */ 
    { float denom = fabsf(cam_dist + r3z); if (denom < 0.001f) denom = 0.001f;
      point3_sq.x = (int)((point3_sq.x - cx) / denom + cx);
      point3_sq.y = (int)((point3_sq.y - cy) / denom + cy);
    }

    SDL_Rect point4_sq;
    /* Normalization x and y cordenates to just set -1 to 1 and x and y */
    point4_sq.x = ((r4x + 1)*WIDTH/2) - offset;
    point4_sq.y = ((r4y + 1)*HEIGHT/2) - offset;
    point4_sq.w = pt_size;
    point4_sq.h = pt_size;
    /* Z axis added formula */ 
    { float denom = fabsf(cam_dist + r4z); if (denom < 0.001f) denom = 0.001f;
      point4_sq.x = (int)((point4_sq.x - cx) / denom + cx);
      point4_sq.y = (int)((point4_sq.y - cy) / denom + cy);
    }

    SDL_Rect point5_sq;
    /* Normalization x and y cordenates to just set -1 to 1 and x and y */
    point5_sq.x = ((r5x + 1)*WIDTH/2) - offset;
    point5_sq.y = ((r5y + 1)*HEIGHT/2) - offset;
    point5_sq.w = pt_size;
    point5_sq.h = pt_size;
    /* Z axis added formula */ 
    { float denom = fabsf(cam_dist + r5z); if (denom < 0.001f) denom = 0.001f;
      point5_sq.x = (int)((point5_sq.x - cx) / denom + cx);
      point5_sq.y = (int)((point5_sq.y - cy) / denom + cy);
    }

    SDL_Rect point6_sq;
    /* Normalization x and y cordenates to just set -1 to 1 and x and y */
    point6_sq.x = ((r6x + 1)*WIDTH/2) - offset;
    point6_sq.y = ((r6y + 1)*HEIGHT/2) - offset;
    point6_sq.w = pt_size;
    point6_sq.h = pt_size;
    /* Z axis added formula */ 
    { float denom = fabsf(cam_dist + r6z); if (denom < 0.001f) denom = 0.001f;
      point6_sq.x = (int)((point6_sq.x - cx) / denom + cx);
      point6_sq.y = (int)((point6_sq.y - cy) / denom + cy);
    }

    SDL_Rect point7_sq;
    /* Normalization x and y cordenates to just set -1 to 1 and x and y */
    point7_sq.x = ((r7x + 1)*WIDTH/2) - offset;
    point7_sq.y = ((r7y + 1)*HEIGHT/2) - offset;
    point7_sq.w = pt_size;
    point7_sq.h = pt_size;
    /* Z axis added formula */ 
    { float denom = fabsf(cam_dist + r7z); if (denom < 0.001f) denom = 0.001f;
      point7_sq.x = (int)((point7_sq.x - cx) / denom + cx);
      point7_sq.y = (int)((point7_sq.y - cy) / denom + cy);
    }

    SDL_Rect point8_sq;
    /* Normalization x and y cordenates to just set -1 to 1 and x and y */
    point8_sq.x = ((r8x + 1)*WIDTH/2) - offset;
    point8_sq.y = ((r8y + 1)*HEIGHT/2) - offset;
    point8_sq.w = pt_size;
    point8_sq.h = pt_size;
    /* Z axis added formula */ 
    { float denom = fabsf(cam_dist + r8z); if (denom < 0.001f) denom = 0.001f;
      point8_sq.x = (int)((point8_sq.x - cx) / denom + cx);
      point8_sq.y = (int)((point8_sq.y - cy) / denom + cy);
    }

    /* Parameters to draw a lines between points
     * Fron face*/
    int point1_connectionx = point1_sq.x + point1_sq.w/2;
    int point1_connectiony = point1_sq.y + point1_sq.h/2;
    int point2_connectionx = point2_sq.x + point2_sq.w/2;
    int point2_connectiony = point2_sq.y + point2_sq.h/2;
    int point3_connectionx = point3_sq.x + point3_sq.w/2;
    int point3_connectiony = point3_sq.y + point3_sq.h/2;
    int point4_connectionx = point4_sq.x + point4_sq.w/2;
    int point4_connectiony = point4_sq.y + point4_sq.h/2;
    /*Back face */
    int point5_connectionx = point5_sq.x + point5_sq.w/2;
    int point5_connectiony = point5_sq.y + point5_sq.h/2;
    int point6_connectionx = point6_sq.x + point6_sq.w/2;
    int point6_connectiony = point6_sq.y + point6_sq.h/2;
    int point7_connectionx = point7_sq.x + point7_sq.w/2;
    int point7_connectiony = point7_sq.y + point7_sq.h/2;
    int point8_connectionx = point8_sq.x + point8_sq.w/2;
    int point8_connectiony = point8_sq.y + point8_sq.h/2;
    /* Drawing the points */
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
    /*Drawing lines */
    /*Conections in the front face*/
    SDL_RenderDrawLine(render, point1_connectionx, point1_connectiony, 
                               point2_connectionx, point2_connectiony); // Drawing the line between the point 1 and point 2
    SDL_RenderDrawLine(render, point1_connectionx, point1_connectiony,
                               point3_connectionx, point3_connectiony); // Line between point 1 and point point 3
    SDL_RenderDrawLine(render, point3_connectionx, point3_connectiony, 
                               point4_connectionx, point4_connectiony); // Line between point 3 and point 4
    SDL_RenderDrawLine(render, point4_connectionx, point4_connectiony,
                               point2_connectionx, point2_connectiony); // Line between point 4 and point 2
    /*Connections in the back face*/
    SDL_RenderDrawLine(render, point5_connectionx, point5_connectiony,
                               point6_connectionx, point6_connectiony); // Line between point 6 and point 6
    SDL_RenderDrawLine(render, point5_connectionx, point5_connectiony,
                               point7_connectionx, point7_connectiony); // Line between point 5 and point 7
    SDL_RenderDrawLine(render, point7_connectionx, point7_connectiony,
                               point8_connectionx, point8_connectiony); // Line between point 7 and point 8
    SDL_RenderDrawLine(render, point8_connectionx, point8_connectiony, 
                               point6_connectionx, point6_connectiony); // Line between point 8 and point 6
    /*Conections between faces*/
    SDL_RenderDrawLine(render, point1_connectionx, point1_connectiony,
                               point5_connectionx, point5_connectiony); // Line between point 1 and point 5
    SDL_RenderDrawLine(render, point2_connectionx, point2_connectiony, 
                               point6_connectionx, point6_connectiony); // Line between point 2 and point 6
    SDL_RenderDrawLine(render, point3_connectionx, point3_connectiony, 
                               point7_connectionx, point7_connectiony); // Line between point 3 and point 7
    SDL_RenderDrawLine(render, point4_connectionx, point4_connectiony,
                               point8_connectionx, point8_connectiony); // Line between point 4 and point 8
    SDL_RenderPresent(render);


    SDL_Delay(1000/FPS);
  }
}

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
