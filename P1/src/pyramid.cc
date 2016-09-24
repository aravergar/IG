#include "pyramid.h"

using namespace std;

class Pyramid: public Model{
protected:
	mesh_struct *mesh;
public:
	virtual Pyramid();
	virtual ~Pyramid();
	virtual draw(_render_mode mode, colorf color1, colorf color2 = NULL, int width = 0);
};

Pyramid::Pyramid(height = 10.0f, radius = 4.0f, faces = 3){
	this->height = height; this->radius = radius;
	if(faces>=3)	this->faces = faces;
	else
		this->faces = 3;
	float alpha = 0.0f;
	float alpha_delta = 2.0f*PI / this->faces;
	
	mesh = new mesh_struct();
	mesh->vertices.resize(this->faces+2);
	mesh->triangles.resize(this->faces*2);
	
	// Inserción de vértices
	mesh->vertices[0].x = 0.0f; mesh->vertices[0].y = height;
		mesh->vertices[0].z = 0.0f;
	for(int i=1; i<this->faces+1; i++){
		mesh->vertices[i].x = cos(alpha)*radius;
		mesh->vertices[i].y = 0.0f;
		mesh->vertices[i].z = sin(alpha)*radius;
		alpha+=alpha_delta;
	}
	mesh->vertices[this->faces+1].x = 0.0f;
	mesh->vertices[this->faces+1].y = 0.0f;
	mesh->vertices[this->faces+1].z = 0.0f;
	
	//~ V - 0
	//~ 1
	//~ 2
	//~ 3
	//~ BOTTOM - 4
	
	//~ 0-1-2
	//~ 0-2-3
	//~ 0-3-1
	//~ 1-4-2
	//~ 2-4-3
	//~ 3-4-1
	
	// Inserción de triángulos
	// * caras superiores
	for(int i=0; i<this->faces-1; i++){
		mesh->triangles[i]._0 = 0;
		mesh->triangles[i]._1 = i+1;
		mesh->triangles[i]._2 = i+2;
	}
	mesh->triangles[this->faces-1]._0 = 0;
	mesh->triangles[this->faces-1]._1 = this->faces;
	mesh->triangles[this->faces-1]._2 = 1;
	
	// * caras inferiores
	for(int i=this->faces; i<this->faces*2-1; i++){
		mesh->triangles[i]._0 = i-this->faces+1;
		mesh->triangles[i]._1 = this->faces+1;
		mesh->triangles[i]._2 = i-this->faces+2;
	}
	mesh->triangles[this->faces*2-1]._0 = this->faces;
	mesh->triangles[this->faces*2-1]._1 = this->faces+1;
	mesh->triangles[this->faces*2-1]._2 = 1;
}
Pyramid::~Pyramid(){
	if(mesh!=NULL){
		if(mesh->vertices!=NULL)
			delete mesh->vertices;
		if(mesh->triangles!=NULL)
			delete mesh->triangles;
		delete mesh;
		mesh = NULL;
	}
}
