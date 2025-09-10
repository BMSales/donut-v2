#include "canvas.hpp"

int main(){
	Canvas canvas = Canvas();
	canvas.PerspectiveProjection(0.0, 50.0, 100.0);
	canvas.PerspectiveProjection(0.0, 0.0, 100.0);
	canvas.Print();
}

