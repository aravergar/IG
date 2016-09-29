//**********************************************************************
// P1 - model.cc
//
// Definitions for Model class
//
// Antonio Rafael Verdejo Garcia 2016
//
// GPL-3.0
//**********************************************************************

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

void Model::test(){
	cout<<"tengo "<<mesh->num_ver<<" vértices y "<<mesh->num_tri<<" triángulos"<<endl;
}

void Model::draw(_render_mode mode, Color3r color1,
	Color3r color2, int width){
	//~ glEnable(GL_CULL_FACE);
	//~ glCullFace(GL_FRONT);
	//~ glFrontFace(GL_CCW);
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
		//~ glLineWidth(width);
		//~ glEnableClientState(GL_VERTEX_ARRAY);
		//~ glVertexPointer(3, GL_FLOAT, 0, mesh->vertices);
		//~ glDrawElements(GL_LINE_STRIP, 3*mesh->num_tri,
			//~ GL_UNSIGNED_INT, mesh->triangles);
		glLineWidth(width);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, mesh->vertices);
		glDrawElements(GL_TRIANGLES, 3*mesh->num_tri,
			GL_UNSIGNED_INT, mesh->triangles);
		
		break;
	case SOLID:
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, mesh->vertices);
		glDrawElements(GL_TRIANGLES, 3*mesh->num_tri,
			GL_UNSIGNED_INT, mesh->triangles);
		break;
	case CHECKERED:
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
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
		cout<<"alternando para i="<<i<<" con cont="<<cont<<endl;
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

// make_triangles(...)
// rellena los triangulos determinados a partir de los vertices de una malla
//
// los vertices a partir de los que hacer los triangulos se determinan por el indice 'init'
// consideramos la parte de la malla a procesar como el siguiente modelo:
//~ n "revoluciones" de m "vertices" cada una:
//~ a	b	c	...	x	x+m	...
//~ a+1	b+1	c+1
//~ a+2	b+2	c+2
//~ ...	...	...	...	x+(m-1)

//~ de lo que se deduce que el iterador vertical es (j=i; j<m-1; j++)
//~ (para en m-2 puesto que para m-1 no hay que calcular triangulo)
//~ siendo y relativo al iterador horizontal,
//~ que en su caso es (i=x; i<n; i++)

//~ for i=x i<m*n i+=m - se ejecuta n veces
	//~ for j=i j<i+m-1 j++ - se ejecuta m-2 veces
		//~ triangulo 1 para j
		//~ triangulo 2 para j

//~ ejemplo, m = 3 n = 3
//~ for i=0 i<3 i+=3
	//~ for j=i j<i+m-1 j++
		//~ triangulo 1 para j
		//~ triangulo 2 para j

//~ ejecutaria:
//~ i0 j0 t 0
//~ i0 j1 t 1
//~ i3 j3 t 3
//~ i3 j4 t 4
//~ i6 j6 t 6
//~ i6 j7 t 7
//~ enough

//~ puesto que no se puede hacer directamente la ultima tira de triangulos,
//~ bajamos en 1 a i y hacemos fuera de bucle la ultima tira

//~ siendo x el inicio de esta parte de la malla

//~ por tanto necesitamos:
	//~ m, numero de vertices por revolucion,
	//~ n, numero de revoluciones
	//~ x, inicio de vertices
	//~ y, inicio de triangulos


void Model::make_triangles_grid(int m, int n, int ver_ind, int tri_ind, bool ccw){
	int k=tri_ind;
	int a, b;
	cout<<"m="<<m<<" n="<<n<<" ver_ind="<<ver_ind<<" tri_ind="<<tri_ind<<endl;
	if(ccw){	a=1; b=2;}
	else{	a=2; b=1;}
	for(int i=ver_ind; i<m*(n-1)+ver_ind; i+=m){	// CORREGIDO de i<(m-1)*n a i<m*(n-1)
		cout<<"tira del vertice numero "<<i<<endl;
		for(int j=i; j<i+m-1; j++){
			mesh->triangles[k][0] = j;
			mesh->triangles[k][a] = j+1;
			mesh->triangles[k][b] = j+m+1;
			cout<<"tri1 con k="<<k<<" 0="<<mesh->triangles[k][0]<<" 1="<<mesh->triangles[k][1]<<" 2="<<mesh->triangles[k][2]<<endl;
			
			mesh->triangles[k+1][0] = j;
			mesh->triangles[k+1][a] = j+m+1;
			mesh->triangles[k+1][b] = j+m;
			cout<<"tri2 con k="<<k+1<<" 0="<<mesh->triangles[k+1][0]<<" 1="<<mesh->triangles[k+1][1]<<" 2="<<mesh->triangles[k+1][2]<<endl;
						
			k+=2;
		}
	}
	int h=ver_ind;
	cout<<"FINAL ROUND"<<endl;
	
	//~ m=4
	//~ n=6
	//~ ver_ind = 1
	//~ 1	5	9	13	17	21
	//~ 2	6	10	14	18	22
	//~ 3	7	11	15	19	23
	//~ 4	8	12	16	20	24
	
	//~ 0	4	8	12	16	20
	//~ 1	5	9	13	17	21
	//~ 2	6	10	14	18	22
	//~ 3	7	11	15	19	23
	
	//~ ver_ind	ver_ind+m	m*(n-2)+ver_ind	m*(n-1)+ver_ind
	//~ v+1
	//~ v+2
	
	
	
	//~ for(int j=m*n-1; j<m*n+m-2; j++){
	//~ for(int j=(m-1)*n+m-1; j<(m-1)*n+2*(m-1); j++){
	//~ for(int j=m*(n-2)+ver_ind; j<m*(n-1)+ver_ind; j++){
	for(int j=m*(n-1)+ver_ind-1; j<m*n+ver_ind-2; j++){
		mesh->triangles[k][0] = j+1;
		mesh->triangles[k][a] = j+2;
		mesh->triangles[k][b] = h+1;
		cout<<"tri1 con j="<<j<<" y k="<<k<<" 0="<<mesh->triangles[k][0]<<" 1="<<mesh->triangles[k][1]<<" 2="<<mesh->triangles[k][2]<<endl;
		
		mesh->triangles[k+1][0] = j+1;
		mesh->triangles[k+1][a] = h+1;
		mesh->triangles[k+1][b] = h;
		cout<<"tri2 con j="<<j<<" y k="<<k+1<<" 0="<<mesh->triangles[k+1][0]<<" 1="<<mesh->triangles[k+1][1]<<" 2="<<mesh->triangles[k+1][2]<<endl;
		k+=2;
		h++;
	}
}

// make_triangles_hollow_body(...)
// rellena los triangulos determinados a partir
//   de los vertices de una malla cerrada VERTICAL y HORIZONTALMENTE
// ejemplo de malla:

//~ m=4
//~ n=5
//~ m*n = 20 vertices
//~ 0	4	8	12	16
//~ 1	5	9	13	17
//~ 2	6	10	14	18
//~ 3	7	11	15	19
//~ se harán triángulos para las filas 1 y 4 y para las columnas 1 y 5
//~ por tanto, itero sobre 0, 1 y 2. Fuera, caso especial, 3 (m-1)
//~ hor. itero sobre 0, 4, 8, 12. Fuera, caso especial, 16 (n-1)
//
// los vertices a partir de los que hacer los triangulos se determinan por el indice 'init'
// consideramos la parte de la malla a procesar como el siguiente modelo:
//~ n "revoluciones" de m "vertices" cada una:
//~ a	b	c	...	x	x+m	...
//~ a+1	b+1	c+1
//~ a+2	b+2	c+2
//~ ...	...	...	...	x+(m-1)
void Model::make_triangles_hollow_body(int m, int n, int ver_ind, int tri_ind){
	int k=tri_ind;
	
	cout<<"m="<<m<<" n="<<n<<" ver_ind="<<ver_ind<<" tri_ind="<<tri_ind<<endl;
	cout<<"triangulos ordinarios"<<endl;
	for(int i=ver_ind; i<m*n-m; i+=m){	//itera de columna en columna
		for(int j=i; j<i+m-1; j++){		//itera de vertice en vertice
			mesh->triangles[k][0] = j;
			mesh->triangles[k][1] = j+1;
			mesh->triangles[k][2] = j+m+1;
			cout<<"tri1 con k="<<k<<" 0="<<mesh->triangles[k][0]<<" 1="<<mesh->triangles[k][1]<<" 2="<<mesh->triangles[k][2]<<endl;
			
			mesh->triangles[k+1][0] = j;
			mesh->triangles[k+1][1] = j+m+1;
			mesh->triangles[k+1][2] = j+m;
			cout<<"tri2 con k="<<k+1<<" 0="<<mesh->triangles[k+1][0]<<" 1="<<mesh->triangles[k+1][1]<<" 2="<<mesh->triangles[k+1][2]<<endl;
						
			k+=2;
		}
		cout<<"triangulos para cerrar bucle actual i="<<i<<endl;
		//triangulos para unir verticalmente
		mesh->triangles[k][0] = i+m-1;	//ultimo vertice de la columna
		mesh->triangles[k][1] = i;		//primer vertice de la columna
		mesh->triangles[k][2] = i+m;	//primer vertice de la columna siguiente
		cout<<"fbucle tri1 con k="<<k<<" 0="<<mesh->triangles[k][0]<<" 1="<<mesh->triangles[k][1]<<" 2="<<mesh->triangles[k][2]<<endl;
		
		mesh->triangles[k+1][0] = i+m-1;	//ultimo vertice de la columna
		mesh->triangles[k+1][1] = i+m;		//primer vertice de la columna siguiente
		mesh->triangles[k+1][2] = i+2*m-1;	//ultimo vertice de la columna siguiente
		cout<<"fbucle tri2 con k="<<k+1<<" 0="<<mesh->triangles[k+1][0]<<" 1="<<mesh->triangles[k+1][1]<<" 2="<<mesh->triangles[k+1][2]<<endl;
		k+=2;
	}
	cout<<"triangulos para unir horizontalmente el grid"<<endl;
	//bucle final para unir horizontalmente
	int h=ver_ind;
	for(int j=m*n-m; j<m*n-1; j++){	//itera de vertice en vertice
		cout<<"uniendo para j="<<j<<endl;
		mesh->triangles[k][0] = j;
		mesh->triangles[k][1] = j+1;
		mesh->triangles[k][2] = h+1;
		cout<<"tri1 con k="<<k<<" 0="<<mesh->triangles[k][0]<<" 1="<<mesh->triangles[k][1]<<" 2="<<mesh->triangles[k][2]<<endl;
		
		mesh->triangles[k+1][0] = j;
		mesh->triangles[k+1][1] = h+1;
		mesh->triangles[k+1][2] = h;
		cout<<"tri2 con k="<<k+1<<" 0="<<mesh->triangles[k+1][0]<<" 1="<<mesh->triangles[k+1][1]<<" 2="<<mesh->triangles[k+1][2]<<endl;
		k+=2;
		h++;
	}
	cout<<"dos triangulos para vertice final"<<endl;
	//triangulos para unir verticalmente el ultimo vertice (esquina de grid)
	//~ m*n-1 - m*n-m - ver_ind
	//~ m*n-1 - ver_ind - m-1
	mesh->triangles[k][0] = ver_ind+m*n-1;
	mesh->triangles[k][1] = ver_ind+m*n-m;
	mesh->triangles[k][2] = ver_ind;
	cout<<"chungo tri1 con k="<<k<<" 0="<<mesh->triangles[k][0]<<" 1="<<mesh->triangles[k][1]<<" 2="<<mesh->triangles[k][2]<<endl;
	
	mesh->triangles[k+1][0] = ver_ind+m*n-1;
	mesh->triangles[k+1][1] = ver_ind;
	mesh->triangles[k+1][2] = ver_ind+m-1;
	cout<<"chungo tri2 con k="<<k+1<<" 0="<<mesh->triangles[k+1][0]<<" 1="<<mesh->triangles[k+1][1]<<" 2="<<mesh->triangles[k+1][2]<<endl;
	
	
}

//~ 0
//~ 1 4 7
//~ 2 5 8
//~ 3 6 9
//~ x

//~ 0 1 4
//~ 0 4 7
//~ 0 7 1






void Model::make_triangles_fan(int m, int n, int ver_ind, int tri_ind, int center_ind, bool ccw){
	cout<<"fan para m="<<m<<", n="<<n<<", ver_ind="<<ver_ind<<", tri_ind="<<tri_ind<<", center_ind="<<center_ind<<" y ccw="<<ccw<<endl;
	int j = ver_ind;
	int a, b;
	if(ccw){	a=1; b=2;}
	else{	a=2; b=1;}
	for(int i=tri_ind; i<tri_ind+n-1; i++){
		mesh->triangles[i][0] = center_ind;
		mesh->triangles[i][a] = j;
		mesh->triangles[i][b] = j+m;
		cout<<"insertando triangulo fan en i="<<i<<", con 0="<<center_ind<<", a="<<j<<" y b="<<j+m<<endl;
		j+=m;
	}
	mesh->triangles[tri_ind+n-1][0] = center_ind;
	mesh->triangles[tri_ind+n-1][a] = j;
	mesh->triangles[tri_ind+n-1][b] = ver_ind;
	cout<<"insertando triangulo FINAL en i="<<tri_ind+n-1<<", con 0="<<center_ind<<", a="<<j<<" y b="<<ver_ind<<endl;
	//~ if(ccw){
		//~ for(int i=tri_ind; i<tri_ind+n-1; i++){
			//~ triangles[i][0] = center_ind;
			//~ triangles[i][1] = j;
			//~ triangles[i][2] = j+m;
			//~ j+=m;
		//~ }
		//~ triangles[tri_ind+n-1][0] = center_ind;
		//~ triangles[tri_ind+n-1][1] = j;
		//~ triangles[tri_ind+n-1][2] = ver_ind;
	//~ }
	//~ else{
		//~ for(int i=tri_ind; i<tri_ind+n-1; i++){
			//~ triangles[i][0] = center_ind;
			//~ triangles[i][1] = j+m;
			//~ triangles[i][2] = j;
			//~ j+=m;
		//~ }
		
	//~ }
}

void Model::revolution(Tuple3r* vertices, Tuple3r* countour, uint count_num, uint revs, uint init, int plane, int axis){
	float alpha = 0.0f;
	float alpha_delta = 2.0f*PI / revs;
	cout<<"punto generador 0: plane="<<countour[0][plane]<<", axis="<<countour[0][axis]<<", ind="<<countour[0][3-(plane+axis)]<<endl;
	for(uint i=init; i<count_num+init; i++){
		vertices[i][X] = countour[i-init][X];
		vertices[i][Y] = countour[i-init][Y];
		vertices[i][Z] = countour[i-init][Z];
		cout<<"generar para i="<<i<<", x="<<vertices[i][X]<<", y="<<vertices[i][Y]<<", z="<<vertices[i][Z]<<endl;
	}
	int cont=count_num+init;
	alpha+=alpha_delta;
	//~ cout<<"????"<<plane+axis<<endl;
	int ind_plane = 3-(int)(plane+axis);
	cout<<"plane="<<plane<<", axis="<<axis<<" e ind_plane="<<ind_plane<<endl;
	// Introducir aquí variación de la generación dependiendo del eje sobre el que rotar
	switch(axis){
	case 0:
		cout<<"generación por el eje "<<axis<<endl;
		for(uint i=1; i<revs; i++){
			for(uint j=0; j<count_num; j++){
				vertices[cont][ind_plane] = countour[j][ind_plane]*cos(alpha);
				vertices[cont][axis] = countour[j][axis];
				vertices[cont][plane] = countour[j][ind_plane]*sin(alpha);
				cout<<"generar para cont="<<cont<<", x="<<vertices[cont][X]<<", y="<<vertices[cont][Y]<<", z="<<vertices[cont][Z]<<endl;
				cont++;
			}
			alpha+=alpha_delta;
		}
		break;
	case 1:
		cout<<"generación por el eje "<<axis<<endl;
		for(uint i=1; i<revs; i++){
			for(uint j=0; j<count_num; j++){
				vertices[cont][ind_plane] = countour[j][ind_plane]*cos(alpha);
				vertices[cont][axis] = countour[j][axis];
				vertices[cont][plane] = countour[j][ind_plane]*sin(alpha);
				cout<<"generar para cont="<<cont<<", x="<<vertices[cont][X]<<", y="<<vertices[cont][Y]<<", z="<<vertices[cont][Z]<<endl;
				cont++;
			}
			alpha+=alpha_delta;
		}
		break;
	case 2:
		cout<<"generación por el eje "<<axis<<endl;
		for(uint i=1; i<revs; i++){
			for(uint j=0; j<count_num; j++){
				vertices[cont][ind_plane] = countour[j][ind_plane]*cos(alpha);
				vertices[cont][axis] = countour[j][axis];
				vertices[cont][plane] = countour[j][ind_plane]*sin(alpha);
				cout<<"generar para cont="<<cont<<", x="<<vertices[cont][X]<<", y="<<vertices[cont][Y]<<", z="<<vertices[cont][Z]<<endl;
				cont++;
			}
			alpha+=alpha_delta;
		}
		break;
	}
	for(uint i=init; i<count_num*revs+init; i++){
		cout<<"Vertice "<<i<<": x="<<vertices[i][X]<<", y="<<vertices[i][Y]<<", z="<<vertices[i][Z]<<endl;
	}
}

































































