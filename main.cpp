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

  // while(1){
    canvas.PerspectiveProjection(vertex_1, vertex_2, vertex_3);
    canvas.Print();
    usleep(16*1000);
    // system("clear");
  // }
}

