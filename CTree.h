#include <iostream> 
#include <cmath> 
#include <math.h>
#include <stdio.h>
#pragma once

class Point
{
    int x;
    int y;
    Point(int _x, int _y)
    {
        x = _x;
        y = _y;
    }
    Point()
    {
        x = NULL;
        y = NULL;
    }
    friend class Quad;
};

class CNode {
    bool k;
    Point p;
    Point bl, tr;
    CNode *par, * TL, * TR, * BL, * BR;
    CNode(Point _bl,Point _tr) {
        bl = _bl; tr = _tr;
        par=TL=TR=BL=BR=NULL;
        k = false;  // нет точки
    }
    CNode(Point p_, CNode* par_,Point _bl,Point _tr) {
        par = par_; p = p_; TL = TR = BL = BR = NULL;
        bl = _bl; tr = _tr;
        k = true;
    }
    friend class Quad;
};

class Quad {
    CNode* root;// корень дерева 
    
    //Point bl, tr;
public:
    //Quad() { root = NULL; }
    Quad(Point bl_, Point tr_) {
        root->bl = bl_; root->tr = tr_;
    }
    ~Quad() { Clean(); }
    int Empty() { return root == NULL; }
    void Clean() { while (Delete(root) == 0); }
    int Delete(CNode* n) { return 0; }
    int Add(Point t);
};

