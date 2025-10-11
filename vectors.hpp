#pragma once

#include <cmath>

typedef struct Vec2 Vec2;
typedef struct Vec3 Vec3;
typedef struct Plane Plane;

struct Vec2 {
  float x;
  float y;

  float Norm(){
    return std::sqrt(std::pow(x, 2) + std::pow(y, 2));
  }

  float Dot(Vec2 b){
    return x * b.x + y * b.y;
  };

  Vec2(){}
  Vec2(float _x, float _y){
    x = _x;
    y = _y;
  }

  friend Vec2 operator+ (Vec2 lhs, const Vec2& rhs){
    return Vec2(lhs.x + rhs.x, lhs.y + rhs.y);
  }

  friend Vec2 operator- (Vec2 lhs, const Vec2& rhs){
    return Vec2(lhs.x - rhs.x, lhs.y - rhs.y);
  }
};

struct Vec3 {
  float x;
  float y;
  float z;

  float Norm(){
    return std::sqrt(std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2));
  }

  Vec3 Normalize(){
    float norm = Norm();
    Vec3 normalized_vector;
    normalized_vector.x /= norm;
    normalized_vector.y /= norm;
    normalized_vector.z /= norm;

    return normalized_vector;
  }

  float Dot(Vec3 b){
    return x * b.x + y * b.y + z * b.z;
  };

	Vec3 Cross(Vec3 b){
		Vec3 product;

		product.x = y * b.z - z * b.y;
		product.y = - (x * b.z - z * b.x);
		product.z = x * b.y - y * b.x;

		return product;
	}

  Vec3(){}
  Vec3(float _x, float _y, float _z){
    x = _x;
    y = _y;
    z = _z;
  }

  friend Vec3 operator+ (Vec3 lhs, const Vec3& rhs){
    return Vec3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
  }

  friend Vec3 operator- (Vec3 lhs, const Vec3& rhs){
    return Vec3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
  }
};
