#include "CTree.h"
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <fstream>
using namespace std;

int main() {
	Point bl(0, 0);
	Point tr(9, 9);
	Quad C(bl, tr);
	Point p(1, 1);
	C.Add(p);
	Point a(2, 2);
	C.Add(a);
	/*C.DeleteNode(a);
	C.Add(a);
	Point cp(3, 4);
	C.Add(cp);
	Point c(1, 1);
	C.Add(c);
	Point m(8, 5);
	C.Find(m);
	C.Quantity();
	C.Vicinity(p);
	Autotest();*/
	return 0;
}