#include <iostream> 
#include <cmath> 
#include <math.h>
#include <stdio.h>
#pragma once
void Autotest();


class Point {
public:
    double x;
    double y;
    Point(double _x, double _y) {
        x = _x;
        y = _y;
    }
    Point() {
        x = NULL;
        y = NULL;
    }
    friend class Quad;
};

class CNode {
public:
    bool k;
    Point p;
    Point bl, tr;
    CNode* par, * TL, * TR, * BL, * BR;
    CNode() {
        k = false;
        p.x = NULL;
        p.y = NULL;
        bl.x = NULL;
        bl.y = NULL;
        par = TL = TR = BL = BR = NULL;
    }
    CNode(Point p_, CNode* par_, Point _bl, Point _tr) {
        par = par_; p.x = p_.x; p.y = p_.y; TL = TR = BL = BR = NULL;
        bl.x = _bl.x;
        bl.y = _bl.y;
        tr.x = _tr.x;
        tr.y = _tr.y;
        if (p.x != NULL && p.y != NULL) {
            k = true;
        }
        else { k = false; }
    }
    friend class Quad;
};

class Quad {
    CNode* root = new CNode();
public:
    Quad() { root = NULL; }
    Quad(Point tr_) {
        root->bl.x = 0;
        root->bl.y = 0;
        root->tr.x = tr_.x;
        root->tr.y = tr_.y;
    }
    ~Quad() { Clean(); }
    int Empty() { return root == NULL; }
    void Clean() { while (Delete(root) != 0); }
    int Delete(CNode* n) { return 0; }
    int Add(Point t);
    int DeleteNode(Point t);
    CNode* Find(Point t);
    int Quantity();
    void Quantity1(CNode* p);
    void Vicinity(Point p);
};

