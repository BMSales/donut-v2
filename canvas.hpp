#pragma once

#include <string>
#include <vector>

#include "vectors.hpp"
#include "object.hpp"

class Canvas {
  public:
		Canvas();

		void DrawObject(Object* object);
    void ChangeFOV(float new_fov);
		void Print();
    void ClearScreen();

	private:
		int height;
		int width;
		std::vector<std::vector<int>> screen;

		float fov;
		float aspect_ratio;
		float transform;

		bool IsInTriangle(Vec2 vertex_1, Vec2 vertex_2, Vec2 vertex_3, Vec2 position);
		bool AABB_Collision(int min_x, int max_x, int min_y, int max_y);

		float LeftRightVector(Vec2 A, Vec2 B, Vec2 P);
    Vec2 ScreenSpacePerspectiveProjection(Vec3 vertex);
		void DrawTriangle(Triangle* triangle);
};
