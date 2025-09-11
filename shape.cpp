#include <stdlib.h>
#include <math.h>
#include "shape.hpp"

// Shape::Shape(){
//   this->num_points = num_points;
//   points = (float**)calloc(num_points, sizeof(float*));
//
//   for(int i = 0; i < num_points; i++){
//     points[i] = (float*)calloc(3, sizeof(float));
//   }
// }

Shape::~Shape(){
  for(int i = 0; i < num_points; i++){
    free(points[i]);
  }
  free(points);
}

// Shape::Rotate_X(float angle){
//
// }
