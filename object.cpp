#include <cmath>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <ranges>
#include <vector>

#include "object.hpp"

#define M_PI 3.14159265358979323846

Object::Object(std::string pathToFile){
  std::ifstream object_file(pathToFile);
  std::string line;
  std::string objVertex;
  std::string objTexture;
  std::string objNormal;
  std::string objFace;
  char faceData = 'v';

  Triangle objTriangle;

  int k = 0;

  if(!object_file){
    std::cout << "ERROR: could not open file" << std::endl;
    exit(-1);
  }

  while(getline(object_file, line)){
    if(line.substr(0, 2) == "v "){
      for(int i = 2; line[i] != '\0'; i++){
        objVertex += line[i];
        if(line[i] == ' ' || line[i + 1] == '\0'){
          vert.push_back(stof(objVertex));
          objVertex = "";
        }
      }
    }

    if(line.substr(0, 2) == "vt"){
      for(int i = 3; line[i] != '\0'; i++){
        objTexture += line[i];
        if(line[i] == ' ' || line[i + 1] == '\0'){
          texture.push_back(stof(objTexture));
          objTexture = "";
        }
      }
    }

    if(line.substr(0, 2) == "vn"){
      for(int i = 3; line[i] != '\0'; i++){
        objNormal += line[i];
        if(line[i] == ' ' || line[i + 1] == '\0'){
          faceNormal.push_back(stof(objNormal));
          objNormal = "";
        }
      }
    }

    if(line.substr(0, 2) == "f "){
      vertIndex.push_back(std::vector<int>());
      textureIndex.push_back(std::vector<int>());
      normIndex.push_back(std::vector<int>());
      for(int i = 2; line[i] != '\0'; i++){
        objFace += line[i];
        if(line[i] == '/' && faceData == 'v'){
          vertIndex[k].push_back(stoi(objFace));
          objFace = "";
          faceData = 't';
        }
        else if(line[i] == '/' && faceData == 't'){
          textureIndex[k].push_back(stoi(objFace));
          objFace = "";
        }
        else if(line[i] == ' ' || line[i + 1] == '\0'){
          normIndex[k].push_back(stoi(objFace));
          objFace = "";
          faceData = 'v';
        }
      }
      k++;
    }
  }

  int firstVertex;
	float normHelper = 0.0;
  if(vertIndex[0][0] < 0){
    firstVertex = - vert.size() / 3;
  }
  else {
    firstVertex = 1;
  }

  for(auto [vertex, texture, normal] : std::views::zip(vertIndex, textureIndex, normIndex)){
		objTriangle.A = {vert[(vertex[0] - firstVertex) * 3], vert[(vertex[0] - firstVertex) * 3 + 1], vert[(vertex[0] - firstVertex) * 3 + 2], 1};
		objTriangle.B = {vert[(vertex[1] - firstVertex) * 3], vert[(vertex[1] - firstVertex) * 3 + 1], vert[(vertex[1] - firstVertex) * 3 + 2], 1};
		objTriangle.C = {vert[(vertex[2] - firstVertex) * 3], vert[(vertex[2] - firstVertex) * 3 + 1], vert[(vertex[2] - firstVertex) * 3 + 2], 1};
    // objTriangle.A.x = vert[(vertex[0] - firstVertex) * 3];
    // objTriangle.A.y = vert[(vertex[0] - firstVertex) * 3 + 1];
    // objTriangle.A.z = vert[(vertex[0] - firstVertex) * 3 + 2];

    // objTriangle.B.x = vert[(vertex[1] - firstVertex) * 3];
    // objTriangle.B.y = vert[(vertex[1] - firstVertex) * 3 + 1];
    // objTriangle.B.z = vert[(vertex[1] - firstVertex) * 3 + 2];
    //
    // objTriangle.C.x = vert[(vertex[2] - firstVertex) * 3];
    // objTriangle.C.y = vert[(vertex[2] - firstVertex) * 3 + 1];
    // objTriangle.C.z = vert[(vertex[2] - firstVertex) * 3 + 2];

		objTriangle.normal = {faceNormal[(normal[0] - firstVertex) * 3], faceNormal[(normal[0] - firstVertex) * 3 + 1], faceNormal[(normal[0] - firstVertex) * 3 + 2], 1};
    // objTriangle.normal.x = faceNormal[(normal[0] - firstVertex) * 3];
    // objTriangle.normal.y = faceNormal[(normal[0] - firstVertex) * 3 + 1];
    // objTriangle.normal.z = faceNormal[(normal[0] - firstVertex) * 3 + 2];

		normHelper = objTriangle.normal.Norm();
		objTriangle.normal = {objTriangle.normal.coord[0]/normHelper, objTriangle.normal.coord[1]/normHelper, objTriangle.normal.coord[2]/normHelper, 1}
    // objTriangle.normal.x = objTriangle.normal.x / objTriangle.normal.Norm();
    // objTriangle.normal.y = objTriangle.normal.y / objTriangle.normal.Norm();
    // objTriangle.normal.z = objTriangle.normal.z / objTriangle.normal.Norm();
    
    tri.push_back(objTriangle);
    if(vertex.size() > 3){
      for(int i = 3; i < vertex.size(); i++){
        objTriangle.B = objTriangle.C;
				objTriangle.C = {vert[(vertex[i] - firstVertex) * 3], vert[(vertex[i] - firstVertex) * 3 + 1], vert[(vertex[i] - firstVertex) * 3 + 2], 1};
        // objTriangle.C.x = vert[(vertex[i] - firstVertex) * 3];
        // objTriangle.C.y = vert[(vertex[i] - firstVertex) * 3 + 1];
        // objTriangle.C.z = vert[(vertex[i] - firstVertex) * 3 + 2];

				objTriangle.normal = {faceNormal[(normal[i] - firstVertex) * 3], faceNormal[(normal[i] - firstVertex) * 3 + 1], faceNormal[(normal[i] - firstVertex) * 3 + 2], 1};
        // objTriangle.normal.x = faceNormal[(normal[i] - firstVertex) * 3];
        // objTriangle.normal.y = faceNormal[(normal[i] - firstVertex) * 3 + 1];
        // objTriangle.normal.z = faceNormal[(normal[i] - firstVertex) * 3 + 2];

				normHelper = objTriangle.normal.Norm();
				objTriangle.normal = {objTriangle.normal.coord[0]/normHelper, objTriangle.normal.coord[1]/normHelper, objTriangle.normal.coord[2]/normHelper, 1}
        // objTriangle.normal.x = objTriangle.normal.x / objTriangle.normal.Norm();
        // objTriangle.normal.y = objTriangle.normal.y / objTriangle.normal.Norm();
        // objTriangle.normal.z = objTriangle.normal.z / objTriangle.normal.Norm();

        tri.push_back(objTriangle);
      }
    }
  }
}

void Object::SetRandomColors(){
  std::random_device device;
  std::default_random_engine engine(device());
  std::uniform_int_distribution<int> uniform_dist(0, 255);

  for(auto &triangle : tri){
    triangle.color_code = uniform_dist(engine);
  }
}
