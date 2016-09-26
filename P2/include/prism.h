//**********************************************************************
// P1 - prism.h
//
// Header file for Prism class
//
// Antonio Rafael Verdejo Garcia 2016
//
// GPL-3.0
//**********************************************************************

#ifndef _PRISM_H
#define _PRISM_H

#include "model.h"

using namespace std;

// Class Prism
//
// Define un objeto 3D con forma de prisma a partir de 3 parámetros:
// * radio (distancia entre una esquina y el centro proyectado en base
// * altura (distancia desde la base hasta la cara superior)
// * número de caras (a partir de 3)
// Por tanto, un prisma de número de caras muy alto puede equivaler
//   a un cilindro, puesto que su base parecerá un círculo
class Prism: public Model{
protected:
	float height, radius;
	int faces;
public:
	Prism(float height = 80.0f, float radius = 56.5685f, int faces = 4);
};

#endif
