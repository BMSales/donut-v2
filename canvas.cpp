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

void Canvas::PerspectiveProjection(float x, float y, float z){
	float proj_x = x * transform/aspect_ratio * z;
	float proj_y = y * transform/z;

  std::cout << "x " << proj_x << "\n";
  std::cout << "y " << proj_y << "\n";

	int col = ((proj_x + 1.0)/2.0) * width;
	int row = ((-proj_y + 1.0)/2.0) * height;

	matrix[row][col] = '.';
}

void Canvas::Print(){
	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
			std::cout << matrix[i][j];
		}
		std::cout << "\n";
	}
}
