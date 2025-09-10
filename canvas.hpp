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

		void PerspectiveProjection(float x, float y, float z);
    void ChangeFOV(float new_fov);
		void Print();
};
