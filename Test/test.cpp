#include <cstdio>
#include "vertex.h"

void point_test() {
	Vertex *v = new Vertex();
	v->set_point({ 1, 2 });
	printf("%lf\n", v->point().first);
	return;
}

int main() {
    point_test();
    return 0;
}