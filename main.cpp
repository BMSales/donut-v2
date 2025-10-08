#include <cstdlib>
#include <iostream>
#include <unistd.h>

#include "canvas.hpp"
#include "object.hpp"
#include "vectors.hpp"

int main(int argc, char* argv[]){
  if(argc < 2){
    std::cout << "Must inform path to object" << std::endl;
    return 1;
  }

	Canvas canvas = Canvas();
	Object object = Object(argv[1]);
  object.SetRandomColors();
	float z = 3.0;
	object.SetOffset({0.0, 0.0, z});
	float angle_1 = 0.5;
	float angle_2 = -0.9;
	float angle_3 = 0.3;

  while(1){
    canvas.DrawObject(&object);
    canvas.Print();
    usleep(16*1000);
    canvas.ClearScreen();
		object.RotateX(angle_1);
		object.RotateY(angle_2);
		object.RotateZ(angle_3);
  }
}
