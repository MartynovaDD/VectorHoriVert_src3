#include "CTree.h"
#include <queue>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;


int Quad::Add(Point _t) {
	Point t = _t;  // вставляемая точка
	Point bl; //левый нижний угол
	Point tr; // правый вегхний
	int a = 0; // 0 если вставили, 1 вставили точку
	CNode* n;
	Point null(NULL, NULL);
	CNode* nul = NULL;
	CNode* tochka = new CNode(null, nul, bl, tr);;  // точка котрая уже есть в квадрате
	n = root;
	int f = 0, s = 0;
	if (t.x < root->bl.x || t.x > root->tr.x || t.y > root->tr.y || t.y < root->bl.y) {   // если точка выходит за границы 
		cout << "tochka ne vhodit v oblast'" << endl;
		return -1;
	}
	else {
		if (root->p.x == NULL && root->k == false) {  // вставляем первую точку
			root->p.x = t.x;
			root->p.y = t.y;
			root->k = true;
			cout << "dobavili vershiny (" << t.x << "," << t.y << ")" << endl;
			return 0;
		}
		else {
			while (a != 1) {       // пока не вcтавим
				if (n->p.x == t.x && n->p.y == t.y) { a = 1; cout << "tochka (" << t.x << "," << t.y << ") yze est'" << endl; return -1; } // если уже есть эта точка
				else if (t.x == (n->tr.x + n->bl.x) / 2 || t.y == (n->tr.y + n->bl.y) / 2) {   // если точка попадает на пересечение
					a = 1;
					cout << "ne vstavili tochky. popadaet na peresechenie" << endl;
				}
				else if (t.x > (n->tr.x + n->bl.x) / 2 && t.y > (n->tr.y + n->bl.y) / 2) {   // если точка попадает в правый верхний угол
					if (n->p.x != NULL || tochka->p.x != NULL) {       // если там уже есть точка
						if (f == 0) {
							tochka->p.x = n->p.x; tochka->p.y = n->p.y;                            // запоминаем эту точку
							f = 1;
							n->p.x = NULL;
							n->p.y = NULL;
						}
						if (tochka->p.x == (n->tr.x + n->bl.x) / 2 && tochka->p.y == (n->tr.y + n->bl.y) / 2) { // если существующая точка при разбиении попадет на пересечение
							a = 1;
							cout << "ne vstavili tochky" << endl;
						}
						else if (tochka->p.x > (n->tr.x + n->bl.x) / 2 && tochka->p.y > (n->tr.y + n->bl.y) / 2) {  //точка попадает туда же
							bl = Point((n->tr.x + n->bl.x) / 2, (n->tr.y + n->bl.y) / 2);
							tr = Point(n->tr.x, n->tr.y);
							n->TR = new CNode(null, n, bl, tr);
							n->TR->k = true;
							s = 1;
							n = n->TR;  // переход
						}
						else if (tochka->p.x < (n->tr.x + n->bl.x) / 2 && tochka->p.y >(n->tr.y + n->bl.y) / 2) { //если точка попадает в другой квадрат при разбиении
							bl = Point(n->bl.x, (n->tr.y + n->bl.y) / 2);
							tr = Point((n->tr.x + n->bl.x) / 2, n->tr.y);
							n->TL = new CNode(tochka->p, n, bl, tr);
							tochka->p.x = NULL; tochka->p.y = NULL;
							bl = Point((n->tr.x + n->bl.x) / 2, (n->tr.y + n->bl.y) / 2);
							tr = Point(n->tr.x, n->tr.y);
							n->TR = new CNode(t, n, bl, tr);
							a = 1;
							n = n->TR;
						}
						else if (tochka->p.x < (n->tr.x + n->bl.x) / 2 && tochka->p.y < (n->tr.y + n->bl.y) / 2) {//если точка попадает в другой квадрат при разбиении
							bl = Point(n->bl.x, n->bl.y);
							tr = Point((n->tr.x + n->bl.x) / 2, (n->tr.y + n->bl.y) / 2);
							n->BL = new CNode(tochka->p, n, bl, tr);
							tochka->p.x = NULL; tochka->p.y = NULL;
							bl = Point((n->tr.x + n->bl.x) / 2, (n->tr.y + n->bl.y) / 2);
							tr = Point(n->tr.x, n->tr.y);
							n->TR = new CNode(t, n, bl, tr);
							a = 1;
							n = n->TR;
						}
						else if (tochka->p.x > (n->tr.x + n->bl.x) / 2 && tochka->p.y < (n->tr.y + n->bl.y) / 2) {//если точка попадает в другой квадрат при разбиении
							bl = Point((n->tr.x + n->bl.x) / 2, n->bl.y);
							tr = Point(n->tr.x, (n->tr.y + n->bl.y) / 2);
							n->BR = new CNode(tochka->p, n, bl, tr); //создаем квадрат для исходной точки
							tochka->p.x = NULL; tochka->p.y = NULL;  //перемещаем точку на нижний уровень
							bl = Point((n->tr.x + n->bl.x) / 2, (n->tr.y + n->bl.y) / 2);
							tr = Point(n->tr.x, n->tr.y);
							n->TR = new CNode(t, n, bl, tr);
							a = 1;
							n = n->TR;
						}
					}
					else if (s == 0 && n->p.x == NULL && n->p.y == NULL && n->TR == NULL) {//............если нет точек и никогда не было     // могут ли вообще быть такие ситуации???
						bl = Point((n->tr.x + n->bl.x) / 2, (n->tr.y + n->bl.y) / 2);
						tr = Point(n->tr.x, n->tr.y);
						n->TR = new CNode(t, n, bl, tr);
						a = 1;
						n = n->TR;
					}
					else if (s == 0 && n->p.x == NULL && n->p.y == NULL && n->k == true && n->TR != NULL) {// .....................если нет точек, но были, а сейчас они в ветвях
						n = n->TR;
					}
				}


				else if (t.x < (n->tr.x + n->bl.x) / 2 && t.y >(n->tr.y + n->bl.y) / 2) {   // если точка попадает в левый верхний угол
					if (n->p.x != NULL || tochka->p.x != NULL) {       // если там уже есть точка
						if (f == 0) {
							tochka->p.x = n->p.x; tochka->p.y = n->p.y;                            // запоминаем эту точку
							f = 1;
							n->p.x = NULL;
							n->p.y = NULL;
						}
						if (tochka->p.x == (n->tr.x + n->bl.x) / 2 && tochka->p.y == (n->tr.y + n->bl.y) / 2) { // если существующая точка при разбиении попадет на пересечение
							a = 1;
							cout << "ne vstavili tochky" << endl;
						}
						else if (tochka->p.x < (n->tr.x + n->bl.x) / 2 && tochka->p.y >(n->tr.y + n->bl.y) / 2) {  //но там уже есть точка, поэтому переходим в пв квадрат(уменьшаем убласть) и делаем тоже самое для него
							bl = Point(n->bl.x, (n->tr.y + n->bl.y) / 2);
							tr = Point((n->tr.x + n->bl.x) / 2, n->tr.y);
							n->TL = new CNode(null, n, bl, tr);
							n->TL->k = true;
							n = n->TL;  // переход
							s = 1;
						}
						else if (tochka->p.x < (n->tr.x + n->bl.x) / 2 && tochka->p.y < (n->tr.y + n->bl.y) / 2) { //если точка попадает в другой квадрат при разбиении
							bl = Point(n->bl.x, n->bl.y);
							tr = Point((n->tr.x + n->bl.x) / 2, (n->tr.y + n->bl.y) / 2);
							n->BL = new CNode(tochka->p, n, bl, tr);
							tochka->p.x = NULL; tochka->p.y = NULL;
							bl = Point(n->bl.x, (n->tr.y + n->bl.y) / 2);
							tr = Point((n->tr.x + n->bl.x) / 2, n->tr.y);
							n->TL = new CNode(t, n, bl, tr);
							a = 1;
							n = n->TL;
						}
						else if (tochka->p.x > (n->tr.x + n->bl.x) / 2 && tochka->p.y < (n->tr.y + n->bl.y) / 2) {//если точка попадает в другой квадрат при разбиении
							bl = Point((n->tr.x + n->bl.x) / 2, n->bl.y);
							tr = Point(n->tr.x, (n->tr.y + n->bl.y) / 2);
							n->BR = new CNode(tochka->p, n, bl, tr);
							tochka->p.x = NULL; tochka->p.y = NULL;
							bl = Point(n->bl.x, (n->tr.y + n->bl.y) / 2);
							tr = Point((n->tr.x + n->bl.x) / 2, n->tr.y);
							n->TL = new CNode(t, n, bl, tr);
							a = 1;
							n = n->TL;
						}
						else if (tochka->p.x > (n->tr.x + n->bl.x) / 2 && tochka->p.y > (n->tr.y + n->bl.y) / 2) {//если точка попадает в другой квадрат при разбиении
							bl = Point((n->tr.x + n->bl.x) / 2, (n->tr.y + n->bl.y) / 2);
							tr = Point(n->tr.x, n->tr.y);
							n->TR = new CNode(tochka->p, n, bl, tr); //создаем квадрат для исходной точки
							tochka->p.x = NULL; tochka->p.y = NULL;  //перемещаем точку на нижний уровень
							bl = Point(n->bl.x, (n->tr.y + n->bl.y) / 2);
							tr = Point((n->tr.x + n->bl.x) / 2, n->tr.y);
							n->TL = new CNode(t, n, bl, tr);
							a = 1;
							n = n->TL;
						}
					}
					else if (s == 0 && n->p.x == NULL && n->p.y == NULL && n->TL == NULL) {//............если нет точек и никогда не было     // могут ли вообще быть такие ситуации???
						bl = Point(n->bl.x, (n->tr.y + n->bl.y) / 2);
						tr = Point((n->tr.x + n->bl.x) / 2, n->tr.y);
						n->TL = new CNode(t, n, bl, tr);
						a = 1;
						n = n->TL;
					}
					else if (s == 0 && n->p.x == NULL && n->p.y == NULL && n->k == true) {// .....................если нет точек, но были, а сейчас они в ветвях
						n = n->TL;
					}
				}


				else if (t.x < (n->tr.x + n->bl.x) / 2 && t.y < (n->tr.y + n->bl.y) / 2) {   // если точка попадает в левый нижний угол
					if (n->p.x != NULL || tochka->p.x != NULL) {       // если там уже есть точка						
						if (f == 0) {
							tochka->p.x = n->p.x; tochka->p.y = n->p.y;                            // запоминаем эту точку
							f = 1;
							n->p.x = NULL;
							n->p.y = NULL;
						}
						if (tochka->p.x == (n->tr.x + n->bl.x) / 2 && tochka->p.y == (n->tr.y + n->bl.y) / 2) { // если существующая точка при разбиении попадет на пересечение
							a = 1;
							cout << "ne vstavili tochky" << endl;
						}
						else if (tochka->p.x < (n->tr.x + n->bl.x) / 2 && tochka->p.y < (n->tr.y + n->bl.y) / 2) {  //но там уже есть точка, поэтому переходим в пв квадрат(уменьшаем убласть) и делаем тоже самое для него
							bl = Point(n->bl.x, n->bl.y);
							tr = Point((n->tr.x + n->bl.x) / 2, (n->tr.y + n->bl.y) / 2);
							n->BL = new CNode(null, n, bl, tr);
							n->BL->k = true;
							n = n->BL;  // переход
							s = 1;
						}
						else if (tochka->p.x > (n->tr.x + n->bl.x) / 2 && tochka->p.y < (n->tr.y + n->bl.y) / 2) { //если точка попадает в другой квадрат при разбиении
							bl = Point((n->tr.x + n->bl.x) / 2, n->bl.y);
							tr = Point(n->tr.x, (n->tr.y + n->bl.y) / 2);
							n->BR = new CNode(tochka->p, n, bl, tr);
							tochka->p.x = NULL; tochka->p.y = NULL;
							bl = Point(n->bl.x, n->bl.y);
							tr = Point((n->tr.x + n->bl.x) / 2, (n->tr.y + n->bl.y) / 2);
							n->BL = new CNode(t, n, bl, tr);
							a = 1;
							n = n->BL;
						}
						else if (tochka->p.x > (n->tr.x + n->bl.x) / 2 && tochka->p.y > (n->tr.y + n->bl.y) / 2) {//если точка попадает в другой квадрат при разбиении
							bl = Point((n->tr.x + n->bl.x) / 2, (n->tr.y + n->bl.y) / 2);
							tr = Point(n->tr.x, n->tr.y);
							n->TR = new CNode(tochka->p, n, bl, tr);
							tochka->p.x = NULL; tochka->p.y = NULL;
							bl = Point(n->bl.x, n->bl.y);
							tr = Point((n->tr.x + n->bl.x) / 2, (n->tr.y + n->bl.y) / 2);
							n->BL = new CNode(t, n, bl, tr);
							a = 1;
							n = n->BL;
						}
						else if (tochka->p.x < (n->tr.x + n->bl.x) / 2 && tochka->p.y >(n->tr.y + n->bl.y) / 2) {//если точка попадает в другой квадрат при разбиении
							bl = Point(n->bl.x, (n->tr.y + n->bl.y) / 2);
							tr = Point((n->tr.x + n->bl.x) / 2, n->tr.y);
							n->TL = new CNode(tochka->p, n, bl, tr); //создаем квадрат для исходной точки
							tochka->p.x = NULL; tochka->p.y = NULL;  //перемещаем точку на нижний уровень
							bl = Point(n->bl.x, n->bl.y);
							tr = Point((n->tr.x + n->bl.x) / 2, (n->tr.y + n->bl.y) / 2);
							n->BL = new CNode(t, n, bl, tr);
							a = 1;
							n = n->BL;
						}
					}
					else if (s == 0 && n->p.x == NULL && n->p.y == NULL && n->BL == NULL) {//............если нет точек и никогда не было     // могут ли вообще быть такие ситуации???
						bl = Point(n->bl.x, (n->tr.y + n->bl.y) / 2);
						tr = Point((n->tr.x + n->bl.x) / 2, n->tr.y);
						n->BL = new CNode(t, n, bl, tr);
						a = 1;
						n = n->BL;
					}
					else if (s == 0 && n->p.x == NULL && n->p.y == NULL && n->k == true) {// .....................если нет точек, но были, а сейчас они в ветвях
						n = n->BL;
					}
				}

				else if (t.x > (n->tr.x + n->bl.x) / 2 && t.y < (n->tr.y + n->bl.y) / 2) {   // если точка попадает в правый нижний угол
					if (n->p.x != NULL || tochka->p.x != NULL) {       // если там уже есть точка
						if (f == 0) {
							tochka->p.x = n->p.x; tochka->p.y = n->p.y;                            // запоминаем эту точку
							f = 1;
							n->p.x = NULL;
							n->p.y = NULL;
						}
						if (tochka->p.x == (n->tr.x + n->bl.x) / 2 && tochka->p.y == (n->tr.y + n->bl.y) / 2) { // если существующая точка при разбиении попадет на пересечение
							a = 1;
							cout << "ne vstavili tochky" << endl;
						}
						else if (tochka->p.x > (n->tr.x + n->bl.x) / 2 && tochka->p.y < (n->tr.y + n->bl.y) / 2) {  //но там уже есть точка, поэтому переходим в пв квадрат(уменьшаем убласть) и делаем тоже самое для него
							bl = Point((n->tr.x + n->bl.x) / 2, n->bl.y);
							tr = Point(n->tr.x, (n->tr.y + n->bl.y) / 2);
							n->BR = new CNode(null, n, bl, tr);
							n->BR->k = true;
							n = n->BR;  // переход
							s = 1;
						}
						else if (tochka->p.x > (n->tr.x + n->bl.x) / 2 && tochka->p.y > (n->tr.y + n->bl.y) / 2) { //если точка попадает в другой квадрат при разбиении
							bl = Point((n->tr.x + n->bl.x) / 2, (n->tr.y + n->bl.y) / 2);
							tr = Point(n->tr.x, n->tr.y);
							n->TR = new CNode(tochka->p, n, bl, tr);
							tochka->p.x = NULL; tochka->p.y = NULL;
							bl = Point((n->tr.x + n->bl.x) / 2, n->bl.y);
							tr = Point(n->tr.x, (n->tr.y + n->bl.y) / 2);
							n->BR = new CNode(t, n, bl, tr);
							a = 1;
							n = n->BR;
						}
						else if (tochka->p.x < (n->tr.x + n->bl.x) / 2 && tochka->p.y >(n->tr.y + n->bl.y) / 2) {//если точка попадает в другой квадрат при разбиении
							bl = Point(n->bl.x, (n->tr.y + n->bl.y) / 2);
							tr = Point((n->tr.x + n->bl.x) / 2, n->tr.y);
							n->TL = new CNode(tochka->p, n, bl, tr);
							tochka->p.x = NULL; tochka->p.y = NULL;
							bl = Point((n->tr.x + n->bl.x) / 2, n->bl.y);
							tr = Point(n->tr.x, (n->tr.y + n->bl.y) / 2);
							n->BR = new CNode(t, n, bl, tr);
							a = 1;
							n = n->BR;
						}
						else if (tochka->p.x < (n->tr.x + n->bl.x) / 2 && tochka->p.y < (n->tr.y + n->bl.y) / 2) {//если точка попадает в другой квадрат при разбиении
							bl = Point(n->bl.x, n->bl.y);
							tr = Point((n->tr.x + n->bl.x) / 2, (n->tr.y + n->bl.y) / 2);
							n->BL = new CNode(tochka->p, n, bl, tr); //создаем квадрат для исходной точки
							tochka->p.x = NULL; tochka->p.y = NULL;  //перемещаем точку на нижний уровень
							bl = Point((n->tr.x + n->bl.x) / 2, n->bl.y);
							tr = Point(n->tr.x, (n->tr.y + n->bl.y) / 2);
							n->BR = new CNode(t, n, bl, tr);
							a = 1;
							n = n->BR;
						}
					}
					else if (s == 0 && n->p.x == NULL && n->p.y == NULL && n->BR == NULL) {//............если нет точек и никогда не было     // могут ли вообще быть такие ситуации???
						bl = Point((n->tr.x + n->bl.x) / 2, n->bl.y);
						tr = Point(n->tr.x, (n->tr.y + n->bl.y) / 2);
						n->BR = new CNode(t, n, bl, tr);
						a = 1;
						n = n->BR;
					}
					else if (s == 0 && n->p.x == NULL && n->p.y == NULL && n->k == true) {// .....................если нет точек, но были, а сейчас они в ветвях
						n = n->BR;
					}
				}
			}
			if (n->p.x == t.x && n->p.y == t.y) {
				cout << "dobavili tochky (" << t.x << "," << t.y << ")" << endl;
			}
			return 0;
		}
	}
}




int Quad::DeleteNode(Point _t) {
	Point t = _t;  // удаляемая точка
	int a = 0; // 0 если не удалили, 1 удалили точку
	CNode* n;
	n = root;
	if (t.x < root->bl.x || t.x > root->tr.x || t.y > root->tr.y || t.y < root->bl.y) { // если точка выходит за границы 
		cout << "tochka vihodit za oblast'" << endl;
		return -1;
	}
	else if (root->p.x == t.x && root->p.y == t.y) {
		root = NULL;
		cout << "ydalili koren'" << endl;
		return 0;
	}
	else {
		while (a != 1) {
			if (n == NULL) {
				cout << "net tokoy tochki" << endl;
				a = 1;
			}
			if (t.x > (n->tr.x + n->bl.x) / 2 && t.y > (n->tr.y + n->bl.y) / 2) {

				if (n->TR->p.x == t.x && n->TR->p.y == t.y) {
					a = 1;
					n->TR = NULL;
				}
				else {
					n = n->TR;
				}
			}
			else if (t.x < (n->tr.x + n->bl.x) / 2 && t.y >(n->tr.y + n->bl.y) / 2) {
				n = n->TL;
				if (n->p.x == t.x && n->p.y == t.y) {
					a = 1;
					n->par->TL = NULL;
				}
			}
			else if (t.x < (n->tr.x - n->bl.x) / 2 && t.y < (n->tr.y - n->bl.y) / 2) {
				if (n->BL->p.x == t.x && n->BL->p.y == t.y) {
					a = 1;
					n->BL = NULL;
				}
				else {
					n = n->BL;
				}
			}
			else if (t.x > (n->tr.x + n->bl.x) / 2 && t.y < (n->tr.y + n->bl.y) / 2) {
				if (n->BR->p.x == t.x && n->BR->p.y == t.y) {
					a = 1;
					n->BR = NULL;
				}
				else {
					n = n->BR;
				}
			}
		}
		cout << "ydalili tochky (" << t.x << "," << t.y << ")" << endl;
		return 0;
	}
}

CNode* Quad::Find(Point _t) {
	Point t = _t;  // вставляемая точка
	int a = 0; // 0 если вставили, 1 вставили точку
	CNode* n;
	n = root;
	bool l;
	if ((root->bl.x > t.x && t.x > root->tr.x) || (root->bl.y > t.y && t.y > root->tr.y)) { // если точка выходит за границы 
		l = false;
		return NULL;
	}
	else if (root->p.x == t.x && root->p.y == t.y) {
		a = 1;
		l = true;
		return root;
	}
	else {
		while (a != 1) {
			if (t.x > (n->tr.x - n->bl.x) / 2 && t.y > (n->tr.y - n->bl.y) / 2) {
				if (n->TR == NULL) {
					a = 1;
					l = false;
				}
				else {
					if (n->TR->p.x == t.x && n->TR->p.y == t.y) {
						a = 1;
						l = true;
						n = n->TR;
					}
					else {
						n = n->TR;
					}
				}
			}
			else if (t.x < (n->tr.x - n->bl.x) / 2 && t.y >(n->tr.y - n->bl.y) / 2) {
				if (n->TL == NULL) {
					a = 1;
					l = false;
				}
				else {
					if (n->TL->p.x == t.x && n->TL->p.y == t.y) {
						a = 1;
						l = true;
						n = n->TL;
					}
					else {
						n = n->TL;
					}
				}
			}
			else if (t.x < (n->tr.x - n->bl.x) / 2 && t.y < (n->tr.y - n->bl.y) / 2) {
				if (n->BL == NULL) {
					a = 1;
					l = false;
				}
				else {
					if (n->BL->p.x == t.x && n->BL->p.y == t.y) {
						a = 1;
						l = true;
						n = n->BL;
					}
					else {
						n = n->BL;
					}
				}
			}
			else if (t.x > (n->tr.x - n->bl.x) / 2 && t.y < (n->tr.y - n->bl.y) / 2) {
				if (n->BR == NULL) {
					a = 1;
					l = false;
				}
				else {
					if (n->BR->p.x == t.x && n->BR->p.y == t.y) {
						a = 1;
						l = true;
						n = n->BR;
					}
					else {
						n = n->BR;
					}
				}
			}
		}
		cout << "esti li tochka (" << t.x << "," << t.y << ") v dereve:" << endl;
		if (l == true) {
			cout << "true" << endl;
		}
		else {
			cout << "false" << endl;
		}
		if (l == false) {
			return NULL;
		}
		else {
			return n;
		}
	}
}

int Quad::Quantity() {
	int sum = 0;
	queue<CNode*> Queue;
	Queue.push(root);
	cout << "vse tochki v dereve:" << endl;
	while (!Queue.empty()) {
		CNode* n = Queue.front();
		Queue.pop();
		if (n->p.x == NULL && n->p.y == NULL) {
		}
		else {
			sum++;
			cout << "(" << n->p.x << "," << n->p.y << ")" << endl;
		}
		if (n->TR != NULL) {
			Queue.push(n->TR);
		}
		if (n->TL != NULL) {
			Queue.push(n->TL);
		}
		if (n->BL != NULL) {
			Queue.push(n->BL);
		}
		if (n->BR != NULL) {
			Queue.push(n->BR);
		}
	}
	return sum;
}

void Quad::Quantity1(CNode* p) {
	queue<CNode*> Queue;
	Queue.push(p);
	while (!Queue.empty()) {
		CNode* n = Queue.front();
		Queue.pop();
		if (n->p.x == NULL && n->p.y == NULL) {
		}
		else {
			cout << "(" << n->p.x << "," << n->p.y << ")" << endl;
		}
		if (n->TR != NULL) {
			Queue.push(n->TR);
		}
		if (n->TL != NULL) {
			Queue.push(n->TL);
		}
		if (n->BL != NULL) {
			Queue.push(n->BL);
		}
		if (n->BR != NULL) {
			Queue.push(n->BR);
		}
	}
}

void Quad::Vicinity(Point p) {
	CNode* n = Find(p);
	cout << "V okrestnosti tochki (" << p.x << "," << p.y << "):" << endl;
	if (n == NULL) {
	}
	else {
		if (n->par->TR != n && n->par->TR != NULL) {
			if (n->par->TR->p.x == NULL && n->par->TR->p.y == NULL) {
				Quantity1(n->par->TR);
			}
			else {
				cout << "(" << n->par->TR->p.x << "," << n->par->TR->p.y << ")" << endl;
			}
		}
		if (n->par->TL != n && n->par->TL != NULL) {
			if (n->par->TL->p.x == NULL && n->par->TL->p.y == NULL) {
				Quantity1(n->par->TL);
			}
			else {
				cout << "(" << n->par->TL->p.x << "," << n->par->TL->p.y << ")" << endl;
			}
		}
		if (n->par->BL != n && n->par->BL != NULL) {
			if (n->par->BL->p.x == NULL && n->par->BL->p.y == NULL) {
				Quantity1(n->par->BL);
			}
			else {
				cout << "(" << n->par->BL->p.x << "," << n->par->BL->p.y << ")" << endl;
			}
		}
		if (n->par->BR != n && n->par->BR != NULL) {
			if (n->par->BR->p.x == NULL && n->par->BR->p.y == NULL) {
				Quantity1(n->par->BR);
			}
			else {
				cout << "(" << n->par->BR->p.x << "," << n->par->BR->p.y << ")" << endl;
			}
		}
	}
}