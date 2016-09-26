//**********************************************************************
// P1 - tetrahedron.cc
//
// Definitions for Tetrahedron class
//
// Antonio Rafael Verdejo Garcia 2016
//
// GPL-3.0
//**********************************************************************

#include "tetrahedron.h"

using namespace std;

Tetrahedron::Tetrahedron(float edge_length){
	float height = sqrt(2.0/3.0)*edge_length;
	float radius = sin(0.61547970867038734107)*height/sin(0.95531661812450927816);
	Pyramid(height,radius,3);
}
