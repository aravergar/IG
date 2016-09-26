//**********************************************************************
// P1 - pyramid.cc
//
// Definitions for Pyramid class
//
// Antonio Rafael Verdejo Garcia 2016
//
// GPL-3.0
//**********************************************************************

#include "pyramid.h"

using namespace std;

Pyramid::Pyramid(float height, float radius, int faces_val){
	cout<<"Creo piramide con parametros "<<height<<" "<<radius<<" "<<faces_val<<"\n";
	this->height = height; this->radius = radius;
	if(faces_val>=3)	this->faces = faces_val;
	else
		this->faces = 3;
	float alpha = 0.0f;
	float alpha_delta = 2.0f*PI / this->faces;
	
	cout<<"ALOJO MEMORIA PARA VERTICES Y TRIANGULOS\n";
	mesh = new Mesh();
	mesh->num_ver = faces+2;
	mesh->num_tri = faces*2;
	mesh->vertices = (Tuple3r*) malloc((mesh->num_ver)*sizeof(Tuple3r));
	mesh->triangles = (Tuple3n*) malloc((mesh->num_tri)*sizeof(Tuple3n));

	cout<<"COMIENZO INSERCION DE VERTICES\n";
	//Inserción de vértices
	mesh->vertices[0][X] = 0.0f; mesh->vertices[0][Y] = height;
		mesh->vertices[0][Z] = 0.0f;
	for(int i=1; i<faces+1; i++){
		mesh->vertices[i][X] = cos(alpha)*radius;
		mesh->vertices[i][Y] = 0.0f;
		mesh->vertices[i][Z] = sin(alpha)*radius;
		alpha+=alpha_delta;
	}
	mesh->vertices[faces+1][X] = 0.0f;
	mesh->vertices[faces+1][Y] = 0.0f;
	mesh->vertices[faces+1][Z] = 0.0f;
	
	cout<<"COMIENZO INSERCION DE TRIANGULOS\n";
	// Inserción de triángulos
	// * caras superiores
	for(int i=0; i<this->faces-1; i++){
		mesh->triangles[i][_0] = 0;
		mesh->triangles[i][_1] = i+1;
		mesh->triangles[i][_2] = i+2;
	}
	mesh->triangles[this->faces-1][_0] = 0;
	mesh->triangles[this->faces-1][_1] = this->faces;
	mesh->triangles[this->faces-1][_2] = 1;
	
	// * caras inferiores
	for(int i=this->faces; i<this->faces*2-1; i++){
		mesh->triangles[i][_0] = i-this->faces+1;
		mesh->triangles[i][_1] = this->faces+1;
		mesh->triangles[i][_2] = i-this->faces+2;
	}
	mesh->triangles[this->faces*2-1][_0] = this->faces;
	mesh->triangles[this->faces*2-1][_1] = this->faces+1;
	mesh->triangles[this->faces*2-1][_2] = 1;
}

























