#include "CTree.h"
#include <fstream>
#include <iostream>
//#include <cmath> 
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
	CNode* tochka = new CNode(null, nul ,bl, tr);;  // точка котрая уже есть в квадрате
	n = root;
	int f = 0, s = 0;
	cout << "(" << t.x << "," << t.y << "):" << endl;
	// Игнорировать объекты, не принадлежащие дереву
	if ((root->bl.x > t.x && t.x > root->tr.x) || (root->bl.y > t.y && t.y > root->tr.y)) { // если точка выходит за границы 
		return -1;
	}
	else {
		if (root->p.x == NULL && root->k == false) {  // вставляем первую точку
			root->p.x = t.x;
			root->p.y = t.y;
			root->k = true;
			return 0;
		}
		else {
			while (a != 1) {       // пока не вcтавим
				if (n->p.x == t.x && n->p.y == t.y) { a = 1; cout << "takay tochka yze est'" << endl; return -1; } // если уже есть эта точка
				else if (t.x > (n->tr.x + n->bl.x) / 2 && t.y > (n->tr.y + n->bl.y) / 2) {   // если точка попадает в правый верхний угол
					if (n->p.x != NULL || tochka->p.x != NULL) {       // если там уже есть точка
						if (f == 0) {
							tochka->p.x = n->p.x; tochka->p.y = n->p.y;                            // запоминаем эту точку
							f = 1;
							n->p.x = NULL;
							n->p.y = NULL;
						}
						if (tochka->p.x > (n->tr.x + n->bl.x) / 2 && tochka->p.y > (n->tr.y + n->bl.y) / 2) {  //точка попадает туда же
							bl = Point((n->tr.x + n->bl.x) / 2, (n->tr.y + n->bl.y) / 2);
							tr = Point(n->tr.x, n->tr.y);
							n->TR = new CNode(null, n, bl, tr);
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
						}
					}
					else if (s == 0 && n->p.x == NULL && n->p.y == NULL && n->k == false) {//............если нет точек и никогда не было     // могут ли вообще быть такие ситуации???
						bl = Point((n->tr.x + n->bl.x) / 2, (n->tr.y + n->bl.y) / 2);
						tr = Point(n->tr.x, n->tr.y);
						n->TR = new CNode(t, n, bl, tr);
						a = 1;
					}
					else if (s == 0 && n->p.x == NULL && n->p.y == NULL && n->k == true) {// .....................если нет точек, но были, а сейчас они в ветвях
						bl = Point((n->tr.x + n->bl.x) / 2, (n->tr.y + n->bl.y) / 2);
						tr = Point(n->tr.x, n->tr.y);
						if (n->TR == NULL) {
							n->TR = new CNode(null, n, bl, tr);
							n = n->TR;
						}
						else {
							n = n->TR;
						}
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
						if (tochka->p.x < (n->tr.x + n->bl.x) / 2 && tochka->p.y >(n->tr.y + n->bl.y) / 2) {  //но там уже есть точка, поэтому переходим в пв квадрат(уменьшаем убласть) и делаем тоже самое для него
							bl = Point(n->bl.x, (n->tr.y + n->bl.y) / 2);
							tr = Point((n->tr.x + n->bl.x) / 2, n->tr.y);
							n->TL = new CNode(null, n, bl, tr);
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
						}
					}
					else if (s == 0 && n->p.x == NULL && n->p.y == NULL && n->k == false) {//............если нет точек и никогда не было     // могут ли вообще быть такие ситуации???
						bl = Point(n->bl.x, (n->tr.y + n->bl.y) / 2);
						tr = Point((n->tr.x + n->bl.x) / 2, n->tr.y);
						n->TL = new CNode(t, n, bl, tr);
						a = 1;
					}
					else if (s == 0 && n->p.x == NULL && n->p.y == NULL && n->k == true) {// .....................если нет точек, но были, а сейчас они в ветвях
						bl = Point(n->bl.x, (n->tr.y + n->bl.y) / 2);
						tr = Point((n->tr.x + n->bl.x) / 2, n->tr.y);
						if (n->TL == NULL) {
							n->TL = new CNode(null, n, bl, tr);
							n = n->TL;
						}
						else {
							n = n->TL;
						}
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
						if (tochka->p.x < (n->tr.x + n->bl.x) / 2 && tochka->p.y < (n->tr.y + n->bl.y) / 2) {  //но там уже есть точка, поэтому переходим в пв квадрат(уменьшаем убласть) и делаем тоже самое для него
							bl = Point(n->bl.x, n->bl.y);
							tr = Point((n->tr.x + n->bl.x) / 2, (n->tr.y + n->bl.y) / 2);
							n->BL = new CNode(null, n, bl, tr);
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
						}
					}
					else if (s == 0 && n->p.x == NULL && n->p.y == NULL && n->k == false) {//............если нет точек и никогда не было     // могут ли вообще быть такие ситуации???
						bl = Point(n->bl.x, (n->tr.y + n->bl.y) / 2);
						tr = Point((n->tr.x + n->bl.x) / 2, n->tr.y);
						n->BL = new CNode(t, n, bl, tr);
						a = 1;
					}
					else if (s == 0 && n->p.x == NULL && n->p.y == NULL && n->k == true) {// .....................если нет точек, но были, а сейчас они в ветвях
						bl = Point(n->bl.x, n->bl.y);
						tr = Point((n->tr.x + n->bl.x) / 2, (n->tr.y + n->bl.y) / 2);
						if (n->BL == NULL) {
							n->BL = new CNode(null, n, bl, tr);
							n = n->BL;
						}
						else {
							n = n->BL;
						}
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
						if (tochka->p.x > (n->tr.x + n->bl.x) / 2 && tochka->p.y < (n->tr.y + n->bl.y) / 2) {  //но там уже есть точка, поэтому переходим в пв квадрат(уменьшаем убласть) и делаем тоже самое для него
							bl = Point((n->tr.x + n->bl.x) / 2, n->bl.y);
							tr = Point(n->tr.x, (n->tr.y + n->bl.y) / 2);
							n->BR = new CNode(null, n, bl, tr);
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
						}
					}
					else if (s == 0 && n->p.x == NULL && n->p.y == NULL && n->k == false) {//............если нет точек и никогда не было     // могут ли вообще быть такие ситуации???
						bl = Point((n->tr.x + n->bl.x) / 2, n->bl.y);
						tr = Point(n->tr.x, (n->tr.y + n->bl.y) / 2);
						n->BR = new CNode(t, n, bl, tr);
						a = 1;
					}
					else if (s == 0 && n->p.x == NULL && n->p.y == NULL && n->k == true) {// .....................если нет точек, но были, а сейчас они в ветвях
						bl = Point((n->tr.x + n->bl.x) / 2, n->bl.y);
						tr = Point(n->tr.x, (n->tr.y + n->bl.y) / 2);
						if (n->BR == NULL) {
							n->BR = new CNode(null, n, bl, tr);
							n = n->BR;
						}
						else {
							n = n->BR;
						}
					}
				}
			}
			return 0;
		}
	}
}




int Quad::DeleteNode(Point _t) {
	Point t = _t;  // вставляемая точка
	//Point bl; //левый нижний угол
	//Point tr; // правый вегхний
	int a = 0; // 0 если вставили, 1 вставили точку
	CNode* n;
	//CNode* tochka;  // точка котрая уже есть в квадрате
	n = root;
	// Игнорировать объекты, не принадлежащие дереву
	if ((root->bl.x > t.x && t.x  > root->tr.x) || (root->bl.y > t.y && t.y > root->tr.y)) { // если точка выходит за границы 
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
			//вершину еще проверить может она единственная
			//if (n->p.x == t.x && n->p.y == t.y) { delete n; a = 1; return -1; } // если уже есть эта точка
			//tochka->p.x = n->p.x; tochka->p.y = n->p.y;           //запоминаем точку которая уже есть в квадрате, потому что н меняется
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
	Point t = _t;  // вставляемая точка
	int a = 0; // 0 если вставили, 1 вставили точку
	CNode* n;
	n = root;
	bool l;
	if ((root->bl.x > t.x && t.x > root->tr.x) || (root->bl.y > t.y && t.y > root->tr.y)) { // если точка выходит за границы 
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