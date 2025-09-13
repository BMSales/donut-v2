#pragma once

class Canvas{
	private:
		int height;
		int width;
		char** matrix;

		float fov;
		float aspect_ratio;
		float transform;


	public:
		Canvas();
		~Canvas();

		void DrawTriangle(float* vertex_1, float* vertex_2, float* vertex_3);
    void ChangeFOV(float new_fov);
		void Print();
};
