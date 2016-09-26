//**********************************************************************
// P1 - cube.h
//
// Header file for Cube class
//
// Antonio Rafael Verdejo Garcia 2016
//
// GPL-3.0
//**********************************************************************

#ifndef _CUBE_H
#define _CUBE_H

#include "prism.h"

using namespace std;

// Class Cube
//
// Define un objeto 3D con forma cúbica a partir de 1 parámetro:
// * longitud de la arista
class Cube: public Prism{
protected:
public:
	//~ Pyramid(float height = 100.0f, float radius = 0.0f, int faces = 3);
	Cube(float edge_length);
};

#endif
