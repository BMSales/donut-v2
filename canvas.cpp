#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "canvas.hpp"
#include "vectors.hpp"

#define M_PI 3.14159265358979323846

Canvas::Canvas(){
	// retrieves the terminal's dimensions
	struct winsize window;
	// w.ws_row for rows
	// w.ws_col for collumns
	ioctl(STDIN_FILENO, TIOCGWINSZ, &window);

	height = window.ws_row;
	width = window.ws_col;
	matrix.reserve(height);

	fov = 90.0;
	aspect_ratio = (float)width/(float)height;
	transform = 1.0/( tanf((fov * M_PI/180.0)/2.0) );

	for(int i = 0; i < height; i++){
		matrix[i].reserve(width);
	}
	
	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
			matrix[i][j] = ' ';
		}
	}
}

void Canvas::ChangeFOV(float new_fov){
	if(new_fov <= 0.0 || new_fov >= 180.0){
		std::cout << "invalid angle" << std::endl;
		exit(-1);
	}

	fov = new_fov;
	transform = 1.0/( tanf((fov * M_PI/180.0)/2.0) );
}

int Canvas::LeftRightVector(Vec2 A, Vec2 B, Vec2 P){
	Vec2 vector_AB;
	Vec2 vector_AP;
	int rotation_assist;

	vector_AB = B - A;

	// rotate AB to determine if P is on the right side 
	// or the left side of AB
	// the rotation is done according to screen space
	rotation_assist = vector_AB.x;
	vector_AB.x = -vector_AB.y;
	vector_AB.y = rotation_assist;

	vector_AP = P - A;

	return vector_AB.Dot(vector_AP);
}

bool Canvas::IsInTriangle(Vec2 vertex_1, Vec2 vertex_2, Vec2 vertex_3, Vec2 position){
	int AB = LeftRightVector(vertex_1, vertex_2, position);
	int BC = LeftRightVector(vertex_2, vertex_3, position);
	int CA = LeftRightVector(vertex_3, vertex_1, position);

	if(AB >= 0 && BC >= 0 && CA >= 0){
		return true;
	}

	return false;
}

Vec2 Canvas::ScreenSpacePerspectiveProjection(Vec3 vertex){
	Vec2 screen_space_vertex;

	screen_space_vertex.x = vertex.x * transform/(aspect_ratio * vertex.z);
	screen_space_vertex.y = vertex.y * transform/vertex.z;

	screen_space_vertex.x = ((screen_space_vertex.x + 1.0)/2.0) * width;
	screen_space_vertex.y = ((-screen_space_vertex.y + 1.0)/2.0) * height;

	return screen_space_vertex;
}

void Canvas::DrawTriangle(Vec3 vertex_1, Vec3 vertex_2, Vec3 vertex_3){
	Vec2 screen_space_vertex_1 = ScreenSpacePerspectiveProjection(vertex_1);
	Vec2 screen_space_vertex_2 = ScreenSpacePerspectiveProjection(vertex_2);
	Vec2 screen_space_vertex_3 = ScreenSpacePerspectiveProjection(vertex_3);
	Vec2 position;

	int left = std::min(std::min(screen_space_vertex_1.x, screen_space_vertex_2.x), screen_space_vertex_3.x);
	int right = std::max(std::max(screen_space_vertex_1.x, screen_space_vertex_2.x), screen_space_vertex_3.x);
	right = std::min(right, width);
	int up = std::min(std::min(screen_space_vertex_1.y, screen_space_vertex_2.y), screen_space_vertex_3.y);
	int down = std::max(std::max(screen_space_vertex_1.y, screen_space_vertex_2.y), screen_space_vertex_3.y);

	for(int i = up; i < down; i++){
		position.y = i;
		for(int j = left; j < right; j++){
			position.x = j;
			if(IsInTriangle(screen_space_vertex_1, screen_space_vertex_2, screen_space_vertex_3, position)){
				matrix[i][j] = '$';
			}
		}
	}
}

void Canvas::Print(){
	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
			std::cout << matrix[i][j];
			matrix[i][j] = ' ';
		}
		std::cout << std::endl;
	}
}
