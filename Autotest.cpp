#include "CTree.h"
#include <iostream>
#include <fstream>
using namespace std;

void Autotest(void) {
	cout << "------------------" << endl;
	cout << "Autotest:" << endl;
	Point tr(6, 6);
	Quad C(tr);
	Point A(1, 1);
	Point B(2, 1);
	Point D(5, 4);
	C.Add(A);
	C.Add(B);
	C.Add(D);
	if (C.Quantity() == 3) {
		cout << "Autotest passed..." << endl;
	}
	else {
		cout << "Autotest falled..." << endl;
	}
}
