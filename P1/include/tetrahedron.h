//**********************************************************************
// P1 - tetrahedron.h
//
// Header file for Tetrahedron class
//
// Antonio Rafael Verdejo Garcia 2016
//
// GPL-3.0
//**********************************************************************

#ifndef _TETRAHEDRON_H
#define _TETRAHEDRON_H

#include "pyramid.h"

using namespace std;

// Class Tetrahedron
//
// Define un objeto 3D con forma tetraédrica a partir de 1 parámetro:
// * longitud de la arista
class Tetrahedron: public Pyramid{
protected:
public:
	//~ Pyramid(float height = 100.0f, float radius = 0.0f, int faces = 3);
	Tetrahedron(float edge_length);
};

#endif
