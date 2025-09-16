#pragma once

#include "vectors.hpp"
#include "shape.hpp"
#include <vector>

class Canvas{
  public:
		Canvas();

		void DrawShape(Shape shape);
    void ChangeFOV(float new_fov);
		void Print();

	private:
		int height;
		int width;
		std::vector<std::vector<char>> matrix;

		float fov;
		float aspect_ratio;
		float transform;

		bool IsInTriangle(Vec2 vertex_1, Vec2 vertex_2, Vec2 vertex_3, Vec2 position);
		bool AABB_Collision(int min_x, int max_x, int min_y, int max_y);

		int LeftRightVector(Vec2 A, Vec2 B, Vec2 P);
    Vec2 ScreenSpacePerspectiveProjection(Vec3 vertex);
		void DrawTriangle(Triangle triangle);

};
