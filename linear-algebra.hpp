#pragma once

#include <vector>
#include "vectors.hpp"

class Matrix{
  public:
    Matrix();
    Matrix(int rows, int cols);

    float GetValue(int row, int col);

    void SetValue(int row, int col, float value);
    void SetRandomValues();

    void Resize(int rows, int cols);
    void Identity(int size);
    void Translation(float x, float y, float z);
    void Scaling(float x, float y, float z);
    void RotationX(float angle);
    void RotationY(float angle);
    void RotationZ(float angle);
    void PerspectiveProjection(float fov, float aspect_ratio, float far, float near);
    void ScreenSpace(int width, int height);

    void Print();
    Matrix Multiply(Matrix input);
    Vec4 Multiply(Vec4 input);

  private:
    int rows;
    int cols;
    std::vector<std::vector<float>> values;
};

// TODO:
// Add the following operations
// addition and subtraction
// adjugate matrix (too hard, maybe?)
// determinant
// eigenvalues and eigenvectors calculations (autovalor e autovetor)
// gauss jordan
// inverse matrix
// scalar multiplication
// transpose

// TODO:
// Add the following functionalities
// GetRow
// GetCollumn
// GetNumRows
// GetNumCols
// SwapRows
// SwapCollumns
// Determine if a square matrix is orthogonal
