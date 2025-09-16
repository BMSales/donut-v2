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
	vector_AP = P - A;

	// rotate AB to determine if P is on the right side 
	// or the left side of AB
	// the rotation is done according to screen space
	rotation_assist = vector_AB.x;
	vector_AB.x = -vector_AB.y;
	vector_AB.y = rotation_assist;

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

bool Canvas::AABB_Collision(int min_x, int max_x, int min_y, int max_y){
	if(
		min_x < width && max_x >= 0 &&
		min_y < height && max_y >= 0
	){
		return true;
	}
	return false;
}

void Canvas::DrawTriangle(Triangle triangle){
	while(1){
		std::cout << triangle.A.y << std::endl;
	}
	Vec2 screen_space_vertex_1 = ScreenSpacePerspectiveProjection(triangle.A);
	Vec2 screen_space_vertex_2 = ScreenSpacePerspectiveProjection(triangle.B);
	Vec2 screen_space_vertex_3 = ScreenSpacePerspectiveProjection(triangle.C);
	Vec2 position;

	int min_x = std::min(std::min(screen_space_vertex_1.x, screen_space_vertex_2.x), screen_space_vertex_3.x);
	int max_x = std::max(std::max(screen_space_vertex_1.x, screen_space_vertex_2.x), screen_space_vertex_3.x);
	int min_y = std::min(std::min(screen_space_vertex_1.y, screen_space_vertex_2.y), screen_space_vertex_3.y);
	int max_y = std::max(std::max(screen_space_vertex_1.y, screen_space_vertex_2.y), screen_space_vertex_3.y);

	if(!AABB_Collision(min_x, max_x, min_y, max_y)){
		return;
	}
	else{
		if(min_x < 0){
			min_x = 0;
		}
		if(max_x > width - 1){
			max_x = width - 1;
		}
		if(min_y < 0){
			min_y = 0;
		}
		if(max_y > height - 1){
			max_y = height - 1;
		}
	}

	for(int i = min_y; i <= max_y; i++){
		position.y = i;
		for(int j = min_x; j <= max_x; j++){
			position.x = j;
			if(IsInTriangle(screen_space_vertex_1, screen_space_vertex_2, screen_space_vertex_3, position)){
				matrix[i][j] = '.';
			}
		}
	}
}

void Canvas::DrawShape(Shape shape){
	std::vector<int> test;
	test.push_back(1);
	test.push_back(1);
	test.push_back(1);
	for(auto &triangle : test){
		std::cout << triangle;
		exit(1);
		// DrawTriangle(triangle);
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
