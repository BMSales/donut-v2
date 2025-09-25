#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

#include "object.hpp"

#define M_PI 3.14159265358979323846

Object::Object(std::string pathToFile){
  std::ifstream object_file(pathToFile);
  std::string line;
	std::string objVertex;
	std::string objFace;

	int k = 0;

  if(!object_file){
    std::cout << "ERROR: could not open file" << std::endl;
    exit(-1);
  }

  while(getline(object_file, line)){

    if(line.substr(0, 2) == "v "){
			for(int i = 2; line[i] != '\0'; i++){
				objVertex += line[i];
				if(line[i] == ' ' && objVertex != " "){
					vert.push_back(stof(objVertex));
					objVertex = "";
				}
			}
    }

		if(line.substr(0, 2) == "f "){
			vertIndex.push_back(std::vector<int>());
			for(int i = 2; line[i] != '\0'; i++){
				if(objFace == "" || objFace == "-"){
					objFace += line[i];
				}
				else if(line[i] == ' ' || line[i + 1] == '\0'){
					vertIndex[k].push_back(stoi(objFace));
					objFace = "";
				}
			}
			k++;
		}
	}

	// for(auto &indexes : vertIndex){
	// }

	for(auto &vertex : vert){
		std::cout << vertex << std::endl;
	}
}

void Object::RotateX(float angle){
	float rad = angle * M_PI/180.0;
	float cos_rad = cos(rad);
	float sin_rad = sin(rad);

	for(auto &triangle : tri){
		triangle.A = triangle.A - offset;
		triangle.B = triangle.B - offset;
		triangle.C = triangle.C - offset;
	}

	for(auto &triangle : tri){
		triangle.A.y = triangle.A.y * cos_rad + triangle.A.z * -sin_rad;
		triangle.B.y = triangle.B.y * cos_rad + triangle.B.z * -sin_rad;
		triangle.C.y = triangle.C.y * cos_rad + triangle.C.z * -sin_rad;

		triangle.A.z = triangle.A.y * sin_rad + triangle.A.z * cos_rad;
		triangle.B.z = triangle.B.y * sin_rad + triangle.B.z * cos_rad;
		triangle.C.z = triangle.C.y * sin_rad + triangle.C.z * cos_rad;
	}

	for(auto &triangle : tri){
		triangle.A = triangle.A + offset;
		triangle.B = triangle.B + offset;
		triangle.C = triangle.C + offset;
	}
}

void Object::RotateY(float angle){
	float rad = angle * M_PI/180.0;
	float cos_rad = cos(rad);
	float sin_rad = sin(rad);

	for(auto &triangle : tri){
		triangle.A = triangle.A - offset;
		triangle.B = triangle.B - offset;
		triangle.C = triangle.C - offset;
	}

	for(auto &triangle : tri){
		triangle.A.x = triangle.A.x * cos_rad + triangle.A.z * -sin_rad;
		triangle.B.x = triangle.B.x * cos_rad + triangle.B.z * -sin_rad;
		triangle.C.x = triangle.C.x * cos_rad + triangle.C.z * -sin_rad;

		triangle.A.z = triangle.A.x * sin_rad + triangle.A.z * cos_rad;
		triangle.B.z = triangle.B.x * sin_rad + triangle.B.z * cos_rad;
		triangle.C.z = triangle.C.x * sin_rad + triangle.C.z * cos_rad;
	}

	for(auto &triangle : tri){
		triangle.A = triangle.A + offset;
		triangle.B = triangle.B + offset;
		triangle.C = triangle.C + offset;
	}
}

void Object::RotateZ(float angle){
	float rad = angle * M_PI/180.0;
	float cos_rad = cos(rad);
	float sin_rad = sin(rad);

	for(auto &triangle : tri){
		triangle.A = triangle.A - offset;
		triangle.B = triangle.B - offset;
		triangle.C = triangle.C - offset;
	}

	for(auto &triangle : tri){
		triangle.A.x = triangle.A.x * cos_rad + triangle.A.y * -sin_rad;
		triangle.B.x = triangle.B.x * cos_rad + triangle.B.y * -sin_rad;
		triangle.C.x = triangle.C.x * cos_rad + triangle.C.y * -sin_rad;

		triangle.A.y = triangle.A.x * sin_rad + triangle.A.y * cos_rad;
		triangle.B.y = triangle.B.x * sin_rad + triangle.B.y * cos_rad;
		triangle.C.y = triangle.C.x * sin_rad + triangle.C.y * cos_rad;
	}

	for(auto &triangle : tri){
		triangle.A = triangle.A + offset;
		triangle.B = triangle.B + offset;
		triangle.C = triangle.C + offset;
	}
}
