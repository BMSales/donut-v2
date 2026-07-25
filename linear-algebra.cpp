#include <cmath>
#include <iostream>
#include <iomanip>
#include <random>
#include <vector>
#include "linear-algebra.hpp"

#define M_PI 3.14159265358979323846
#define RAD_CONV M_PI/180.0

Matrix::Matrix(){
	rows = 0;
	cols = 0;
	values = {{}};
}

Matrix::Matrix(int rows, int cols){
	if(rows <= 0 || cols <= 0){
		std::cout << "Invalid value for row/collumn!" << std::endl;
		exit(-1);
	}
	this->rows = rows;
	this->cols = cols;
	this->values.resize(rows);
	for(int i = 0; i < rows; i++){
		this->values[i].resize(cols);
	}
}

float Matrix::GetValue(int row, int col){
	return values[row][col];
}

void Matrix::SetValue(int row, int col, float value){
	values[row][col] = value;
}

void Matrix::SetRandomValues(){
	std::random_device device;
	std::default_random_engine engine(device());
	std::uniform_int_distribution<int> uniform_dist(0, 5);
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < cols; j++){
			values[i][j] = uniform_dist(engine);
		}
	}
}

void Matrix::Resize(int rows, int cols){
	if(rows <= 0 || cols <= 0){
		std::cout << "Invalid value for size!" << std::endl;
		exit(-1);
	}
	this->rows = rows;
	this->cols = cols;
	this->values.resize(rows);
	for(int i = 0; i < rows; i++){
		this->values[i].resize(cols);
	}
}

void Matrix::Identity(int size){
	if(size <= 0){
		std::cout << "Invalid value for size!" << std::endl;
		exit(-1);
	}
	this->rows = size;
	this->cols = size;
	this->values.resize(size);
	for(int i = 0; i < size; i++){
		this->values[i].resize(size);
	}
	for(int i = 0; i < size; i++){
		this->values[i][i] = 1;
	}
}

void Matrix::Translation(float x, float y, float z){
	this->Identity(4);
	this->values[3][0] = x;
	this->values[3][1] = y;
	this->values[3][2] = z;
}

void Matrix::Scaling(float x, float y, float z){
	this->Identity(4);
	this->values[0][0] = x;
	this->values[1][1] = y;
	this->values[2][2] = z;
}

void Matrix::RotationX(float angle){
	float rad = angle * RAD_CONV;
	float cos_rad = cos(rad);
	float sin_rad = sin(rad);

	this->Identity(4);
	this->values[1][1] = cos_rad;
	this->values[1][2] = -sin_rad;
	this->values[2][1] = sin_rad;
	this->values[2][2] = cos_rad;
}

void Matrix::RotationY(float angle){
	float rad = angle * RAD_CONV;
	float cos_rad = cos(rad);
	float sin_rad = sin(rad);

	this->Identity(4);
	this->values[0][0] = cos_rad;
	this->values[0][2] = sin_rad;
	this->values[2][0] = -sin_rad;
	this->values[2][2] = cos_rad;
}

void Matrix::RotationZ(float angle){
	float rad = angle * RAD_CONV;
	float cos_rad = cos(rad);
	float sin_rad = sin(rad);

	this->Identity(4);
	this->values[0][0] = cos_rad;
	this->values[0][1] = -sin_rad;
	this->values[1][0] = sin_rad;
	this->values[1][1] = cos_rad;
}

void Matrix::PerspectiveProjection(float fov, float aspect_ratio, float far, float near){
	float fov_rad = fov * RAD_CONV;
	float arctan = atanf(fov_rad/2);
	this->Resize(4, 4);
	this->values[0][0] = arctan * aspect_ratio;
	this->values[1][1] = arctan;
	this->values[2][2] = far/(far - near);
	this->values[2][3] = 1;
	this->values[3][2] = -far*near/(far - near);
}

void Matrix::Print(){
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < cols; j++){
			std::cout << std::fixed << std::setprecision(3) << values[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

Matrix Matrix::Multiply(Matrix input){
	if(this->cols != input.rows){
		std::cout << "Matrices cannot be multiplied!" << std::endl;
		exit(-1);
	}
	int m = this->rows;
	int n = input.cols;
	float helper = 0;
	Matrix product = Matrix(m, n);

	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			for(int k = 0; k < this->cols; k++){
				helper += this->values[i][k] * input.values[k][j];
			}
			product.values[i][j] = helper;
			helper = 0;
		}
	}

	return product;
}

Vec4 Matrix::Multiply(Vec4 input){
	if(this->rows != 4){
		std::cout << "Cannot multiply vector with this matrix!" << std::endl;
		exit(-1);
	}
	float helper;
	Vec4 product;

	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			helper += input.coord[j] * this->values[j][i];
		}
		product.coord[i] = helper;
		helper = 0;
	}

	return product;
}
