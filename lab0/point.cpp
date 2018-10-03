#include "point.h"

double distance(point A, point B) {
	double x = A.x - B.x;
	double y = A.y - B.y;
	return sqrt(x * x + y * y);
}

double dot(point A, point B) {
	return A.x * B.x + A.y * B.y;
}

double point::length() {
	return sqrt(x * x + y * y);
}

void point::normalize() {
	double len = length();
	x /= len;
	y /= len;
	return;
}
