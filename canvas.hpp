#pragma once

#include <string>
#include <vector>

#include "vectors.hpp"
#include "object.hpp"

class Canvas {
  public:
    Canvas();

    void DrawObject(Object* object);
    void SetFOV(float new_fov);
    void Print();
    void ClearScreen();

  private:
    int height;
    int width;
    std::vector<std::vector<int>> screen;

    float fov;
    float aspect_ratio;
    float transform;

    bool IsInTriangle(Triangle screen_space_triangle, Vec2 position);
    bool AABB_Collision(int min_x, int max_x, int min_y, int max_y);

    float LeftRightVector(Vec3 A, Vec3 B, Vec2 P);
    Triangle ScreenSpacePerspectiveProjection(Triangle triangle);
    void DrawTriangle(Triangle* triangle);
};
