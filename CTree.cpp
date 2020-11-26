#include "CTree.h"


int Quad::Add(Point _t) {
	Point t = _t;  // вставляемая точка
	Point bl; //левый нижний угол
	Point tr; // правый вегхний
	int a = 0; // 0 если вставили, 1 вставили точку
	CNode* n; 
	CNode* tochka;  // точка котрая уже есть в квадрате
	// Игнорировать объекты, не принадлежащие дереву
	//if 

	if (root->p.x == NULL && root->k==false) {  // вставляем первую точку
		root->p.x = t.x; 
		root->p.y = t.y;
		root->k = true;
	}
	else {
		
		//for (n = root; n != NULL;) {
		while(a!=1){       // пока не втавим
			if (n->p.x == t.x && n->p.y == t.y) { a = 1; return -1; } // если уже есть эта точка
			tochka->p.x = n->p.x; tochka->p.y = n->p.y;           //запоминаем точку которая уже есть в квадрате, потому что н меняется
			if (t.x > (n->tr.x - n->bl.x) / 2 && t.y > (n->tr.y - n->bl.y) / 2) {   // если точка попадает в правый верхний угол
				if (tochka->p.x > (n->tr.x + n->bl.x) / 2 && tochka->p.y > (n->tr.y + n->bl.y) / 2) {  //но там уже есть точка, поэтому переходим в пв квадрат(уменьшаем убласть) и делаем тоже самое для него
					bl = Point((n->tr.x + n->bl.x) / 2, (n->tr.y + n->bl.y) / 2);
					tr = Point(n->tr.x, n->tr.y);
					n->TR = new CNode(bl,tr); 
					n = n->TR;  // переход
					return 0;
				}
				if (tochka->p.x < (n->tr.x + n->bl.x) / 2 && tochka->p.y > (n->tr.y + n->bl.y) / 2) { //если точка попадает в другой квадрат при разбиении
					bl = Point(n->bl.x, (n->tr.y + n->bl.y) / 2);
					tr = Point((n->tr.x + n->bl.x) / 2, n->tr.y);
					n->BR = new CNode(tochka->p, n, bl, tr); 
					tochka->p.x = NULL; tochka->p.y = NULL;
					bl = Point((n->tr.x + n->bl.x) / 2, (n->tr.y + n->bl.y) / 2);
					tr = Point(n->tr.x, n->tr.y);
					n->TR = new CNode(t, n, bl, tr);
					a = 1;
				}
				if (tochka->p.x < (n->tr.x + n->bl.x) / 2 && n->p.y > (tochka->tr.y + n->bl.y) / 2) {//если точка попадает в другой квадрат при разбиении
					bl = Point(n->bl.x, n->bl.y);
					tr = Point((n->tr.x + n->bl.x) / 2, (n->tr.y + n->bl.y) / 2);
					n->BR = new CNode(tochka->p, n, bl, tr);
					tochka->p.x = NULL; tochka->p.y = NULL;
					bl = Point((n->tr.x + n->bl.x) / 2, (n->tr.y + n->bl.y) / 2);
					tr = Point(n->tr.x, n->tr.y);
					n->TR = new CNode(t, n, bl, tr);
					a = 1;
				}
				if (tochka->p.x > (n->tr.x + n->bl.x) / 2 && tochka->p.y < (n->tr.y + n->bl.y) / 2) {//если точка попадает в другой квадрат при разбиении
					bl = Point((n->tr.x + n->bl.x) / 2, n->bl.y);
					tr = Point(n->tr.x, (n->tr.y + n->bl.y) / 2);
					n->BR = new CNode(tochka->p, n,bl,tr); //создаем квадрат для исходной точки
					tochka->p.x = NULL; tochka->p.y = NULL;  //перемещаем точку на нижний уровень
					bl = Point((n->tr.x + n->bl.x) / 2, (n->tr.y + n->bl.y) / 2);
					tr = Point(n->tr.x, n->tr.y);
					n->TR = new CNode(t, n,bl,tr);
					a = 1;
				}
				if (n->p.x == NULL && n->p.y == NULL && n->k == false) {//............если нет точек и никогда не было     // могут ли вообще быть такие ситуации???
					bl = Point((n->tr.x - n->bl.x) / 2, (n->tr.y - n->bl.y) / 2);
					tr = Point(n->tr.x, n->tr.y);
					n->TR = new CNode(t, n, bl, tr);
					a = 1;
				}
				if (n->p.x == NULL && n->p.y == NULL && n->k == true) {// .....................если нет точек, но были, а сейчас они в ветвях
					bl = Point((n->tr.x - n->bl.x) / 2, (n->tr.y - n->bl.y) / 2);
					tr = Point(n->tr.x, n->tr.y);
					n->TR = new CNode(t, n, bl, tr);
					n = n->TR;
					a = 0;
				}
			}






















			if (t.x < (n->tr.x - n->bl.x) / 2 && t.y > (n->tr.y - n->bl.y) / 2) {
				if (n->p.x < (n->tr.x - n->bl.x) / 2 && n->p.y > (n->tr.y - n->bl.y) / 2) {
					bl = Point(n->bl.x, (n->tr.y - n->bl.y) / 2);
					tr = Point((n->tr.x - n->bl.x) / 2, n->tr.y);
					n->TL = new CNode(bl, tr);
					n = n->TL;
					//n->TR = new CNode(t, n); 
					return 0;
				}
				if (n->p.x < (n->tr.x - n->bl.x) / 2 && n->p.y < (n->tr.y - n->bl.y) / 2) {
					bl = Point(n->bl.x, n->bl.y);
					tr = Point((n->tr.x - n->bl.x) / 2, (n->tr.y - n->bl.y) / 2);
					n->BL = new CNode(n->p, n, bl, tr);
					n->p.x = NULL; n->p.y = NULL;
					bl = Point((n->tr.x - n->bl.x) / 2, (n->tr.y - n->bl.y) / 2);
					tr = Point(n->tr.x, n->tr.y);
					n->TL = new CNode(t, n, bl, tr);
					a = 1;
				}
				if (n->p.x < (n->tr.x - n->bl.x) / 2 && n->p.y >(n->tr.y - n->bl.y) / 2) {
					bl = Point(n->bl.x, n->bl.y);
					tr = Point((n->tr.x - n->bl.x) / 2, (n->tr.y - n->bl.y) / 2);
					n->BR = new CNode(n->p, n, bl, tr);
					n->p.x = NULL; n->p.y = NULL;
					bl = Point((n->tr.x - n->bl.x) / 2, (n->tr.y - n->bl.y) / 2);
					tr = Point(n->tr.x, n->tr.y);
					n->TR = new CNode(t, n, bl, tr);
					a = 1;
				}
				if (n->p.x > (n->tr.x - n->bl.x) / 2 && n->p.y < (n->tr.y - n->bl.y) / 2) {
					bl = Point((n->tr.x - n->bl.x) / 2, n->bl.y);
					tr = Point(n->tr.x, (n->tr.y - n->bl.y) / 2);
					n->BR = new CNode(n->p, n, bl, tr);
					n->p.x = NULL; n->p.y = NULL;
					bl = Point((n->tr.x - n->bl.x) / 2, (n->tr.y - n->bl.y) / 2);
					tr = Point(n->tr.x, n->tr.y);
					n->TR = new CNode(t, n, bl, tr);
					a = 1;
				}
				if (n->p.x == NULL && n->p.y == NULL) {
					bl = Point((n->tr.x - n->bl.x) / 2, (n->tr.y - n->bl.y) / 2);
					tr = Point(n->tr.x, n->tr.y);
					n->TR = new CNode(t, n, bl, tr);
					a = 1;
				}

		}
	}
	

}