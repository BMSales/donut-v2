#include <cmath>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>

#include "object.hpp"

#define M_PI 3.14159265358979323846

Object::Object(std::string pathToFile){
  std::ifstream object_file(pathToFile);
  std::string line;
	std::string objVertex;
	std::string objFace;
  
	Triangle objTriangle;

	int k = 0;

  if(!object_file){
    std::cout << "ERROR: could not open file" << std::endl;
    exit(-1);
  }

  while(getline(object_file, line)){
    if(line.substr(0, 2) == "v "){
			for(int i = 2; line[i] != '\0'; i++){
				objVertex += line[i];
				if(line[i] == ' ' || line[i + 1] == '\0'){
					vert.push_back(stof(objVertex));
					objVertex = "";
				}
			}
    }

		if(line.substr(0, 2) == "f "){
			vertIndex.push_back(std::vector<int>());
			for(int i = 2; line[i] != '\0'; i++){
        objFace += line[i];
				if(line[i] == ' ' || line[i + 1] == '\0'){
					vertIndex[k].push_back(stoi(objFace));
					objFace = "";
				}
			}
			k++;
		}
	}

	int firstVertex;
	if(vertIndex[0][0] < 0){
		firstVertex = - vert.size() / 3;
	}
	else {
		firstVertex = 1;
	}

	for(auto &index : vertIndex){
		objTriangle.A.x = vert[(index[0] - firstVertex) * 3];
		objTriangle.A.y = vert[(index[0] - firstVertex) * 3 + 1];
		objTriangle.A.z = vert[(index[0] - firstVertex) * 3 + 2];

		objTriangle.B.x = vert[(index[1] - firstVertex) * 3];
		objTriangle.B.y = vert[(index[1] - firstVertex) * 3 + 1];
		objTriangle.B.z = vert[(index[1] - firstVertex) * 3 + 2];

		objTriangle.C.x = vert[(index[2] - firstVertex) * 3];
		objTriangle.C.y = vert[(index[2] - firstVertex) * 3 + 1];
		objTriangle.C.z = vert[(index[2] - firstVertex) * 3 + 2];

		tri.push_back(objTriangle);
		if(index.size() > 3){
			for(int i = 3; i < index.size(); i++){
				objTriangle.B = objTriangle.C;
				objTriangle.C.x = vert[(index[i] - firstVertex) * 3];
				objTriangle.C.y = vert[(index[i] - firstVertex) * 3 + 1];
				objTriangle.C.z = vert[(index[i] - firstVertex) * 3 + 2];

				tri.push_back(objTriangle);
			}
		}
	}
}

void Object::SetRandomColors(){
  std::random_device device;
  std::default_random_engine engine(device());
  std::uniform_int_distribution<int> uniform_dist(0, 255);

  for(auto &triangle : tri){
    triangle.color_code = uniform_dist(engine);
  }
}

void Object::SetOffset(Vec3 offset){
	this->offset = offset;
}

Vec3 Object::GetOffset(){
	return offset;
}

void Object::RotateX(float angle){
	float rad = angle * M_PI/180.0;
	float cos_rad = cos(rad);
	float sin_rad = sin(rad);
	Triangle helper_triangle;

	for(auto &triangle : tri){
		helper_triangle = triangle;

		triangle.A.y = helper_triangle.A.y * cos_rad + helper_triangle.A.z * -sin_rad;
		triangle.B.y = helper_triangle.B.y * cos_rad + helper_triangle.B.z * -sin_rad;
		triangle.C.y = helper_triangle.C.y * cos_rad + helper_triangle.C.z * -sin_rad;

		triangle.A.z = helper_triangle.A.y * sin_rad + helper_triangle.A.z * cos_rad;
		triangle.B.z = helper_triangle.B.y * sin_rad + helper_triangle.B.z * cos_rad;
		triangle.C.z = helper_triangle.C.y * sin_rad + helper_triangle.C.z * cos_rad;
	}
}

void Object::RotateY(float angle){
	float rad = angle * M_PI/180.0;
	float cos_rad = cos(rad);
	float sin_rad = sin(rad);
	Triangle helper_triangle;

	for(auto &triangle : tri){
		helper_triangle = triangle;

		triangle.A.x = helper_triangle.A.x * cos_rad + helper_triangle.A.z * sin_rad;
		triangle.B.x = helper_triangle.B.x * cos_rad + helper_triangle.B.z * sin_rad;
		triangle.C.x = helper_triangle.C.x * cos_rad + helper_triangle.C.z * sin_rad;

		triangle.A.z = helper_triangle.A.x * -sin_rad + helper_triangle.A.z * cos_rad;
		triangle.B.z = helper_triangle.B.x * -sin_rad + helper_triangle.B.z * cos_rad;
		triangle.C.z = helper_triangle.C.x * -sin_rad + helper_triangle.C.z * cos_rad;
	}
}

void Object::RotateZ(float angle){
	float rad = angle * M_PI/180.0;
	float cos_rad = cos(rad);
	float sin_rad = sin(rad);
	Triangle helper_triangle;

	for(auto &triangle : tri){
		helper_triangle = triangle;

		triangle.A.x = helper_triangle.A.x * cos_rad + helper_triangle.A.y * -sin_rad;
		triangle.B.x = helper_triangle.B.x * cos_rad + helper_triangle.B.y * -sin_rad;
		triangle.C.x = helper_triangle.C.x * cos_rad + helper_triangle.C.y * -sin_rad;

		triangle.A.y = helper_triangle.A.x * sin_rad + helper_triangle.A.y * cos_rad;
		triangle.B.y = helper_triangle.B.x * sin_rad + helper_triangle.B.y * cos_rad;
		triangle.C.y = helper_triangle.C.x * sin_rad + helper_triangle.C.y * cos_rad;
	}
}
