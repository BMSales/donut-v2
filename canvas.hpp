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
    std::vector<std::vector<float>> z_buffer;
    std::vector<int> depth_color_code;

    float fov;
    float aspect_ratio;
    float transform;

    bool CanDrawPixel(Triangle screen_space_triangle, Vec3 position);
    bool AABB_Collision(int min_x, int max_x, int min_y, int max_y);

    int DepthMap(int i, int j);

    float SignedTriangleArea(Triangle triangle);
    Triangle ScreenSpacePerspectiveProjection(Triangle triangle);
    void DrawTriangle(Triangle* triangle);
};
