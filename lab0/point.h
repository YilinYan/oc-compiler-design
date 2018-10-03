#ifndef __POINT_H__
#define __POINT_H__

#include <cmath>

class point{
	public:
		point(): x(0), y(0) {}
		point(double a, double b) {
			x = a;
			y = b;
		}
		void normalize();
		double length();
	public:
		double x, y;
};

double distance(point A, point B);
double dot(point A, point B);

#endif
