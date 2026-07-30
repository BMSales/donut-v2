#pragma once

#include <string>
#include <vector>

#include "vectors.hpp"
#include "linear-algebra.hpp"
#include "object.hpp"

class Camera {
public:
	Camera();

	void DrawObject(Object*);
	void Print();
	void ClearScreen();

	int GetHeight();
	int GetWidth();
	void SetTransformations(Matrix, Matrix, Matrix, Matrix, Matrix, Matrix, Matrix);
	void SetFOV(float);

private:
	int height;
	int width;
	std::vector<std::vector<int>> screen;
	std::vector<std::vector<float>> z_buffer;
	std::vector<int> bw_color_code;
	float fov;
	float aspect_ratio;
	Matrix transformations[6];

	bool CanDrawPixel(Triangle, Vec4);
	bool AABB_Collision(int, int, int, int);

	int DepthMap(int, int);
	int Lighting(Triangle, Vec3);

	float SignedTriangleArea(Triangle);
	void DrawTriangle(Triangle);
};
