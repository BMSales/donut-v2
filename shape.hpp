#pragma once

#include <stdlib.h>
#include <math.h>

class Shape(){
	private:
		int num_points;
		float** points;
	public:
		Shape(int new_num_points){
			num_points = new_num_points;
			points = (float**)calloc(num_points, sizeof(float*));

			for(int i = 0; i < num_points; i++){
				points[i] = (float*)calloc(3, sizeof(float));
			}
		}

		~Shape(){
			for(int i = 0; i < num_points; i++){
				free(points[i]);
			}
			free(points);
		}

		// void torus(float inner_radius, float ring_radius){
		// 	float 
		// 	for(
		// }
}
