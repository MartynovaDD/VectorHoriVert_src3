#include "CTree.h"
#include <fstream>
#include <iostream>
//#include <cmath> 
#include <stdlib.h>
#include <stdio.h>
using namespace std;

// � ��������� �����������

int Quad::Add(Point _t) {
	Point t = _t;  // ����������� �����
	Point bl; //����� ������ ����
	Point tr; // ������ �������
	int a = 0; // 0 ���� ��������, 1 �������� �����
	CNode* n;
	Point null(NULL, NULL);
	CNode* nul = NULL;
	CNode* tochka = new CNode(null, nul ,bl, tr);;  // ����� ������ ��� ���� � ��������
	n = root;
	int f = 0, s = 0;
	// ������������ �������, �� ������������� ������
	if ((root->bl.x > t.x && t.x > root->tr.x) || (root->bl.y > t.y && t.y > root->tr.y)) { // ���� ����� ������� �� ������� 
		return -1;
	}
	else {
		if (root->p.x == NULL && root->k == false) {  // ��������� ������ �����
			root->p.x = t.x;
			root->p.y = t.y;
			root->k = true;
			cout << "yraaa" << endl;
			return 0;
		}
		else {
			//tochka->p.x = n->p.x; tochka->p.y = n->p.y;           //���������� ����� ������� ��� ���� � ��������, ������ ��� � ��������
			//for (n = root; n != NULL;) {
			while (a != 1) {       // ���� �� �c�����
				if (n->p.x == t.x && n->p.y == t.y) { a = 1; return -1; } // ���� ��� ���� ��� �����
				else if (t.x > (n->tr.x - n->bl.x) / 2 && t.y > (n->tr.y - n->bl.y) / 2) {   // ���� ����� �������� � ������ ������� ����
					cout << "a" << endl;
					if (n->p.x != NULL) {       // ���� ��� ��� ���� �����
						if (f == 0) {
							tochka->p.x = n->p.x; tochka->p.y = n->p.y;                            // ���������� ��� �����
							f = 1;
							n->p.x = NULL;
							n->p.y = NULL;
						}
						if (tochka->p.x > (n->tr.x + n->bl.x) / 2 && tochka->p.y > (n->tr.y + n->bl.y) / 2) {  //����� �������� ���� ��
							bl = Point((n->tr.x + n->bl.x) / 2, (n->tr.y + n->bl.y) / 2);
							tr = Point(n->tr.x, n->tr.y);
							n->TR = new CNode(bl, tr);
							s = 1;
							//tochka->p.x = n->p.x; tochka->p.y = n->p.y;
							n = n->TR;  // �������
							cout << "c" << endl;
						}
						else if (tochka->p.x < (n->tr.x + n->bl.x) / 2 && tochka->p.y >(n->tr.y + n->bl.y) / 2) { //���� ����� �������� � ������ ������� ��� ���������
							bl = Point(n->bl.x, (n->tr.y + n->bl.y) / 2);
							tr = Point((n->tr.x + n->bl.x) / 2, n->tr.y);
							n->TL = new CNode(tochka->p, n, bl, tr);
							tochka->p.x = NULL; tochka->p.y = NULL;
							bl = Point((n->tr.x + n->bl.x) / 2, (n->tr.y + n->bl.y) / 2);
							tr = Point(n->tr.x, n->tr.y);
							n->TR = new CNode(t, n, bl, tr);
							a = 1;
							//return 0;
							cout << "c" << endl;
						}
						else if (tochka->p.x < (n->tr.x + n->bl.x) / 2 && tochka->p.y < (n->tr.y + n->bl.y) / 2) {//���� ����� �������� � ������ ������� ��� ���������
							cout << "bbbbbbbbbbbbbb" << endl;
							bl = Point(n->bl.x, n->bl.y);
							tr = Point((n->tr.x + n->bl.x) / 2, (n->tr.y + n->bl.y) / 2);
							n->BL = new CNode(tochka->p, n, bl, tr);
							tochka->p.x = NULL; tochka->p.y = NULL;
							bl = Point((n->tr.x + n->bl.x) / 2, (n->tr.y + n->bl.y) / 2);
							tr = Point(n->tr.x, n->tr.y);
							n->TR = new CNode(t, n, bl, tr);
							a = 1;
							//return 0;
							cout << "c" << endl;
						}
						else if (tochka->p.x > (n->tr.x + n->bl.x) / 2 && tochka->p.y < (n->tr.y + n->bl.y) / 2) {//���� ����� �������� � ������ ������� ��� ���������
							bl = Point((n->tr.x + n->bl.x) / 2, n->bl.y);
							tr = Point(n->tr.x, (n->tr.y + n->bl.y) / 2);
							n->BR = new CNode(tochka->p, n, bl, tr); //������� ������� ��� �������� �����
							tochka->p.x = NULL; tochka->p.y = NULL;  //���������� ����� �� ������ �������
							bl = Point((n->tr.x + n->bl.x) / 2, (n->tr.y + n->bl.y) / 2);
							tr = Point(n->tr.x, n->tr.y);
							n->TR = new CNode(t, n, bl, tr);
							a = 1;
							//return 0;
							cout << "c" << endl;
						}

					}
					else if (s == 0 && n->p.x == NULL && n->p.y == NULL && n->k == false) {//............���� ��� ����� � ������� �� ����     // ����� �� ������ ���� ����� ��������???
						bl = Point((n->tr.x - n->bl.x) / 2, (n->tr.y - n->bl.y) / 2);
						tr = Point(n->tr.x, n->tr.y);
						n->TR = new CNode(t, n, bl, tr);
						a = 1;
						//return 0;
						cout << "c" << endl;
					}
					else if (s == 0 && n->p.x == NULL && n->p.y == NULL && n->k == true) {// .....................���� ��� �����, �� ����, � ������ ��� � ������
						bl = Point((n->tr.x - n->bl.x) / 2, (n->tr.y - n->bl.y) / 2);
						tr = Point(n->tr.x, n->tr.y);
						n->TR = new CNode(bl, tr);
						n = n->TR;
						a = 0;
						cout << "b" << endl;
						//cout << "c" << endl;
					}
				}


				else if (t.x < (n->tr.x - n->bl.x) / 2 && t.y >(n->tr.y - n->bl.y) / 2) {   // ���� ����� �������� � ����� ������� ����
					//cout << "neploho" << endl;
					if (n->p.x != NULL) {       // ���� ��� ��� ���� �����
						if (f == 0) {
							tochka->p.x = n->p.x; tochka->p.y = n->p.y;                            // ���������� ��� �����
							f = 1;
							n->p.x = NULL;
							n->p.y = NULL;
						}
						if (tochka->p.x < (n->tr.x + n->bl.x) / 2 && tochka->p.y >(n->tr.y + n->bl.y) / 2) {  //�� ��� ��� ���� �����, ������� ��������� � �� �������(��������� �������) � ������ ���� ����� ��� ����
							bl = Point(n->bl.x, (n->tr.y + n->bl.y) / 2);
							tr = Point((n->tr.x + n->bl.x) / 2, n->tr.y);
							n->TL = new CNode(bl, tr);
							n = n->TL;  // �������
							s = 1;
							//cout << "horosho" << endl;
						}
						else if (tochka->p.x < (n->tr.x + n->bl.x) / 2 && tochka->p.y < (n->tr.y + n->bl.y) / 2) { //���� ����� �������� � ������ ������� ��� ���������
							bl = Point(n->bl.x, n->bl.y);
							tr = Point((n->tr.x + n->bl.x) / 2, (n->tr.y + n->bl.y) / 2);
							n->BL = new CNode(tochka->p, n, bl, tr);
							tochka->p.x = NULL; tochka->p.y = NULL;
							bl = Point(n->bl.x, (n->tr.y + n->bl.y) / 2);
							tr = Point((n->tr.x + n->bl.x) / 2, n->tr.y);
							n->TL = new CNode(t, n, bl, tr);
							a = 1;
							//return 0;
							//cout << "horosho" << endl;
						}
						else if (tochka->p.x > (n->tr.x + n->bl.x) / 2 && tochka->p.y < (n->tr.y + n->bl.y) / 2) {//���� ����� �������� � ������ ������� ��� ���������
							bl = Point((n->tr.x + n->bl.x) / 2, n->bl.y);
							tr = Point(n->tr.x, (n->tr.y + n->bl.y) / 2);
							n->BR = new CNode(tochka->p, n, bl, tr);
							tochka->p.x = NULL; tochka->p.y = NULL;
							bl = Point(n->bl.x, (n->tr.y + n->bl.y) / 2);
							tr = Point((n->tr.x + n->bl.x) / 2, n->tr.y);
							n->TL = new CNode(t, n, bl, tr);
							a = 1;
							//return 0;
							cout << "horosho" << endl;
						}
						else if (tochka->p.x > (n->tr.x + n->bl.x) / 2 && tochka->p.y > (n->tr.y + n->bl.y) / 2) {//���� ����� �������� � ������ ������� ��� ���������
							cout << tochka->p.x << endl;
							bl = Point((n->tr.x + n->bl.x) / 2, (n->tr.y + n->bl.y) / 2);
							tr = Point(n->tr.x, n->tr.y);
							n->TR = new CNode(tochka->p, n, bl, tr); //������� ������� ��� �������� �����
							tochka->p.x = NULL; tochka->p.y = NULL;  //���������� ����� �� ������ �������
							bl = Point(n->bl.x, (n->tr.y + n->bl.y) / 2);
							tr = Point((n->tr.x + n->bl.x) / 2, n->tr.y);
							n->TL = new CNode(t, n, bl, tr);
							a = 1;
							//return 0;
							//cout << "horosho" << endl;
						}
					}
					else if (s == 0 && n->p.x == NULL && n->p.y == NULL && n->k == false) {//............���� ��� ����� � ������� �� ����     // ����� �� ������ ���� ����� ��������???
						bl = Point(n->bl.x, (n->tr.y + n->bl.y) / 2);
						tr = Point((n->tr.x + n->bl.x) / 2, n->tr.y);
						n->TL = new CNode(t, n, bl, tr);
						//cout << "otlichno" << endl;
						a = 1;
						//return 0;
						//cout << "horosho" << endl;
					}
					else if (s == 0 && n->p.x == NULL && n->p.y == NULL && n->k == true) {// .....................���� ��� �����, �� ����, � ������ ��� � ������
						bl = Point(n->bl.x, (n->tr.y + n->bl.y) / 2);
						tr = Point((n->tr.x + n->bl.x) / 2, n->tr.y);
						n->TL = new CNode(bl, tr);
						n = n->TL;
						a = 0;
						cout << "horosho" << endl;
					}
				}


				else if (t.x < (n->tr.x - n->bl.x) / 2 && t.y < (n->tr.y - n->bl.y) / 2) {   // ���� ����� �������� � ����� ������ ����
				cout << "hey" << endl;
					if (n->p.x != NULL) {       // ���� ��� ��� ���� �����
						
						if (f == 0) {
							tochka->p.x = n->p.x; tochka->p.y = n->p.y;                            // ���������� ��� �����
							f = 1;
							n->p.x = NULL;
							n->p.y = NULL;
						}
						if (tochka->p.x < (n->tr.x + n->bl.x) / 2 && tochka->p.y < (n->tr.y + n->bl.y) / 2) {  //�� ��� ��� ���� �����, ������� ��������� � �� �������(��������� �������) � ������ ���� ����� ��� ����
							bl = Point(n->bl.x, n->bl.y);
							tr = Point((n->tr.x + n->bl.x) / 2, (n->tr.y + n->bl.y) / 2);
							n->BL = new CNode(bl, tr);
							n = n->BL;  // �������
							s = 1;
						}
						else if (tochka->p.x > (n->tr.x + n->bl.x) / 2 && tochka->p.y < (n->tr.y + n->bl.y) / 2) { //���� ����� �������� � ������ ������� ��� ���������
							bl = Point((n->tr.x + n->bl.x) / 2, n->bl.y);
							tr = Point(n->tr.x, (n->tr.y + n->bl.y) / 2);
							n->BR = new CNode(tochka->p, n, bl, tr);
							tochka->p.x = NULL; tochka->p.y = NULL;
							bl = Point(n->bl.x, n->bl.y);
							tr = Point((n->tr.x + n->bl.x) / 2, (n->tr.y + n->bl.y) / 2);
							n->BL = new CNode(t, n, bl, tr);
							a = 1;
							//return 0;
						}
						else if (tochka->p.x > (n->tr.x + n->bl.x) / 2 && tochka->p.y > (n->tr.y + n->bl.y) / 2) {//���� ����� �������� � ������ ������� ��� ���������
							cout << "tyt" << endl;
							bl = Point((n->tr.x + n->bl.x) / 2, (n->tr.y + n->bl.y) / 2);
							tr = Point(n->tr.x, n->tr.y);
							n->TR = new CNode(tochka->p, n, bl, tr);
							cout << tochka->bl.x << endl;
							//tochka->p.x = NULL; tochka->p.y = NULL;
							cout << tochka->k << endl;                      // ������ FALSE 0
							cout << tochka->p.x << endl;                      
							bl = Point(n->bl.x, n->bl.y);
							tr = Point((n->tr.x + n->bl.x) / 2, (n->tr.y + n->bl.y) / 2);
							n->BL = new CNode(t, n, bl, tr);
							a = 1;
							//return 0;
						}
						else if (tochka->p.x < (n->tr.x + n->bl.x) / 2 && tochka->p.y >(n->tr.y + n->bl.y) / 2) {//���� ����� �������� � ������ ������� ��� ���������
							bl = Point(n->bl.x, (n->tr.y + n->bl.y) / 2);
							tr = Point((n->tr.x + n->bl.x) / 2, n->tr.y);
							n->TL = new CNode(tochka->p, n, bl, tr); //������� ������� ��� �������� �����
							tochka->p.x = NULL; tochka->p.y = NULL;  //���������� ����� �� ������ �������
							bl = Point(n->bl.x, n->bl.y);
							tr = Point((n->tr.x + n->bl.x) / 2, (n->tr.y + n->bl.y) / 2);
							n->BL = new CNode(t, n, bl, tr);
							a = 1;
							//return 0;
						}
					}
					else if (s == 0 && n->p.x == NULL && n->p.y == NULL && n->k == false) {//............���� ��� ����� � ������� �� ����     // ����� �� ������ ���� ����� ��������???
						bl = Point(n->bl.x, (n->tr.y + n->bl.y) / 2);
						tr = Point((n->tr.x + n->bl.x) / 2, n->tr.y);
						n->BL = new CNode(t, n, bl, tr);
						a = 1;
						cout << "jjjjjjjjjjjjjjjjjjjjjjjj" << endl;
						//return 0;
					}
					else if (s == 0 && n->p.x == NULL && n->p.y == NULL && n->k == true) {// .....................���� ��� �����, �� ����, � ������ ��� � ������
						cout << "aaaaaa" << endl;
						bl = Point(n->bl.x, (n->tr.y + n->bl.y) / 2);
						tr = Point((n->tr.x + n->bl.x) / 2, n->tr.y);
						n->BL = new CNode(bl, tr);
						n = n->BL;
						a = 0;
					}
				}


				else if (t.x > (n->tr.x - n->bl.x) / 2 && t.y < (n->tr.y - n->bl.y) / 2) {   // ���� ����� �������� � ������ ������ ����
					if (n->p.x != NULL) {       // ���� ��� ��� ���� �����
						if (f == 0) {
							tochka->p.x = n->p.x; tochka->p.y = n->p.y;                            // ���������� ��� �����
							f = 1;
							n->p.x = NULL;
							n->p.y = NULL;
						}
						if (tochka->p.x > (n->tr.x + n->bl.x) / 2 && tochka->p.y < (n->tr.y + n->bl.y) / 2) {  //�� ��� ��� ���� �����, ������� ��������� � �� �������(��������� �������) � ������ ���� ����� ��� ����
							bl = Point((n->tr.x + n->bl.x) / 2, n->bl.y);
							tr = Point(n->tr.x, (n->tr.y + n->bl.y) / 2);
							n->BR = new CNode(bl, tr);
							n = n->BR;  // �������
							s = 1;
						}
						else if (tochka->p.x > (n->tr.x + n->bl.x) / 2 && tochka->p.y > (n->tr.y + n->bl.y) / 2) { //���� ����� �������� � ������ ������� ��� ���������
							bl = Point((n->tr.x + n->bl.x) / 2, (n->tr.y + n->bl.y) / 2);
							tr = Point(n->tr.x, n->tr.y);
							n->TR = new CNode(tochka->p, n, bl, tr);
							tochka->p.x = NULL; tochka->p.y = NULL;
							bl = Point((n->tr.x + n->bl.x) / 2, n->bl.y);
							tr = Point(n->tr.x, (n->tr.y + n->bl.y) / 2);
							n->BR = new CNode(t, n, bl, tr);
							a = 1;
							//return 0;
						}
						else if (tochka->p.x < (n->tr.x + n->bl.x) / 2 && tochka->p.y >(n->tr.y + n->bl.y) / 2) {//���� ����� �������� � ������ ������� ��� ���������
							bl = Point(n->bl.x, (n->tr.y + n->bl.y) / 2);
							tr = Point((n->tr.x + n->bl.x) / 2, n->tr.y);
							n->TL = new CNode(tochka->p, n, bl, tr);
							tochka->p.x = NULL; tochka->p.y = NULL;
							bl = Point((n->tr.x + n->bl.x) / 2, n->bl.y);
							tr = Point(n->tr.x, (n->tr.y + n->bl.y) / 2);
							n->BR = new CNode(t, n, bl, tr);
							a = 1;
							//return 0;
						}
						else if (tochka->p.x < (n->tr.x + n->bl.x) / 2 && tochka->p.y < (n->tr.y + n->bl.y) / 2) {//���� ����� �������� � ������ ������� ��� ���������
							bl = Point(n->bl.x, n->bl.y);
							tr = Point((n->tr.x + n->bl.x) / 2, (n->tr.y + n->bl.y) / 2);
							n->BL = new CNode(tochka->p, n, bl, tr); //������� ������� ��� �������� �����
							tochka->p.x = NULL; tochka->p.y = NULL;  //���������� ����� �� ������ �������
							bl = Point((n->tr.x + n->bl.x) / 2, n->bl.y);
							tr = Point(n->tr.x, (n->tr.y + n->bl.y) / 2);
							n->BR = new CNode(t, n, bl, tr);
							a = 1;
							//return 0;
						}
					}
					else if (s == 0 && n->p.x == NULL && n->p.y == NULL && n->k == false) {//............���� ��� ����� � ������� �� ����     // ����� �� ������ ���� ����� ��������???
						bl = Point((n->tr.x + n->bl.x) / 2, n->bl.y);
						tr = Point(n->tr.x, (n->tr.y + n->bl.y) / 2);
						n->BR = new CNode(t, n, bl, tr);
						a = 1;
						//return 0;
					}
					else if (s == 0 && n->p.x == NULL && n->p.y == NULL && n->k == true) {// .....................���� ��� �����, �� ����, � ������ ��� � ������
						bl = Point((n->tr.x + n->bl.x) / 2, n->bl.y);
						tr = Point(n->tr.x, (n->tr.y + n->bl.y) / 2);
						n->BR = new CNode(bl, tr);
						n = n->BR;
						a = 0;
					}
				}
			}
			return 0;
		}
	}
}




int Quad::DeleteNode(Point _t) {
	Point t = _t;  // ����������� �����
	//Point bl; //����� ������ ����
	//Point tr; // ������ �������
	int a = 0; // 0 ���� ��������, 1 �������� �����
	CNode* n;
	//CNode* tochka;  // ����� ������ ��� ���� � ��������
	n = root;
	// ������������ �������, �� ������������� ������
	if ((root->bl.x > t.x && t.x  > root->tr.x) || (root->bl.y > t.y && t.y > root->tr.y)) { // ���� ����� ������� �� ������� 
		return -1;
	}
	else if (root->p.x == t.x && root->p.y == t.y) {
		delete root;
		return 0;
	}
	else {
		while (a != 1) {
			if (n == NULL) {
				cout << "not this number" << endl;
				a = 1;
			}
			//������� ��� ��������� ����� ��� ������������
			//if (n->p.x == t.x && n->p.y == t.y) { delete n; a = 1; return -1; } // ���� ��� ���� ��� �����
			//tochka->p.x = n->p.x; tochka->p.y = n->p.y;           //���������� ����� ������� ��� ���� � ��������, ������ ��� � ��������
			if (t.x > (n->tr.x - n->bl.x) / 2 && t.y > (n->tr.y - n->bl.y) / 2) {
				if (n->TR->p.x == t.x && n->TR->p.y == t.y) {
					delete n->TR;
					a = 1;
					//return 1;
				}
				else {
					n = n->TR;
				}
			}
			else if (t.x < (n->tr.x - n->bl.x) / 2 && t.y >(n->tr.y - n->bl.y) / 2) {
				if (n->TL->p.x == t.x && n->TL->p.y == t.y) {
					delete n->TL;
					a = 1;
					//return 1;
				}
				else {
					n = n->TL;
				}
			}
			else if (t.x < (n->tr.x - n->bl.x) / 2 && t.y < (n->tr.y - n->bl.y) / 2) {
				if (n->BL->p.x == t.x && n->BL->p.y == t.y) {
					delete n->BL;
					a = 1;
					//return 1;
				}
				else {
					n = n->BL;
				}
			}
			else if (t.x > (n->tr.x - n->bl.x) / 2 && t.y < (n->tr.y - n->bl.y) / 2) {
				if (n->BR->p.x == t.x && n->BR->p.y == t.y) {
					delete n->BR;
					a = 1;
					//return 1;
				}
				else {
					n = n->BR;
				}
			}
		}
		return 0;
	}
}

bool Quad::Find(Point _t) {
	Point t = _t;  // ����������� �����
	int a = 0; // 0 ���� ��������, 1 �������� �����
	CNode* n;
	n = root;
	bool l;
	if ((root->bl.x > t.x && t.x > root->tr.x) || (root->bl.y > t.y && t.y > root->tr.y)) { // ���� ����� ������� �� ������� 
		return false;
	}
	else if (root->p.x == t.x && root->p.y == t.y) {
		a = 1;
		return true;
	}
	else {
		while (a != 1) {
			if (n == NULL) {
				a = 1;
				l = false;
			}
			if (t.x > (n->tr.x - n->bl.x) / 2 && t.y > (n->tr.y - n->bl.y) / 2) {
				if (n->TR->p.x == t.x && n->TR->p.y == t.y) {
					a = 1;
					l = true;
				}
				else {
					n = n->TR;
				}
			}
			else if (t.x < (n->tr.x - n->bl.x) / 2 && t.y >(n->tr.y - n->bl.y) / 2) {
				if (n->TL->p.x == t.x && n->TL->p.y == t.y) {
					a = 1;
					l = true;
				}
				else {
					n = n->TL;
				}
			}
			else if (t.x < (n->tr.x - n->bl.x) / 2 && t.y < (n->tr.y - n->bl.y) / 2) {
				if (n->BL->p.x == t.x && n->BL->p.y == t.y) {
					a = 1;
					l = true;
				}
				else {
					n = n->BL;
				}
			}
			else if (t.x > (n->tr.x - n->bl.x) / 2 && t.y < (n->tr.y - n->bl.y) / 2) {
				if (n->BR->p.x == t.x && n->BR->p.y == t.y) {
					a = 1;
					l = true;
				}
				else {
					n = n->BR;
				}
			}
		}
		return l;
	}
}