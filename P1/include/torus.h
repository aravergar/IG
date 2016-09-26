//**********************************************************************
// P1 - torus.h
//
// Header file for Torus class
//
// Antonio Rafael Verdejo Garcia 2016
//
// GPL-3.0
//**********************************************************************

#ifndef _TORUS_H
#define _TORUS_H

#include "model.h"

using namespace std;

// Class Torus
//
// Define un objeto 3D con forma de toro a partir de 4 parámetros:
// * radio mayor (distancia entre el centro y el centro del tubo)
// * radio menor (radio del tubo)
// * divisiones verticales (numero de divisiones vert., >3)
// * divisiones horizontales (numero de div. hor., >3)
// Por tanto, un prisma de número de caras muy alto puede equivaler
//   a un cilindro, puesto que su base parecerá un círculo

class Torus: public Model{
protected:
	float radius_may, radius_min;
	uint div_ver, div_hor;
public:
	Torus(float radius_may = 100.0f, float radius_min = 30.0f,
		uint div_ver = 6, uint div_hor = 6);
};

//~ class Torus: public Model{
//~ protected:
	//~ float height, radius;
	//~ int faces;
//~ public:
	//~ Torus(float height = 80.0f, float radius = 56.5685f, int faces = 4);
//~ };

#endif
