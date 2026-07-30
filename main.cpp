#include <cstdlib>
#include <iostream>
#include <string>
#include <unistd.h>

#include "camera.hpp"
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

  Camera camera = Camera();
  Object object = Object(pathToObject);
  object.SetRandomColors();
  float angle_1 = 0.0;
  float angle_2 = 0.0;
  float angle_3 = 0.0;
  float far = 100.0;
  float near = 1.0;
  float z = 3.0;

  Matrix scaling = Matrix();
  Matrix rotationX = Matrix();
  Matrix rotationY = Matrix();
  Matrix rotationZ = Matrix();
  Matrix translation = Matrix();
  Matrix perspectiveProj = Matrix();
  Matrix screenSpace = Matrix();

  scaling.Scaling(1, 1, 1);
  rotationX.RotationX(angle_1);
  rotationY.RotationY(angle_2);
  rotationZ.RotationZ(angle_3);
  translation.Translation(0, 0, z);
  perspectiveProj.PerspectiveProjection(30.0, (float)camera.GetWidth()/(float)camera.GetHeight(), far, near);
  screenSpace.ScreenSpace(camera.GetWidth(), camera.GetHeight());

  camera.SetTransformations(translation, scaling, rotationX, rotationY, rotationZ, perspectiveProj, screenSpace);

  while(1){
    camera.DrawObject(&object);
    camera.Print();

    rotationX.RotationX(angle_1);
    rotationY.RotationY(angle_2);
    rotationZ.RotationZ(angle_3);
    perspectiveProj.PerspectiveProjection(45.0, (float)camera.GetWidth()/(float)camera.GetHeight(), far, near);

    camera.SetTransformations(translation, scaling, rotationX, rotationY, rotationZ, perspectiveProj, screenSpace);

    usleep(16*1000);
    camera.ClearScreen();
    angle_1 += 1.0;
    angle_2 -= 0.3;
    angle_3 += 0.1;
  }
}
