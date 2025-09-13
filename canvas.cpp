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
  if(new_fov < 0.0 || new_fov > 180.0){
    std::cout << "invalid angle" << std::endl;
    return;
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

  swap = vector_AB[0];
  vector_AB[0] = -vector_AB[1];
  vector_AB[1] = swap;

  vector_AP[0] = P[0] - A[0];
  vector_AP[1] = P[1] - A[1];

  return vector_AB[0] * vector_AP[0] + vector_AB[1] * vector_AP[1];
}

void Canvas::DrawTriangle(float* vertex_1, float* vertex_2, float* vertex_3){

  float view_space_vertex_1[2];
  float view_space_vertex_2[2];
  float view_space_vertex_3[2];

  int screen_space_vertex_1[2];
  int screen_space_vertex_2[2];
  int screen_space_vertex_3[2];

  int position[2];

  view_space_vertex_1[0] = vertex_1[0] * transform/(aspect_ratio * vertex_1[2]);
  view_space_vertex_1[1] = vertex_1[1] * transform/vertex_1[2];
  view_space_vertex_2[0] = vertex_2[0] * transform/(aspect_ratio * vertex_2[2]);
  view_space_vertex_2[1] = vertex_2[1] * transform/vertex_2[2];
  view_space_vertex_3[0] = vertex_3[0] * transform/(aspect_ratio * vertex_3[2]);
  view_space_vertex_3[1] = vertex_3[1] * transform/vertex_3[2];

  screen_space_vertex_1[0] = ((view_space_vertex_1[0] + 1.0)/2.0) * width;
  screen_space_vertex_1[1] = ((-view_space_vertex_1[1] + 1.0)/2.0) * height;
  screen_space_vertex_2[0] = ((view_space_vertex_2[0] + 1.0)/2.0) * width;
  screen_space_vertex_2[1] = ((-view_space_vertex_2[1] + 1.0)/2.0) * height;
  screen_space_vertex_3[0] = ((view_space_vertex_3[0] + 1.0)/2.0) * width;
  screen_space_vertex_3[1] = ((-view_space_vertex_3[1] + 1.0)/2.0) * height;

  for(int i = 0; i < height; i++){
    position[1] = i;
    for(int j = 0; j < width; j++){
      position[0] = j;
      if(DotProduct(screen_space_vertex_1, screen_space_vertex_2, position) >= 0 && 
          DotProduct(screen_space_vertex_2, screen_space_vertex_3, position) >= 0 && 
          DotProduct(screen_space_vertex_3, screen_space_vertex_1, position) >= 0){
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
