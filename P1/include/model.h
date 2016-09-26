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
#include <GL/gl.h>
#include "vertex.h"
#include "aux_definitions.h"

using namespace std;

class Model{
protected:
	Mesh *mesh;
	Tuple3n* alternate(bool alternate_A);
public:
	//~ virtual Model() = 0;
	~Model();
	virtual void draw(_render_mode mode, Color3r color1,
		Color3r color2 = NULL, int width = 0);
	void make_triangles(int m, int n, int ver_ind, int tri_ind);
};

#endif
