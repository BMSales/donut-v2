#pragma once

class Canvas{
	private:
		int height;
		int width;
		char** matrix;

		float fov;
		float aspect_ratio;
		float transform;

    void ScreenSpacePerspectiveProjection(float vertex[3], int screen_space_vertex[][2]);

	public:
		Canvas();
		~Canvas();

		void DrawTriangle(float vertex_1[3], float vertex_2[3], float vertex_3[3]);
    void ChangeFOV(float new_fov);
		void Print();
  };
