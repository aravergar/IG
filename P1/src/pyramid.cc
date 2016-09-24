#include "pyramid.h"

using namespace std;

//~ class Pyramid: public Model{
//~ protected:
	//~ mesh_struct *mesh;
//~ public:
	//~ virtual Pyramid();
	//~ virtual ~Pyramid();
	//~ virtual draw(_render_mode mode, colorf color1, colorf color2 = NULL, int width = 0);
//~ };

Pyramid::Pyramid(height = 10.0f, radius = 4.0f, faces_val = 3){
	this->height = height; this->radius = radius;
	if(faces_val>=3)	this->faces = faces_val;
	else
		this->faces = 3;
	float alpha = 0.0f;
	float alpha_delta = 2.0f*PI / this->faces;
	
	mesh = new Mesh();
	mesh->vertices = (Tuple3r*) malloc(faces+2);
	mesh->triangles = (Tuple3n*) malloc(faces*2);
	
	//Inserción de vértices
	mesh->vertices[0].X = 0.0f; mesh->vertices[0].Y = height;
		mesh->vertices[0].Z = 0.0f;
	for(int i=1; i<faces+1; i++){
		mesh->vertices[i].X = cos(alpha)*radius;
		mesh->vertices[i].Y = 0.0f;
		mesh->vertices[i].Z = sin(alpha)*radius;
		alpha+=alpha_delta;
	}
	mesh->vertices[faces+1].X = 0.0f;
	mesh->vertices[faces+1].Y = 0.0f;
	mesh->vertices[faces+1].Z = 0.0f;
	
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
	
	
	
	
	
	
	
	//~ // METODO ANTIGUO CON _VERTEX3F
	//~ mesh = new mesh_struct();
	//~ mesh->vertices.resize(this->faces+2);
	//~ mesh->triangles.resize(this->faces*2);
	
	//~ // Inserción de vértices
	//~ mesh->vertices[0].x = 0.0f; mesh->vertices[0].y = height;
		//~ mesh->vertices[0].z = 0.0f;
	//~ for(int i=1; i<this->faces+1; i++){
		//~ mesh->vertices[i].x = cos(alpha)*radius;
		//~ mesh->vertices[i].y = 0.0f;
		//~ mesh->vertices[i].z = sin(alpha)*radius;
		//~ alpha+=alpha_delta;
	//~ }
	//~ mesh->vertices[this->faces+1].x = 0.0f;
	//~ mesh->vertices[this->faces+1].y = 0.0f;
	//~ mesh->vertices[this->faces+1].z = 0.0f;
	
	//~ // Inserción de triángulos
	//~ // * caras superiores
	//~ for(int i=0; i<this->faces-1; i++){
		//~ mesh->triangles[i]._0 = 0;
		//~ mesh->triangles[i]._1 = i+1;
		//~ mesh->triangles[i]._2 = i+2;
	//~ }
	//~ mesh->triangles[this->faces-1]._0 = 0;
	//~ mesh->triangles[this->faces-1]._1 = this->faces;
	//~ mesh->triangles[this->faces-1]._2 = 1;
	
	//~ // * caras inferiores
	//~ for(int i=this->faces; i<this->faces*2-1; i++){
		//~ mesh->triangles[i]._0 = i-this->faces+1;
		//~ mesh->triangles[i]._1 = this->faces+1;
		//~ mesh->triangles[i]._2 = i-this->faces+2;
	//~ }
	//~ mesh->triangles[this->faces*2-1]._0 = this->faces;
	//~ mesh->triangles[this->faces*2-1]._1 = this->faces+1;
	//~ mesh->triangles[this->faces*2-1]._2 = 1;
}

Pyramid::~Pyramid(){
	if(mesh!=NULL){
		if(mesh->vertices!=NULL)
			free (mesh->vertices);
		if(mesh->triangles!=NULL)
			free (mesh->triangles);
		delete mesh;
		mesh = NULL;
	}
}

draw(_render_mode mode, colorf color1, colorf color2 = NULL, int width = 0){
	glEnable(GL_CULL_FACE);
	glColor3f(color1.r, color1.g, color1.b);
	switch(mode){
	case VERTICES:
		glPointSize(width);
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, mesh->vertices);
		glDrawArrays(GL_POINTS, 0, mesh->num_ver);
		break;
	case EDGES:
		glLineWidth(width);
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, mesh->vertices);
		glDrawElements(GL_LINES, 3*mesh->num_tri,
			GL_UNSIGNED_INT, mesh->triangles);
		break;
	case SOLID:
		glLineWidth(width);
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, mesh->vertices);
		glDrawElements(GL_TRIANGLES, 3*mesh->num_tri,
			GL_UNSIGNED_INT, mesh->triangles);
		break;
	case CHECKERED:
		break;
	}
}



























