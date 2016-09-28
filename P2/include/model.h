//**********************************************************************
// P1 - model.h
//
// Header file for Model class
//
// Antonio Rafael Verdejo Garcia 2016
//
// GPL-3.0
//**********************************************************************

#ifndef _MODEL_H
#define _MODEL_H

#include <cstdlib>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <iostream>
#include <GL/gl.h>
#include "aux_definitions.h"

using namespace std;

class Model{
protected:
	Mesh *mesh;
	Tuple3n* alternate(bool alternate_A);
public:
	~Model();
	virtual void draw(_render_mode mode, Color3r color1,
		Color3r color2 = NULL, int width = 0);
	void make_triangles_grid(int m, int n, int ver_ind, int tri_ind);
	void make_triangles_fan(int m, int n, int ver_ind, int tri_ind, int center_ind, bool ccw);
	void make_triangles_hollow_body(int m, int n, int ver_ind, int tri_ind);
	void revolution(Tuple3r* vertices, Tuple3r* countour, uint count_num, uint revs, uint init = 0, int plane = 0, int axis = 0);
	void test();
};

#endif
