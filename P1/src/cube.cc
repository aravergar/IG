//**********************************************************************
// P1 - cube.cc
//
// Definitions for Cube class
//
// Antonio Rafael Verdejo Garcia 2016
//
// GPL-3.0
//**********************************************************************

#include "cube.h"

using namespace std;

Cube::Cube(float edge_length){
	float radius = sqrt(2*pow(edge_length,2));
	//~ float height = sqrt(2.0/3.0)*edge_length;
	//~ float radius = sin(0.61547970867038734107)*height/sin(0.95531661812450927816);
	Prism(edge_length,radius,4);
}
