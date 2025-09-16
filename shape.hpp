#pragma once

#include <vector>
#include "vectors.hpp"

typedef struct Triangle Triangle;

struct Triangle {
	Vec3 A;
	Vec3 B;
	Vec3 C;
};

class Shape {
	private:
		std::vector<Triangle> tri;
		Vec3 center;
	public:
		Shape(unsigned int tri_count);

		std::vector<Triangle> GetTriangles();

		void RotateX(float angle);
		void RotateY(float angle);
		void RotateZ(float angle);
};
