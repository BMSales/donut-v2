#include <iostream>
#include <stdio.h>
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
	matrix = (char**)calloc(height, sizeof(char*));

	fov = 90.0;
	aspect_ratio = (float)width/(float)height;
	transform = 1.0/( tanf((fov * M_PI/180.0)/2.0) );

	for(int i = 0; i < height; i++){
		matrix[i] = (char*)calloc(width, sizeof(char));
	}

	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
			matrix[i][j] = ' ';
		}
	}
}

Canvas::~Canvas(){
	for(int i = 0; i < height; i++){
		free(matrix[i]);
	}
	free(matrix);
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
  int swap;

  vector_AB.x = B.x - A.x;
  vector_AB.y = B.y - A.y;

  // rotate AB to determine if P is on the right side 
  // or the left side of AB
  // the rotation is done according to screen space
  swap = vector_AB.x;
  vector_AB.x = -vector_AB.y;
  vector_AB.y = swap;

  vector_AP.x = P.x - A.x;
  vector_AP.y = P.y - A.y;

  return vector_AB.x * vector_AP.x + vector_AB.y * vector_AP.y;
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

void Canvas::ScreenSpacePerspectiveProjection(Vec3 vertex, Vec2* screen_space_vertex){
  Vec2 view_space_vertex;

  view_space_vertex.x = vertex.x * transform/(aspect_ratio * vertex.z);
  view_space_vertex.y = vertex.y * transform/vertex.z;

  screen_space_vertex->x = ((view_space_vertex.x + 1.0)/2.0) * width;
  screen_space_vertex->y = ((-view_space_vertex.y + 1.0)/2.0) * height;
}

void Canvas::DrawTriangle(Vec3 vertex_1, Vec3 vertex_2, Vec3 vertex_3){
  Vec2 screen_space_vertex_1;
  Vec2 screen_space_vertex_2;
  Vec2 screen_space_vertex_3;

  Vec2 position;

  ScreenSpacePerspectiveProjection(vertex_1, &screen_space_vertex_1);
  ScreenSpacePerspectiveProjection(vertex_2, &screen_space_vertex_2);
  ScreenSpacePerspectiveProjection(vertex_3, &screen_space_vertex_3);

  for(int i = 0; i < height; i++){
    position.y = i;
    for(int j = 0; j < width; j++){
      position.x = j;
      if(IsInTriangle(screen_space_vertex_1, screen_space_vertex_2, screen_space_vertex_3, position)){
        matrix[i][j] = '.';
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
    printf("\n");
	}
}
