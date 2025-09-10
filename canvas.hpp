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

		void PerspectiveProjection(float, float, float);
		void Print();
};
