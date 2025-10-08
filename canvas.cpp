#include <ctime>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "canvas.hpp"
#include "object.hpp"
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

  fov = 45.0;
  aspect_ratio = (float)width/(float)height;
  transform = 1.0/( tanf((fov * M_PI/180.0)/2.0) );

  screen.reserve(height);
  for(int i = 0; i < height; i++){
    screen[i].reserve(width);
  }
}

void Canvas::SetFOV(float new_fov){
  if(new_fov <= 0.0 || new_fov >= 180.0){
    std::cout << "invalid angle" << std::endl;
    exit(-1);
  }

  fov = new_fov;
  transform = 1.0/( tanf((fov * M_PI/180.0)/2.0) );
}

float Canvas::LeftRightVector(Vec3 A, Vec3 B, Vec2 P){
  Vec3 vector_AB;
  Vec3 vector_AP;
	Vec3 T = {P.x, P.y, 0.0};
  float rotation_assist;

  vector_AB = B - A;
  vector_AP = T - A;

  // rotate AB to determine if P is on the right side 
  // or the left side of AB
  // the rotation is done according to screen space
  rotation_assist = vector_AB.x;
  vector_AB.x = -vector_AB.y;
  vector_AB.y = rotation_assist;

  return vector_AB.Dot(vector_AP);
}

bool Canvas::IsInTriangle(Triangle screen_space_triangle, Vec2 position){
  float AB = LeftRightVector(screen_space_triangle.A, screen_space_triangle.B, position);
  float BC = LeftRightVector(screen_space_triangle.B, screen_space_triangle.C, position);
  float CA = LeftRightVector(screen_space_triangle.C, screen_space_triangle.A, position);

  if(AB >= 0 && BC >= 0 && CA >= 0){
    return true;
  }

  return false;
}

Triangle Canvas::ScreenSpacePerspectiveProjection(Triangle triangle){
  Triangle screen_space_triangle;

  screen_space_triangle.A.x = triangle.A.x * transform/(aspect_ratio * triangle.A.z);
  screen_space_triangle.A.y = triangle.A.y * transform/triangle.A.z;
	screen_space_triangle.B.x = triangle.B.x * transform/(aspect_ratio * triangle.B.z);
  screen_space_triangle.B.y = triangle.B.y * transform/triangle.B.z;
	screen_space_triangle.C.x = triangle.C.x * transform/(aspect_ratio * triangle.C.z);
  screen_space_triangle.C.y = triangle.C.y * transform/triangle.C.z;

  screen_space_triangle.A.x = ((screen_space_triangle.A.x + 1.0)/2.0) * width;
  screen_space_triangle.A.y = ((-screen_space_triangle.A.y + 1.0)/2.0) * height;
	screen_space_triangle.B.x = ((screen_space_triangle.B.x + 1.0)/2.0) * width;
  screen_space_triangle.B.y = ((-screen_space_triangle.B.y + 1.0)/2.0) * height;
	screen_space_triangle.C.x = ((screen_space_triangle.C.x + 1.0)/2.0) * width;
  screen_space_triangle.C.y = ((-screen_space_triangle.C.y + 1.0)/2.0) * height;

  return screen_space_triangle;
}

bool Canvas::AABB_Collision(int min_x, int max_x, int min_y, int max_y){
  if(min_x < width && max_x >= 0 && min_y < height && max_y >= 0){
    return true;
  }
  return false;
}

void Canvas::DrawTriangle(Triangle* triangle){
	Triangle screen_space_triangle = ScreenSpacePerspectiveProjection(*triangle);
	Vec2 position;

  int min_x = std::min(std::min(screen_space_triangle.A.x, screen_space_triangle.B.x), screen_space_triangle.C.x);
  int max_x = std::max(std::max(screen_space_triangle.A.x, screen_space_triangle.B.x), screen_space_triangle.C.x);
  int min_y = std::min(std::min(screen_space_triangle.A.y, screen_space_triangle.B.y), screen_space_triangle.C.y);
  int max_y = std::max(std::max(screen_space_triangle.A.y, screen_space_triangle.B.y), screen_space_triangle.C.y);

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
      if(IsInTriangle(screen_space_triangle, position)){
        screen[i][j] = triangle->color_code;
      }
    }
  }
}

void Canvas::DrawObject(Object* object){
  Triangle render_triangle;

  for(auto &triangle : (*object).tri){
    render_triangle.A = triangle.A + object->GetOffset();
    render_triangle.B = triangle.B + object->GetOffset();
    render_triangle.C = triangle.C + object->GetOffset();
    render_triangle.color_code = triangle.color_code;

    DrawTriangle(&render_triangle);
  }
}

void Canvas::Print(){
  std::string line;
  for(int i = 0; i < height; i++){
    for(int j = 0; j < width; j++){
      line += "\033[38;5;" + std::to_string(screen[i][j]) + "m\u2588\033[0m";
      screen[i][j] = 0;
    }
    std::cout << line << std::endl;
    line = "";
  }
}

void Canvas::ClearScreen(){
  std::cout << "\033[2J\033[H";
}

// TODO:
// check if a triangle is facing the camera or not before trying to draw it
