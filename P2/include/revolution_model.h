//**********************************************************************
// P2 - revolution_model.h
//
// Header file for RevolutionModel class
//
// Antonio Rafael Verdejo Garcia 2016
//
// GPL-3.0
//**********************************************************************

#ifndef _REVOLUTION_MODEL_H
#define _REVOLUTION_MODEL_H

#include "model.h"
#include "file_ply_stl.h"

using namespace std;

// Class RevolutionModel
//
// Define un objeto 3D formado a partir de un perfil
//   pasado como parámetro:
// * countour (perfil) ó
// * file (nombre del fichero PLY que contiene el perfil)

enum Topology {HOLLOW, CONCAVE, CONVEX, CLOSED};

class RevolutionModel: public Model{
protected:
	//~ void arrange(vector<float> ver, vector<int> tri);
	int test_plane(Tuple3r *countour);
	void change_plane(Tuple3r *countour, int num_ver, int pre_plane, int plane);
	Topology test_topology(Tuple3r* countour, int num_ver, int plane, int axis, int *ind_axis);
public:
	RevolutionModel(Tuple3r *countour, int num_ver, int plane, int revolutions, int axis);
	RevolutionModel(char *file, int plane, int revolutions, int axis);
};

#endif
