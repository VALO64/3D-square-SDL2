## This is just a practice of my c++ language skills 

Randomly one day I thought that It could be fun if I just code 3D objects just using C and the SDL2 library so I started with the typical 2D square and I started to think how could I success my goal. Idk how YT just recommended me a video https://www.youtube.com/watch?v=qjWkNZ0SXfo but he was using HTML so I had to think in how to use it on C++ so I watch the video tons of times until I got it.

## Process.

We can draw 3D graphics with points in 2 axis, and using a formula to make them 3D, in my case I decided to draw 8 points but those points need to be translated in a specific way 
<img width="804" height="533" alt="image" src="https://github.com/user-attachments/assets/d207af65-3be0-439a-a0ca-7eb55ccfc15b" />

SDL works in pixels but we had to work in a central point with +- 1 x axis and +- 1 y axis, you can check that part in main.cpp and try drawing the points, when you finish to draw and test the points, we can add z axis that will be the projection the blue line on the picture being 
```
x = x/z
y = y/z
```

With this you can project an 3D object on 2D graphics.

To rotate you just have to use the following formula.
```
  x' = xcos(angle) - zsin(angle)
  y' = y
  z' = xsin(angle) + zcos(angle)
```

You can find more information in this post: https://math.stackexchange.com/questions/2305792/3d-projection-on-a-2d-plane-weak-maths-ressources

## Demostration


https://github.com/user-attachments/assets/0c6d5854-7efa-4211-9646-755c664d1379

