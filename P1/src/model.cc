#include "model.h"

using namespace std;

Model::~Model(){
	if(mesh!=NULL){
		if(mesh->vertices!=NULL)
			free (mesh->vertices);
		if(mesh->triangles!=NULL)
			free (mesh->triangles);
		delete mesh;
		mesh = NULL;
	}
}

void Model::draw(_render_mode mode, Color3r color1,
	Color3r color2, int width){
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

Tuple3n* Model::alternate(bool alternate_A){
	Tuple3n* alt = (Tuple3n*) malloc((mesh->num_tri)*sizeof(Tuple3n)/2);
	int cont = 0;
	uint i;
	if(alternate_A)	i=0;
	else
		i=1;
	for( ; i<mesh->num_tri; i+=2){
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
