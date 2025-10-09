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

  screen.resize(height);
  z_buffer.resize(height);
  for(int i = 0; i < height; i++){
    screen[i].resize(width);
    z_buffer[i].resize(width);
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

float Canvas::SignedTriangleArea(Triangle triangle){
	Vec2 triangle_A = {triangle.A.x, triangle.A.y};
	Vec2 triangle_B = {triangle.B.x, triangle.B.y};
	Vec2 triangle_C = {triangle.C.x, triangle.C.y};

  Vec2 vector_AB = triangle_B - triangle_A;
  Vec2 vector_AP = triangle_C - triangle_A;
  Vec2 rotated_AB = {-vector_AB.y, vector_AB.x};

  float base = vector_AB.Norm();
  float height = rotated_AB.Dot(vector_AP);

  return base * height/2;
}

bool Canvas::CanDrawPixel(Triangle screen_space_triangle, Vec3 position){
  Triangle triangle_A = {screen_space_triangle.B, screen_space_triangle.C, position, 0};
  Triangle triangle_B = {screen_space_triangle.C, screen_space_triangle.A, position, 0};
  Triangle triangle_C = {screen_space_triangle.A, screen_space_triangle.B, position, 0};

  float area_A = SignedTriangleArea(triangle_A);
  float area_B = SignedTriangleArea(triangle_B);
  float area_C = SignedTriangleArea(triangle_C);
  float z_position = 0.0;
  float one_over_z = 0.0;

  if(area_A >= 0 && area_B >= 0 && area_C >= 0){
		z_position = (screen_space_triangle.A.z * area_A + screen_space_triangle.B.z * area_B + screen_space_triangle.C.z * area_C)/(area_A + area_B + area_C);
		one_over_z = 1/z_position;
		
    if(one_over_z > z_buffer[position.y][position.x]){
      z_buffer[position.y][position.x] = one_over_z;
      return true;
    }
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

	screen_space_triangle.A.z = triangle.A.z;
	screen_space_triangle.B.z = triangle.B.z;
	screen_space_triangle.C.z = triangle.C.z;

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
	Vec3 position;

	Vec3 AB = triangle->B - triangle->A;
	Vec3 BC = triangle->C - triangle->B;
	Vec3 triangle_normal_vector = AB.Cross(BC);
	Vec3 camera_normal = {0.0, 0.0, 1.0};

	if(triangle_normal_vector.Dot(camera_normal) > 0.0){
		return;
	}

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
      if(CanDrawPixel(screen_space_triangle, position)){
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
  std::vector<std::string> lines;
  for(int i = 0; i < height; i++){
    for(int j = 0; j < width; j++){
      line += "\033[38;5;" + std::to_string(screen[i][j]) + "m\u2588\033[0m";
      screen[i][j] = 0;
      z_buffer[i][j] = 0.0;
    }
    lines.push_back(line);
    line.clear();
  }

  for (auto& l : lines) {
    std::cout << l << '\n';
  }

  std::cout << std::flush;
}

void Canvas::ClearScreen(){
  std::cout << "\033[2J\033[H";
}

// TODO:
// check if a triangle is facing the camera or not before trying to draw it
