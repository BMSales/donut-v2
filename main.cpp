#include <cstdlib>
#include <iostream>
#include <string>
#include <unistd.h>

#include "canvas.hpp"
#include "object.hpp"
#include "vectors.hpp"

int main(int argc, char* argv[]){
	std::string pathToObject;
  if(argc < 2){
    std::cout << "Must inform path to object" << std::endl;
    return 1;
  }
	else {
		pathToObject = argv[1];
	}

	float fov = 45;
	float z = 4.0;
  float angle_1 = 0.5;
  float angle_2 = 180;
  float angle_3 = 0.3;

  Canvas canvas = Canvas();
  Object object = Object(pathToObject);
	canvas.SetFOV(fov);
  object.SetRandomColors();
  object.SetOffset({0.0, 0.0, z});
	object.RotateY(angle_2);

  while(1){
    canvas.DrawObject(&object);
    canvas.Print();
    usleep(16*1000);
    canvas.ClearScreen();
    // object.RotateX(angle_1);
    object.RotateY(angle_2);
    // object.RotateZ(angle_3);
  }
}
