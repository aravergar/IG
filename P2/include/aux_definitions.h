//**********************************************************************
// P1 - model.h
//
// Useful definitions and structures
//
// Antonio Rafael Verdejo Garcia 2016
//
// GPL-3.0
//**********************************************************************

#ifndef _AUX_DEFINTIONS_H
#define _AUX_DEFINTIONS_H

#include <GL/gl.h>

#define PI 3.141592653589793

// Modos de renderizado
enum _render_mode {VERTICES, EDGES, SOLID, CHECKERED};

// Tipos para definir coordenadas, índices
//   y tablas de vértices y triángulos, etc.
typedef GLfloat Real;
typedef GLuint Natural;
const unsigned int X = 0, Y = 1, Z = 2;
const unsigned int _0 = 0, _1 = 1, _2 = 2;
const unsigned int r = 0, g = 1, b = 2;
//~ const unsigned int X, x, _0, r, Y, y, _1, g, Z, z, _2, b;
//~ X = x = _0 = r = 0;
//~ Y = y = _1 = g = 1;
//~ Z = z = _2 = b = 2;
typedef Real Tuple3r[3];
typedef Real Color3r[3];
typedef Natural Tuple3n[3];
typedef Natural Color3n[3];

struct Mesh{
	Natural num_ver;
	Natural num_tri;
	Tuple3r *vertices;
	Tuple3n *triangles;
};

//~ using colorf = Tuple3r;
//~ using colorn = Tuple3n;


#endif
