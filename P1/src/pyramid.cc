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

Pyramid::~Pyramid(){
	cout<<"DESTRUYO PIRAMIDE\n";
	if(mesh!=NULL){
		if(mesh->vertices!=NULL)
			free (mesh->vertices);
		if(mesh->triangles!=NULL)
			free (mesh->triangles);
		delete mesh;
		mesh = NULL;
	}
}

void Pyramid::draw(_render_mode mode, Color3r color1, Color3r color2, int width){
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CCW);
	glColor3f(color1[r], color1[g], color1[b]);
	switch(mode){
	case VERTICES:
		cout<<"Modo VERTICES\n";
		cout<<"---con ver "<<mesh->num_ver<<" y tri "<<mesh->num_tri<<"\n";
		glPointSize(width);
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, mesh->vertices);
		glDrawArrays(GL_POINTS, 0, mesh->num_ver);
		cout<<"Terminado modo VERTICES\n";
		break;
	case EDGES:
		glLineWidth(width);
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, mesh->vertices);
		glDrawElements(GL_LINE_LOOP, 3*mesh->num_tri,
			GL_UNSIGNED_INT, mesh->triangles);
		break;
	case SOLID:
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, mesh->vertices);
		glDrawElements(GL_TRIANGLES, 3*mesh->num_tri,
			GL_UNSIGNED_INT, mesh->triangles);
		break;
	case CHECKERED:
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, mesh->vertices);
		glDrawElements(GL_TRIANGLES, 3*mesh->num_tri/2,
			GL_UNSIGNED_INT, alternate(true));
		glColor3f(color2[r], color2[g], color2[b]);
		cout<<"bien? "<<3*mesh->num_tri<<"\n";
		glDrawElements(GL_TRIANGLES, 3*mesh->num_tri/2,
			GL_UNSIGNED_INT, alternate(false));
		cout<<"bien!\n";
		break;
	}
}

Tuple3n* Pyramid::alternate(bool alternate_A){
	Tuple3n* alt = (Tuple3n*) malloc((mesh->num_tri)*sizeof(Tuple3n)/2);
	int cont = 0;
	uint i;
	if(alternate_A)	i=0;
	else
		i=1;
	for(i; i<mesh->num_tri; i+=2){
		alt[cont][0] = mesh->triangles[i][0];
		alt[cont][1] = mesh->triangles[i][1];
		alt[cont][2] = mesh->triangles[i][2];
		cout<<"alt "<<alt[cont][0]<<" mesh "<<mesh->triangles[i][0]<<endl;
		cout<<"alt "<<alt[cont][1]<<" mesh "<<mesh->triangles[i][1]<<endl;
		cout<<"alt "<<alt[cont][2]<<" mesh "<<mesh->triangles[i][2]<<endl;
		cont++;
	}
	return alt;
}

























