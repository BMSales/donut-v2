#pragma once

class Shape {
	protected:
		int num_points;
		float** points;

	public:
		~Shape();
    void Rotate_X(float angle);
    void Rotate_Y(float angle);
    void Rotate_Z(float angle);
};

// class Torus : public Shape {
//   public:
//
// }
