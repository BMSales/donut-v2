#include <cstdlib>
#include <unistd.h>
#include <ctime>

#include "canvas.hpp"
#include "shape.hpp"
#include "vectors.hpp"

int main(){
	Canvas canvas = Canvas();
	Shape shape = Shape(1000);
	float angle = 1;

  while(1){
    canvas.DrawShape(&shape);
    canvas.Print();
    usleep(16*1000);
    canvas.ClearScreen();
    // system("clear");
		shape.RotateY(angle);
  }
}

