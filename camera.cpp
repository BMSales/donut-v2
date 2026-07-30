#include <ctime>
#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>

#include "camera.hpp"
#include "linear-algebra.hpp"
#include "object.hpp"
#include "vectors.hpp"

Camera::Camera(){
  // retrieves the terminal's dimensions
  struct winsize window;
  // w.ws_row for rows
  // w.ws_col for collumns
  ioctl(STDIN_FILENO, TIOCGWINSZ, &window);

  height = window.ws_row;
  width = window.ws_col;

  fov = 45.0;
  aspect_ratio = (float)width/(float)height;

  screen.resize(height);
  z_buffer.resize(height);
  for(int i = 0; i < height; i++){
    screen[i].resize(width);
    z_buffer[i].resize(width);
  }
  for(int i = 232; i < 256; i++){
    bw_color_code.push_back(i);
  }
}

int Camera::GetHeight(){
  return height;
}

int Camera::GetWidth(){
  return width;
}

void Camera::SetTransformations(Matrix translation, Matrix scaling, Matrix rotationX, Matrix rotationY, Matrix rotationZ, Matrix projection, Matrix screenSpace){
  Matrix product;
  Matrix rotations;

  rotations = rotationX.Multiply(rotationY);
  rotations = rotations.Multiply(rotationZ);

  product = scaling.Multiply(rotations);
  product = product.Multiply(translation);
  product = product.Multiply(projection);

  transformations[0] = translation;
  transformations[1] = scaling;
  transformations[2] = rotations;
  transformations[3] = projection;
  transformations[4] = screenSpace;
  transformations[5] = product;
}

void Camera::SetFOV(float new_fov){
  if(new_fov <= 0.0 || new_fov >= 180.0){
    std::cout << "invalid angle" << std::endl;
    exit(-1);
  }

  fov = new_fov;
}

float Camera::SignedTriangleArea(Triangle triangle){
  Vec2 vertex_A = {triangle.A.coord[0], triangle.A.coord[1]};
  Vec2 vertex_B = {triangle.B.coord[0], triangle.B.coord[1]};
  Vec2 vertex_C = {triangle.C.coord[0], triangle.C.coord[1]};

  Vec2 vector_AB = vertex_B - vertex_A;
  Vec2 vector_AC = vertex_C - vertex_A;
  Vec2 rotated_AB = {-vector_AB.coord[1], vector_AB.coord[0]};

  float base = vector_AB.Norm();
  float height = rotated_AB.Dot(vector_AC);

  return base * height/2.0;
}

bool Camera::CanDrawPixel(Triangle triangle, Vec4 position){
  Triangle triangle_A = {triangle.B, triangle.C, position};
  Triangle triangle_B = {triangle.C, triangle.A, position};
  Triangle triangle_C = {triangle.A, triangle.B, position};

  float area_A = SignedTriangleArea(triangle_A);
  float area_B = SignedTriangleArea(triangle_B);
  float area_C = SignedTriangleArea(triangle_C);
  float z_position = 0.0;
  float one_over_z = 0.0;

  if(area_A >= 0 && area_B >= 0 && area_C >= 0){
    z_position = (triangle.A.coord[3] * area_A + triangle.B.coord[3] * area_B + triangle.C.coord[3] * area_C)/(area_A + area_B + area_C);
    one_over_z = 1/z_position;

    if(one_over_z > z_buffer[position.coord[1]][position.coord[0]]){
      z_buffer[position.coord[1]][position.coord[0]] = one_over_z;
      return true;
    }
  }

  return false;
}

bool Camera::AABB_Collision(int min_x, int max_x, int min_y, int max_y){
  if(min_x < width && max_x >= 0 && min_y < height && max_y >= 0){
    return true;
  }
  return false;
}

int Camera::DepthMap(int i, int j){
  int code = (int)(z_buffer[i][j] * 23);

  if(code >= 23){
    return bw_color_code[22];
  }
  else {
    return bw_color_code[code];
  }
}

int Camera::Lighting(Triangle triangle, Vec3 light){
  Vec3 triangle_normal = {triangle.normal.coord[0], triangle.normal.coord[1], triangle.normal.coord[2]};
  float dot_product = triangle_normal.Dot(light);
  if(dot_product < 0.0){
    return bw_color_code[(int)(dot_product * -22)];
  }
  return 232;
}

void Camera::DrawTriangle(Triangle triangle){
  Vec3 light = {0.0, -1.0, 1.0};
  Vec4 position;

  Vec4 AB = triangle.B - triangle.A;
  Vec4 BC = triangle.C - triangle.B;
  Vec3 AB_v3 = {AB.coord[0], AB.coord[1], AB.coord[2]};
  Vec3 BC_v3 = {BC.coord[0], BC.coord[1], BC.coord[2]};

  AB_v3.coord[2] = 0.0;
  BC_v3.coord[2] = 0.0;

  Vec3 triangle_normal_vector = AB_v3.Cross(BC_v3);
  Vec3 camera_normal = {0.0, 0.0, 1.0};

  if(triangle_normal_vector.Dot(camera_normal) < 0.0){
    return;
  }
  light.coord[0] = light.coord[0]/light.Norm();
  light.coord[1] = light.coord[1]/light.Norm();
  light.coord[2] = light.coord[2]/light.Norm();

  int min_x = std::min(std::min(triangle.A.coord[0], triangle.B.coord[0]), triangle.C.coord[0]);
  int max_x = std::max(std::max(triangle.A.coord[0], triangle.B.coord[0]), triangle.C.coord[0]);
  int min_y = std::min(std::min(triangle.A.coord[1], triangle.B.coord[1]), triangle.C.coord[1]);
  int max_y = std::max(std::max(triangle.A.coord[1], triangle.B.coord[1]), triangle.C.coord[1]);

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
    position.coord[1] = i;
    for(int j = min_x; j <= max_x; j++){
      position.coord[0] = j;
      if(CanDrawPixel(triangle, position)){
        screen[i][j] = Lighting(triangle, light);
        // screen[i][j] = triangle.color_code;
      }
    }
  }
}

void Camera::DrawObject(Object* object){
  Triangle render_triangle;
  float w1, w2, w3;

  for(auto &triangle : (*object).tri){
    //triangle get transformed by the combination of all transformations
    render_triangle.A = transformations[5].Multiply(triangle.A);
    render_triangle.B = transformations[5].Multiply(triangle.B);
    render_triangle.C = transformations[5].Multiply(triangle.C);

    //triangle normal gets rotated
    render_triangle.normal = transformations[2].Multiply(triangle.normal);

    //vertices get normalized after transformations
    w1 = render_triangle.A.coord[3];
    w2 = render_triangle.B.coord[3];
    w3 = render_triangle.C.coord[3];
    render_triangle.A = {render_triangle.A.coord[0]/w1, render_triangle.A.coord[1]/w1, render_triangle.A.coord[2]/w1, 1};
    render_triangle.B = {render_triangle.B.coord[0]/w2, render_triangle.B.coord[1]/w2, render_triangle.B.coord[2]/w2, 1};
    render_triangle.C = {render_triangle.C.coord[0]/w3, render_triangle.C.coord[1]/w3, render_triangle.C.coord[2]/w3, 1};

    // triangle gets transformed into screen space
    render_triangle.A = transformations[4].Multiply(render_triangle.A);
    render_triangle.B = transformations[4].Multiply(render_triangle.B);
    render_triangle.C = transformations[4].Multiply(render_triangle.C);

    render_triangle.A = {render_triangle.A.coord[0], render_triangle.A.coord[1], render_triangle.A.coord[2], w1};
    render_triangle.B = {render_triangle.B.coord[0], render_triangle.B.coord[1], render_triangle.B.coord[2], w2};
    render_triangle.C = {render_triangle.C.coord[0], render_triangle.C.coord[1], render_triangle.C.coord[2], w3};

    render_triangle.color_code = triangle.color_code;

    DrawTriangle(render_triangle);

    render_triangle.A = {0, 0, 0, 0};
    render_triangle.B = {0, 0, 0, 0};
    render_triangle.C = {0, 0, 0, 0};
    render_triangle.normal = {0, 0, 0, 0};
    render_triangle.color_code = 0;
  }
}

void Camera::Print(){
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

void Camera::ClearScreen(){
  std::cout << "\033[2J\033[H";
}

// TODO:
// check if a triangle is facing the camera or not before trying to draw it
