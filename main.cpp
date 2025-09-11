#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "canvas.hpp"

int main(){
	Canvas canvas = Canvas();
  float x = 0.0;
  float y = 0.0;
  float z = 100.0;

  while(1){
    canvas.PerspectiveProjection(x, y, z);
    canvas.Print();
    usleep(16*1000);
    system("clear");
    x += 0.5;
    y += 0.5;
  }
}

