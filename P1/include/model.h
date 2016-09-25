#ifndef _MODEL_H
#define _MODEL_H

#include <cstdlib>
#include <GL/gl.h>
#include "vertex.h"
#include "aux_definitions.h"

using namespace std;

//~ struct mesh_struct{
	//~ vector<_vertex3f> vertices;
	//~ vector<_vertex3i> triangles;
//~ };


class Model{
protected:
	Mesh *mesh;
	Tuple3n* alternate(bool alternate_A);
public:
	//~ virtual Model() = 0;
	~Model();
	virtual void draw(_render_mode mode, Color3r color1,
		Color3r color2 = NULL, int width = 0);
};

#endif
