//**********************************************************************
// P1 - torus.cc
//
// Definitions for Torus class
//
// Antonio Rafael Verdejo Garcia 2016
//
// GPL-3.0
//**********************************************************************

#include "torus.h"

using namespace std;

Torus::Torus(float radius_may, float radius_min, uint div_ver_val, uint div_hor_val){
	// asignación de parámetros
	cout<<"div_ver_val="<<div_ver_val<<endl;
	this->radius_may = radius_may; this->radius_min = radius_min;
	if(div_ver_val>=3)	this->div_ver = div_ver_val;
	else
		this->div_ver = 3;
	if(div_hor_val>=3)	this->div_hor = div_hor_val;
	else
		this->div_hor = 3;
	cout<<"asignaciones para toro: rad_min="<<radius_min<<", rad_may="<<radius_may<<", div_ver="<<div_ver<<", div_hor="<<div_hor<<endl;
	
	cout<<"a reservar memoria para toro"<<endl;
	// reserva de memoria
	mesh = new Mesh();
	mesh->num_ver = div_hor*div_ver;
	mesh->num_tri = div_hor*div_ver*2;
	mesh->vertices = (Tuple3r*) malloc((mesh->num_ver)*sizeof(Tuple3r));
	mesh->triangles = (Tuple3n*) malloc((mesh->num_tri)*sizeof(Tuple3n));
	
	// creación del círculo generador
	Tuple3r* circle = (Tuple3r*) malloc((div_ver)*sizeof(Tuple3r));
	float alpha = 0.0f;
	float alpha_delta = 2.0f*PI / div_ver;
	for(uint i=0; i<div_ver; i++){
		cout<<"div_ver="<<div_ver<<" i="<<i<<endl;
		circle[i][X] = radius_may+radius_min*cos(alpha);
		circle[i][Y] = radius_min*sin(alpha);
		circle[i][Z] = 0.0f;
		alpha-=alpha_delta;
		cout<<"gen x="<<circle[i][X]<<", y="<<circle[i][Y]<<", z="<<circle[i][Z]<<endl;
	}
	
	// revolución del círculo
	revolution(mesh->vertices, circle, div_ver, div_hor);
	
	// asignación de triángulos
	make_triangles_hollow_body(div_ver, div_hor, 0, 0);
	
	cout<<"num ver="<<mesh->num_ver<<", num tri = "<<mesh->num_tri<<endl;
}
