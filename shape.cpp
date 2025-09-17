#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include "shape.hpp"

#define M_PI 3.14159265358979323846

int NegPos(){
	int value = std::rand() % 2;
	if(value == 0){
		return 1;
	}
	return -1;
}

Shape::Shape(unsigned int tri_count){
  std::srand(std::time(0));
  Triangle triangle;
 
  triangle.A.x = 0.0;
  triangle.B.x = 20.0;
  triangle.C.x = -20.0;

  triangle.A.y = 20.0;
  triangle.B.y = -20.0;
  triangle.C.y = -20.0;

  triangle.A.z = 50.0;
  triangle.B.z = 50.0;
  triangle.C.z = 50.0;

	for(int i = 0; i < tri_count; i++){
    tri.push_back(triangle);

    triangle.A.x = 1 + NegPos() * (std::rand() % 31);
    triangle.B.x = 1 + NegPos() * (std::rand() % 31);
    triangle.C.x = 1 + NegPos() * (std::rand() % 31);

    triangle.A.y = 1 + NegPos() * (std::rand() % 31);
    triangle.B.y = 1 + NegPos() * (std::rand() % 31);
    triangle.C.y = 1 + NegPos() * (std::rand() % 31);

    triangle.A.z = 40 + (std::rand() % 31);
    triangle.B.z = 40 + (std::rand() % 31);
    triangle.C.z = 40 + (std::rand() % 31);
    
	}

	for(auto &triangle : tri){
		center.x += (triangle.A.x + triangle.B.x + triangle.C.x);
		center.y += (triangle.A.y + triangle.B.y + triangle.C.y);
		center.z += (triangle.A.z + triangle.B.z + triangle.C.z);
	}

	center.x /= tri_count * 3;
	center.y /= tri_count * 3;
	center.z /= tri_count * 3;

}

Triangle Shape::GetTriangle(unsigned int index){
  if(index > tri.size() - 1){
    std::cout << "invalid index" << std::endl;
    exit(-1);
  }
	return tri[index];
}

void Shape::RotateX(float angle){
	float rad = angle * M_PI/180.0;
	float cos_rad = cos(rad);
	float sin_rad = sin(rad);

	for(auto &triangle : tri){
		triangle.A = triangle.A - center;
		triangle.B = triangle.B - center;
		triangle.C = triangle.C - center;
	}

	for(auto &triangle : tri){
		triangle.A.y = triangle.A.y * cos_rad + triangle.A.z * -sin_rad;
		triangle.B.y = triangle.B.y * cos_rad + triangle.B.z * -sin_rad;
		triangle.C.y = triangle.C.y * cos_rad + triangle.C.z * -sin_rad;

		triangle.A.z = triangle.A.y * sin_rad + triangle.A.z * cos_rad;
		triangle.B.z = triangle.B.y * sin_rad + triangle.B.z * cos_rad;
		triangle.C.z = triangle.C.y * sin_rad + triangle.C.z * cos_rad;
	}

	for(auto& triangle : tri){
		triangle.A = triangle.A + center;
		triangle.B = triangle.B + center;
		triangle.C = triangle.C + center;
	}
}

void Shape::RotateY(float angle){
	float rad = angle * M_PI/180.0;
	float cos_rad = cos(rad);
	float sin_rad = sin(rad);

	for(auto &triangle : tri){
		triangle.A = triangle.A - center;
		triangle.B = triangle.B - center;
		triangle.C = triangle.C - center;
	}

	for(auto &triangle : tri){
		triangle.A.x = triangle.A.x * cos_rad + triangle.A.z * -sin_rad;
		triangle.B.x = triangle.B.x * cos_rad + triangle.B.z * -sin_rad;
		triangle.C.x = triangle.C.x * cos_rad + triangle.C.z * -sin_rad;

		triangle.A.z = triangle.A.x * sin_rad + triangle.A.z * cos_rad;
		triangle.B.z = triangle.B.x * sin_rad + triangle.B.z * cos_rad;
		triangle.C.z = triangle.C.x * sin_rad + triangle.C.z * cos_rad;
	}

	for(auto& triangle : tri){
		triangle.A = triangle.A + center;
		triangle.B = triangle.B + center;
		triangle.C = triangle.C + center;
	}
}

void Shape::RotateZ(float angle){
	float rad = angle * M_PI/180.0;
	float cos_rad = cos(rad);
	float sin_rad = sin(rad);

	for(auto &triangle : tri){
		triangle.A = triangle.A - center;
		triangle.B = triangle.B - center;
		triangle.C = triangle.C - center;
	}

	for(auto &triangle : tri){
		triangle.A.x = triangle.A.x * cos_rad + triangle.A.y * -sin_rad;
		triangle.B.x = triangle.B.x * cos_rad + triangle.B.y * -sin_rad;
		triangle.C.x = triangle.C.x * cos_rad + triangle.C.y * -sin_rad;

		triangle.A.y = triangle.A.x * sin_rad + triangle.A.y * cos_rad;
		triangle.B.y = triangle.B.x * sin_rad + triangle.B.y * cos_rad;
		triangle.C.y = triangle.C.x * sin_rad + triangle.C.y * cos_rad;
	}

	for(auto& triangle : tri){
		triangle.A = triangle.A + center;
		triangle.B = triangle.B + center;
		triangle.C = triangle.C + center;
	}
}
