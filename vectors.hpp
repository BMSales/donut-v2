#pragma once

typedef struct Vec2 Vec2;
typedef struct Vec3 Vec3;

struct Vec2 {
	float x;
	float y;

	float Dot(Vec2 b){
		return x * b.x + y * b.y;
	};
};

struct Vec3 {
	float x;
	float y;
	float z;

	float Dot(Vec3 b){
		return x * b.x + y * b.y + z * b.z;
	};
};
