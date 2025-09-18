#pragma once

#include <fstream>
#include <vector>

#include "vectors.hpp"

typedef struct Triangle Triangle;

struct Triangle {
	Vec3 A;
	Vec3 B;
	Vec3 C;
};

class Object {
	public:
		Object(std::stream pathToFile);

		std::vector<Triangle> tri;
		Triangle GetTriangle(unsigned int index);

		void RotateX(float angle);
		void RotateY(float angle);
		void RotateZ(float angle);

  private:
		Vec3 offset;
};
