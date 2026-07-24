#pragma once

#include <fstream>
#include <vector>

#include "vectors.hpp"

typedef struct Triangle Triangle;

struct Triangle {
	Vec4 A;
	Vec4 B;
	Vec4 C;
	Vec3 normal;
	int color_code;
};

class Object {
public:
	std::vector<Triangle> tri;

	Object(std::string pathToFile);

	void SetRandomColors();

private:
	std::vector<float> vert;
	std::vector<float> texture;
	std::vector<float> faceNormal;
	std::vector<std::vector<int>> vertIndex;
	std::vector<std::vector<int>> textureIndex;
	std::vector<std::vector<int>> normIndex;

};
