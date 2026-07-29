#pragma once

#include <cmath>

typedef struct Vec2 Vec2;
typedef struct Vec3 Vec3;
typedef struct Vec4 Vec4;

struct Vec2 {
	float coord[2];

  float Norm(){
    return std::sqrt(std::pow(coord[0], 2) + std::pow(coord[1], 2));
  }

  float Dot(Vec2 b){
    return coord[0] * b.coord[0] + coord[1] * b.coord[1];
  };

  Vec2(){}
  Vec2(float _x, float _y){
    coord[0] = _x;
    coord[1] = _y;
  }

  friend Vec2 operator+ (Vec2 lhs, const Vec2& rhs){
    return Vec2(lhs.coord[0] + rhs.coord[0], lhs.coord[1] + rhs.coord[1]);
  }

  friend Vec2 operator- (Vec2 lhs, const Vec2& rhs){
    return Vec2(lhs.coord[0] - rhs.coord[0], lhs.coord[1] - rhs.coord[1]);
  }
};

struct Vec3 {
	float coord[3];

  float Norm(){
    return std::sqrt(std::pow(coord[0], 2) + std::pow(coord[1], 2) + std::pow(coord[2], 2));
  }

  float Dot(Vec3 b){
    return coord[0] * b.coord[0] + coord[1] * b.coord[1] + coord[2] * b.coord[2];
  };

	Vec3 Cross(Vec3 b){
		Vec3 product;

		product.coord[0] = coord[1] * b.coord[2] - coord[2] * b.coord[1];
		product.coord[1] = - (coord[0] * b.coord[2] - coord[2] * b.coord[0]);
		product.coord[2] = coord[0] * b.coord[1] - coord[1] * b.coord[0];

		return product;
	}

  Vec3(){}
  Vec3(float _x, float _y, float _z){
    coord[0] = _x;
    coord[1] = _y;
    coord[2] = _z;
  }

  friend Vec3 operator+ (Vec3 lhs, const Vec3& rhs){
    return Vec3(lhs.coord[0] + rhs.coord[0], lhs.coord[1] + rhs.coord[1], lhs.coord[2] + rhs.coord[2]);
  }

  friend Vec3 operator- (Vec3 lhs, const Vec3& rhs){
    return Vec3(lhs.coord[0] - rhs.coord[0], lhs.coord[1] - rhs.coord[1], lhs.coord[2] - rhs.coord[2]);
  }
};

struct Vec4 {
	float coord[4];

  float Norm(){
    return std::sqrt(std::pow(coord[0], 2) + std::pow(coord[1], 2) + std::pow(coord[2], 2) + std::pow(coord[3], 2));
  }

  float Dot(Vec4 b){
    return (coord[0] * b.coord[0]) + (coord[1] * b.coord[1]) + (coord[2] * b.coord[2]) + (coord[3] * b.coord[3]);
  };

  Vec4(){}
  Vec4(float _x, float _y, float _z, float _w){
    coord[0] = _x;
    coord[1] = _y;
    coord[2] = _z;
    coord[3] = _w;
  }

  friend Vec4 operator+ (Vec4 lhs, const Vec4& rhs){
    return Vec4(lhs.coord[0] + rhs.coord[0], lhs.coord[1] + rhs.coord[1], lhs.coord[2] + rhs.coord[2], lhs.coord[3] + rhs.coord[3]);
  }

  friend Vec4 operator- (Vec4 lhs, const Vec4& rhs){
    return Vec4(lhs.coord[0] - rhs.coord[0], lhs.coord[1] - rhs.coord[1], lhs.coord[2] - rhs.coord[2], lhs.coord[3] - rhs.coord[3]);
  }
};
