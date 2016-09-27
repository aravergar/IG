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

using namespace std;

// Class RevolutionModel
//
// Define un objeto 3D formado a partir de un perfil
//   pasado como parámetro:
// * countour (perfil) ó
// * file (nombre del fichero PLY que contiene el perfil)

class RevolutionModel: public Model{
protected:
	//~ void arrange(vector<float> ver, vector<int> tri);
public:
	RevolutionModel(Tuple3r *countour);
	RevolutionModel(char *file);
};

#endif
