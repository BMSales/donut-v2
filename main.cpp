#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "canvas.hpp"

int main(){
	Canvas canvas = Canvas();
  float vertex_1[3] = {0.0, 50.0, 100.0};
  float vertex_2[3] = {50.0, -50.0, 100.0};
  float vertex_3[3] = {-50.0, -50.0, 100.0};
  float fov = 30.0;

  canvas.ChangeFOV(fov);
  

  while(1){
    canvas.DrawTriangle(vertex_1, vertex_2, vertex_3);
    canvas.Print();
    canvas.ChangeFOV(fov);
    usleep(16*1000);
    system("clear");
    // vertex_1[1] -= 0.1;
    // fov += 1.0;
  }
}

