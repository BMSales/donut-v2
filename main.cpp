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
	float angle = 0.0;

	Matrix translation = Matrix();
	Matrix scaling = Matrix();
	Matrix rotationX = Matrix();
	Matrix rotationY = Matrix();
	Matrix rotationZ = Matrix();
	Matrix perspectiveProj = Matrix();
	Matrix screenSpace = Matrix();

	translation.Translation(0, 0, 10);
	scaling.Scaling(1, 1, 1);
	rotationX.RotationX(1);
	rotationY.RotationY(1);
	rotationZ.RotationZ(1);
	perspectiveProj.PerspectiveProjection(45, (float)canvas.GetWidth()/(float)canvas.GetHeight(), 1000, 1);
	screenSpace.ScreenSpace(canvas.GetWidth(), canvas.GetHeight());

	canvas.SetTransformations(translation, scaling, rotationX, rotationY, rotationZ, perspectiveProj, screenSpace);

	while(1){
		canvas.DrawObject(&object);
		canvas.Print();
		rotationX.RotationX(angle);
		canvas.SetTransformations(translation, scaling, rotationX, rotationY, rotationZ, perspectiveProj, screenSpace);
		usleep(16*1000);
		canvas.ClearScreen();
		angle = angle + 0.1;
	}
}
