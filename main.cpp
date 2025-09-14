#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "canvas.hpp"
#include "vectors.hpp"

int main(){
	Canvas canvas = Canvas();
  Vec3 vertex_1 = {0.0, 50.0, 100.0};
  Vec3 vertex_2 = {50.0, -50.0, 100.0};
  Vec3 vertex_3 = {-50.0, -50.0, 100.0};

  while(1){
    canvas.DrawTriangle(vertex_1, vertex_2, vertex_3);
    canvas.Print();
    usleep(16*1000);
    system("clear");
  }
}

