#include "CTree.h"
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <fstream>
using namespace std;

int main() {
	Point tr(9, 9);
	Quad C(tr);
	Point p(1, 1);
	C.Add(p);
	Point a(2, 2);
	C.Add(a);
	C.DeleteNode(a);
	C.Add(a);
	Point d(3, 4);
	C.Add(d);
	Point r(9, 7);
	C.Add(r);
	Point c(1, 1);
	C.Add(c);
	Point m(8, 5);
	C.Find(m);
	C.Quantity();
	Autotest();
	return 0;
}