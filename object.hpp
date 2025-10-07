#pragma once

#include <fstream>
#include <vector>

#include "vectors.hpp"

typedef struct Triangle Triangle;

struct Triangle {
	Vec3 A;
	Vec3 B;
	Vec3 C;
	int color_code;
};

class Object {
	public:
		Object(std::string pathToFile);

		std::vector<Triangle> tri;
		std::vector<float> vert;
		std::vector<std::vector<int>> vertIndex;

		void RotateX(float angle);
		void RotateY(float angle);
		void RotateZ(float angle);

    void SetRandomColors();
		void SetOffset(Vec3 offset);
		Vec3 GetOffset();

  private:
		Vec3 offset;
};
