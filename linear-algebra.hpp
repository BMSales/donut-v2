#pragma once

#include <vector>
#include "vectors.hpp"

class Matrix{
  public:
    Matrix();
    Matrix(int, int);

    float GetValue(int, int);

    void SetValue(int, int, float);
    void SetRandomValues();

    void Resize(int, int);
    void Identity(int);
    void Translation(float, float, float);
    void Scaling(float, float, float);
    void RotationX(float);
    void RotationY(float);
    void RotationZ(float);
    void PerspectiveProjection(float, float, float, float);
    void ScreenSpace(int, int);

    void Print();
    Matrix Multiply(Matrix);
    Vec4 Multiply(Vec4);

  private:
    int rows;
    int cols;
    std::vector<std::vector<float>> values;
};
