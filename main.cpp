#include "CTree.h"
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <fstream>
using namespace std;

int main() {
	Point bl(0, 0);
	Point tr(8, 8);
	Quad C(bl,tr);
	Point p(5, 5);
	C.Add(p);
	Point cp(1, 1);
	C.Add(cp);
	//Point c(1, 1);
	//C.Add(c);
	Point k(1, 7);
	C.Add(k);
	//Point m(7, 7);  ////??????????
	Point m(3, 3);
	C.Add(m);
	return 0;
}