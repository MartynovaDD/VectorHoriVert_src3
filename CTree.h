#include <iostream> 
#include <cmath> 
#include <math.h>
#include <stdio.h>
#pragma once

class Point {
public:
    int x;
    int y;
    Point(int _x, int _y) {
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
    bool k;
    Point p;
    Point bl, tr;
    CNode* par, * TL, * TR, * BL, * BR;
    CNode() {
        k = false;
        bl.x = NULL;
        bl.y = NULL;
        par = TL = TR = BL = BR = NULL;
    }
    /*CNode(Point _bl, Point _tr) {          //????????????????????????????
        bl.x = _bl.x;
        bl.y = _bl.y; 
        tr.x = _tr.x;
        tr.y = _tr.y;
        par = TL = TR = BL = BR = NULL;
        k = false;  // нет точки
    }*/
    CNode(Point p_, CNode* par_, Point _bl, Point _tr) {
        par = par_; p.x = p_.x; p.y = p_.y; TL = TR = BL = BR = NULL;
        bl.x = _bl.x;
        bl.y = _bl.y; 
        tr.x = _tr.x;
        tr.y = _tr.y;
        if(p.x!=NULL){ k = true; }
        else { k = false; }
        //k = true;
    }
    friend class Quad;
};

class Quad {
    CNode* root = new CNode();//указатель на корень дерева
public:
    Quad() { root = NULL; }
    Quad(Point bl_, Point tr_) {   //границы исходного квадрата
        root->bl.x = bl_.x;
        root->bl.y = bl_.y;
        root->tr.x = tr_.x;
        root->tr.y = tr_.y;
    }
    ~Quad() { Clean(); }
    int Empty() { return root == NULL; }
    void Clean() { while (Delete(root) != 0); }
    int Delete(CNode* n) { return 0; }
    int Add(Point t);
    int DeleteNode(Point t);
    bool Find(Point t);
    //int Quantity(Point bl, Point tr);
};

