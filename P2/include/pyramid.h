//**********************************************************************
// P1 - pyramid.h
//
// Header file for Pyramid class
//
// Antonio Rafael Verdejo Garcia 2016
//
// GPL-3.0
//**********************************************************************

#ifndef _PYRAMID_H
#define _PYRAMID_H

#include "model.h"

using namespace std;

// Class Pyramid
//
// Define un objeto 3D con forma piramidal a partir de 3 parámetros:
// * radio (distancia entre una esquina y el centro proyectado en base
// * altura (distancia desde la base hasta el vértice)
// * número de caras (a partir de 3)
// Por tanto, una pirámide de número de caras muy alto puede equivaler
//   a un cono, puesto que su base parecerá un círculo
class Pyramid: public Model{
protected:
	float height, radius;
	int faces;
public:
	Pyramid(float height = 100.0f, float radius = 0.0f, int faces = 3);
};

#endif
