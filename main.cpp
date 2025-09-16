#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "canvas.hpp"
#include "shape.hpp"
#include "vectors.hpp"

int main(){
	Canvas canvas = Canvas();
	Shape shape = Shape(1);
	float angle = 1;
  Vec3 vertex_1 = {0.0, 50.0, 100.0};
  Vec3 vertex_2 = {50.0, -50.0, 100.0};
  Vec3 vertex_3 = {-50.0, -50.0, 100.0};

  while(1){
		// canvas.DrawTriangle((Triangle){vertex_1,vertex_2,vertex_3});
    canvas.DrawShape(shape);
    canvas.Print();
    usleep(16*1000);
    system("clear");
		// shape.RotateY(angle);
  }
}

