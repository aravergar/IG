#ifndef _MODEL_H
#define _MODEL_H

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
public:
	//~ virtual Model() = 0;
	virtual ~Model() = 0;
	virtual draw(_render_mode mode, colorf color1,
		colorf color2 = NULL, int width = 0) = 0;
};

#endif
