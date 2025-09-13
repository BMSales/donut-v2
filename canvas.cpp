#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "canvas.hpp"

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

int DotProduct(int A[2], int B[2], int P[2]){
  int vector_AB[2];
  int vector_AP[2];
  int swap;

  vector_AB[0] = B[0] - A[0];
  vector_AB[1] = B[1] - A[1];

  // rotate AB to determine if P is on the right side 
  // or the left side of AB
  // the rotation is done according to screen space
  swap = vector_AB[0];
  vector_AB[0] = -vector_AB[1];
  vector_AB[1] = swap;

  vector_AP[0] = P[0] - A[0];
  vector_AP[1] = P[1] - A[1];

  return vector_AB[0] * vector_AP[0] + vector_AB[1] * vector_AP[1];
}

bool IsInTriangle(int vertex_1[2], int vertex_2[2], int vertex_3[2], int position[2]){
  int AB = DotProduct(vertex_1, vertex_2, position);
  int BC = DotProduct(vertex_2, vertex_3, position);
  int CA = DotProduct(vertex_3, vertex_1, position);

  if(AB >= 0 && BC >= 0 && CA >= 0){
    return true;
  }

  return false;
}

void Canvas::ScreenSpacePerspectiveProjection(float vertex[3], int screen_space_vertex[][2]){
  float view_space_vertex[2];

  view_space_vertex[0] = vertex[0] * transform/(aspect_ratio * vertex[2]);
  view_space_vertex[1] = vertex[1] * transform/vertex[2];

  (*screen_space_vertex)[0] = ((view_space_vertex[0] + 1.0)/2.0) * width;
  (*screen_space_vertex)[1] = ((-view_space_vertex[1] + 1.0)/2.0) * height;
}

void Canvas::DrawTriangle(float vertex_1[3], float vertex_2[3], float vertex_3[3]){
  int screen_space_vertex_1[2];
  int screen_space_vertex_2[2];
  int screen_space_vertex_3[2];

  int position[2];

  ScreenSpacePerspectiveProjection(vertex_1, &screen_space_vertex_1);
  ScreenSpacePerspectiveProjection(vertex_2, &screen_space_vertex_2);
  ScreenSpacePerspectiveProjection(vertex_3, &screen_space_vertex_3);

  for(int i = 0; i < height; i++){
    position[1] = i;
    for(int j = 0; j < width; j++){
      position[0] = j;
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
