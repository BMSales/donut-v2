#include <cstdlib>
#include <unistd.h>
#include <ctime>

#include "canvas.hpp"
#include "object.hpp"
#include "vectors.hpp"

int main(){
	Canvas canvas = Canvas();
	Object shape = Object(30);
	float angle_1 = 1;
	float angle_2 = -1;
	float angle_3 = 0.5;

  while(1){
    canvas.DrawObject(&shape);
    canvas.Print();
    usleep(16*1000);
    canvas.ClearScreen();
    // system("clear");
		shape.RotateX(angle_1);
		shape.RotateY(angle_2);
		shape.RotateZ(angle_3);
  }
}

