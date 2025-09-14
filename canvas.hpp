#pragma once

#include "vectors.hpp"
#include <vector>

class Canvas{
	private:
		int height;
		int width;
		std::vector<std::vector<char>> matrix;

		float fov;
		float aspect_ratio;
		float transform;

		bool IsInTriangle(Vec2 vertex_1, Vec2 vertex_2, Vec2 vertex_3, Vec2 position);
		int LeftRightVector(Vec2 A, Vec2 B, Vec2 P);
    Vec2 ScreenSpacePerspectiveProjection(Vec3 vertex);

	public:
		Canvas();
		~Canvas();

		void DrawTriangle(Vec3 vertex_1, Vec3 vertex_2, Vec3 vertex_3);
    void ChangeFOV(float new_fov);
		void Print();
};
