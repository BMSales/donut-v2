#pragma once

typedef struct Vec2 Vec2;
typedef struct Vec3 Vec3;

struct Vec2 {
  float x;
  float y;

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

  float Dot(Vec3 b){
    return x * b.x + y * b.y + z * b.z;
  };

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
