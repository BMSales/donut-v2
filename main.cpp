#include <cstdlib>
#include <iostream>
#include <string>
#include <unistd.h>

#include "canvas.hpp"
#include "linear-algebra.hpp"
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

  Canvas canvas = Canvas();
  Object object = Object(pathToObject);
  object.SetRandomColors();
  float angle_1 = 0.0;
  float angle_2 = 0.0;
  float angle_3 = 0.0;
  float far = 100.0;
  float near = 1.0;
  float z = 4.0;

  Matrix translation = Matrix();
  Matrix scaling = Matrix();
  Matrix rotationX = Matrix();
  Matrix rotationY = Matrix();
  Matrix rotationZ = Matrix();
  Matrix perspectiveProj = Matrix();
  Matrix screenSpace = Matrix();

  translation.Translation(0, 0, z);
  scaling.Scaling(1, 1, 1);
  rotationX.RotationX(angle_1);
  rotationY.RotationY(angle_2);
  rotationZ.RotationZ(angle_3);
  perspectiveProj.PerspectiveProjection(45.0, (float)canvas.GetWidth()/(float)canvas.GetHeight(), far, near);
  screenSpace.ScreenSpace(canvas.GetWidth(), canvas.GetHeight());

  canvas.SetTransformations(translation, scaling, rotationX, rotationY, rotationZ, perspectiveProj, screenSpace);

  while(1){
    canvas.DrawObject(&object);
    canvas.Print();

    rotationX.RotationX(angle_1);
    rotationY.RotationY(angle_2);
    rotationZ.RotationZ(angle_3);
    perspectiveProj.PerspectiveProjection(45.0, (float)canvas.GetWidth()/(float)canvas.GetHeight(), far, near);

    canvas.SetTransformations(translation, scaling, rotationX, rotationY, rotationZ, perspectiveProj, screenSpace);

    usleep(16*1000);
    canvas.ClearScreen();
    angle_1 += 1.0;
    angle_2 -= 0.3;
    angle_3 += 0.1;
  }
}
