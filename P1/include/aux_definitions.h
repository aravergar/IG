#ifndef _AUX_DEFINTIONS_H
#define _AUX_DEFINTIONS_H

#include <GL/gl.h>

#define PI 3.141592653589793

// Modos de renderizado
typedef enum _render_mode {VERTICES, EDGES, SOLID, CHECKERED};

// Tipos para definir coordenadas, índices
//   y tablas de vértices y triángulos, etc.
typedef GLfloat Real;
typedef GLuint Natural;
const unsigned int X=x=_0=r=0, Y=y=_1=g=1, Z=z=_2=g=2;
typedef Real Tuple3r[3];
typedef Natural Tuple3n[3];

struct Mesh{
	Natural num_ver;
	Natural num_tri;
	Tuple3r *vertices;
	Tuple3n *triangles;
};

using colorf = Tuple3r;
using colorn = Tuple3n;


#endif
