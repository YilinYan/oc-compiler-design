#include <iostream>
#include <cstdio>

#include "point.h"

int main(){
	point x = point(1.0, 2.0);
	point y = point(2.0, 3.0);
	point z;

	printf("v1(1.0, 2.0), v2(2.0, 3.0)\n");
	printf("dot: %lf\n", dot(x, y));
	printf("distance: %lf\n", distance(x, y));
	printf("v1 length: %lf\n", x.length());
	x.normalize();
	printf("v1 normalize: (%lf, %lf)\n", x.x, x.y);


	return 0;
}
