#include <cstdlib>
#include <unistd.h>
#include <ctime>

#include "canvas.hpp"
#include "object.hpp"
#include "vectors.hpp"

int main(){
	Canvas canvas = Canvas();
	Object object = Object("./monkey/Suzanne.obj");
	float z = 0.0;
	object.setOffset({0.0, 0.0, z});
	float angle_1 = 1;
	float angle_2 = -0.5;
	float angle_3 = 0.5;

  while(1){
    canvas.DrawObject(&object);
    canvas.Print();
    usleep(16*1000);
    canvas.ClearScreen();
		object.RotateX(angle_1);
		object.RotateY(angle_2);
		z += 0.01;
		object.setOffset({0.0, 0.0, z});
		// object.RotateZ(angle_3);
  }
}

