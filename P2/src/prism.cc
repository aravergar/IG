//**********************************************************************
// P1 - prism.cc
//
// Definitions for Prism class
//
// Antonio Rafael Verdejo Garcia 2016
//
// GPL-3.0
//**********************************************************************

#include "prism.h"

using namespace std;

Prism::Prism(float height, float radius, int faces_val){
	this->height = height; this->radius = radius;
	if(faces_val>=3)	faces = faces_val;
	else
		faces = 3;
	float alpha = 0.0f;
	float alpha_delta = 2.0f*PI / faces;
	
	mesh = new Mesh();
	mesh->num_ver = faces*2+2;
	mesh->num_tri = faces*4;
	mesh->vertices = (Tuple3r*) malloc((mesh->num_ver)*sizeof(Tuple3r));
	mesh->triangles = (Tuple3n*) malloc((mesh->num_tri)*sizeof(Tuple3n));

	//Inserción de vértices
	// * centro cara superior
	mesh->vertices[0][X] = 0.0f; mesh->vertices[0][Y] = height;
		mesh->vertices[0][Z] = 0.0f;
	
	// * tira de vertices (para compatibilidad con make_triangles)
	for(int i=1; i<faces*2+1; i+=2){
		// * vertice superior
		mesh->vertices[i][X] = cos(alpha)*radius;
		mesh->vertices[i][Y] = height;
		mesh->vertices[i][Z] = sin(alpha)*radius;
		cout<<"vertice "<<i<<" X="<<mesh->vertices[i][X]<<" Y="<<mesh->vertices[i][Y]<<" Z="<<mesh->vertices[i][Z]<<endl;
		
		// * vertice inferior
		mesh->vertices[i+1][X] = cos(alpha)*radius;
		mesh->vertices[i+1][Y] = 0.0f;
		mesh->vertices[i+1][Z] = sin(alpha)*radius;
		cout<<"vertice "<<i+1<<" X="<<mesh->vertices[i+1][X]<<" Y="<<mesh->vertices[i+1][Y]<<" Z="<<mesh->vertices[i+1][Z]<<endl;
		alpha+=alpha_delta;
		
	}
	
	// * centro cara inferior
	mesh->vertices[faces*2+1][X] = 0.0f;
	mesh->vertices[faces*2+1][Y] = 0.0f;
	mesh->vertices[faces*2+1][Z] = 0.0f;
	
	for(int i=0; i<=faces*2+1; i++){
		cout<<"vertice i="<<i<<", X="<<mesh->vertices[i][X]<<" Y="<<mesh->vertices[i][Y]<<" Z="<<mesh->vertices[i][Z]<<endl;
	}
	
	// Inserción de triángulos
	// * caras superiores
	int j=1;
	for(int i=0; i<faces-1; i++){
		mesh->triangles[i][0] = 0;
		mesh->triangles[i][1] = j;
		mesh->triangles[i][2] = j+2;
		j+=2;
	}
	mesh->triangles[faces-1][0] = 0;
	mesh->triangles[faces-1][1] = faces*2-1;
	mesh->triangles[faces-1][2] = 1;
	
	//~ 0
	//~ 1 2 3
	//~ 4 5 6
	//~ 7
	
	//~ 0
	//~ 1 2 3 4
	//~ 5 6 7 8
	//~ 9
	
	//~ 0
	//~ 1 2 ...
	//~ faces+1 faces+2 faces+3 ...
	//~ faces*2+1
	
	//~ init init+1 init+2 ...
	//~ num+1 num+2 num+3 ...
	//~ it = 0
	//~ init+it - num+it+1 - num+it+2
	//~ init+it - num+it+2 - init+1
	
	//~ 1 4 5
	//~ 1 5 2
	//~ 2 5 6
	//~ 2 6 3
	//~ 3 6 4
	//~ 3 4 1
	
	// * caras laterales
	// testeo de make_triangles
	
	make_triangles_grid(2, faces, 1, faces);
	
	// * caras inferiores
	cout<<"vertice 9 "<<mesh->vertices[9][0]<<" "<<mesh->vertices[9][1]<<" "<<mesh->vertices[9][2]<<endl;
	
	int k = 2;
	for(int i=faces*3; i<faces*4-1; i++){
		mesh->triangles[i][_0] = k;
		mesh->triangles[i][_1] = faces*2+1;
		mesh->triangles[i][_2] = k+2;
		k+=2;
		cout<<"tri con i="<<i<<" 0="<<mesh->triangles[i][0]<<" 1="<<mesh->triangles[i][1]<<" 2="<<mesh->triangles[i][2]<<endl;
	}
	mesh->triangles[faces*4-1][_0] = faces*2;
	mesh->triangles[faces*4-1][_1] = faces*2+1;
	mesh->triangles[faces*4-1][_2] = 2;
	cout<<"tri con i="<<faces*4-1<<" 0="<<mesh->triangles[faces*4-1][0]<<" 1="<<mesh->triangles[faces*4-1][1]<<" 2="<<mesh->triangles[faces*4-1][2]<<endl;
	cout<<mesh->triangles[faces*4-1][_0]<<"???"<<endl;
	cout<<"num_tri "<<mesh->num_tri<<endl;
	cout<<"¿¿¿¿?¿?"<<mesh->triangles[16][0]<<" "<<mesh->triangles[16][1]<<" "<<mesh->triangles[16][2]<<endl;
	cout<<"comienza la fiesta\n";
	for(int i=0; i<faces*4; i++){
		cout<<"triangulo "<<i<<", a = "<<mesh->triangles[i][0]<<", b = "<<mesh->triangles[i][1]<<", c = "<<mesh->triangles[i][2]<<endl;
	}
}




























