//**********************************************************************
// P2 - ply_model.h
//
// Header file for PlyModel class
//
// Antonio Rafael Verdejo Garcia 2016
//
// GPL-3.0
//**********************************************************************

#ifndef _PLYMODEL_H
#define _PLYMODEL_H

#include "model.h"
#include "file_ply_stl.h"

using namespace std;

// Class PlyModel
//
// Define un objeto 3D formado a partir de un fichero PLY pasado
//   cuyo nombre es pasado como parámetro:
// * file (nombre del fichero PLY)
class PlyModel: public Model{
protected:
	void arrange(vector<float> ver, vector<int> tri);
public:
	PlyModel(char *file);
};

#endif
