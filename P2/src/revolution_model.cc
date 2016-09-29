//**********************************************************************
// P2 - revolution_model.cc
//
// Definitions for RevolutionModel class
//
// Antonio Rafael Verdejo Garcia 2016
//
// GPL-3.0
//**********************************************************************

#include "revolution_model.h"

using namespace std;

RevolutionModel::RevolutionModel(Tuple3r *countour, int num_ver, int plane, int revolutions, int axis){
	// averiguar el plano en que se encuentra
	int pre_plane = test_plane(countour);
	int m;
	cout<<"el preplano es "<<pre_plane<<" y el plano es "<<plane<<endl;
	cout<<"el eje provisional es "<<axis<<endl;
	// determinar el eje
	
	if (plane == axis){
		if(plane == Z)	axis = X;
		else	axis++;
	}
	
	if(pre_plane!=plane){
		change_plane(countour, num_ver, pre_plane, plane, axis);
	}
	
	cout<<"el plano final es "<<plane<<endl;
	cout<<"el eje final es "<<axis<<endl;
	if(revolutions<3)	revolutions=3;
	cout<<"el número de revoluciones es "<<revolutions<<endl;
	
	this->plane = plane;	this->axis = axis;	this->revolutions = revolutions;
	
	// inicializaciones
	mesh = new Mesh();
	
	//~ el cuerpo puede ser - hueco, copa, casco, esferico - equivalentes a los antiguos HOLLOW, LACKING_TOP, LACKING_BOTTOM, CLOSED
	//~ si es esferico, hay que mirar si es necesario hacer grid (si el perfil tiene 3 vertices, es como hacer tapa sup. e inf.)
	//~ el perfil puede tener dos vertices si es hueco, copa o casco (en cuyos casos solo hay grid si es hueco)
	//~ se prepara la tapa superior - si es copa o hueco, se crea vertice top
	//~ se prepara grid - si hueco con v>=2, si copa o hueco con v>=3, si esfera con v>=4
	//~ se prepara la tapa inferior - si es casco o hueco, se crea vertice inferior
	
	int ind_axis;
	Topology topol = test_topology(countour, num_ver, plane, axis, &ind_axis);
	
	switch(topol){
		case HOLLOW:
			cout<<"el objeto es HOLLOW"<<endl;
			mesh->num_ver = num_ver*revolutions+2;
			mesh->num_tri = (num_ver-1)*revolutions*2+2*revolutions;
			//~ mesh->num_tri = 3*(num_ver)*revolutions;
			cout<<"el objeto TIENE "<<mesh->num_ver<<" vértices y "<<mesh->num_tri<<" triángulos"<<endl;
			mesh->vertices = (Tuple3r*) malloc((mesh->num_ver)*sizeof(Tuple3r));
			mesh->triangles = (Tuple3n*) malloc((mesh->num_tri)*sizeof(Tuple3n));
			m = num_ver;
			//~ revolution(mesh->vertices, countour, num_ver, revolutions, 1);	// comun a los 4
			//~ revolution(Tuple3r* vertices, Tuple3r* countour, uint count_num, uint revs, uint init)
			break;
		case CONCAVE:	//TERMINAR
			cout<<"el objeto es CONCAVE"<<endl;
			mesh->num_ver = (num_ver-1)*revolutions+2;
			mesh->num_tri = 3*(num_ver-1)*revolutions;
			m = num_ver-1;
			//~ revolution(mesh->vertices, countour, num_ver, revolutions, 1);
			break;
		case CONVEX:	//TERMINAR
			cout<<"el objeto es CONVEX"<<endl;
			mesh->num_ver = (num_ver-1)*revolutions+2;
			mesh->num_tri = 3*(num_ver-1)*revolutions;
			m = num_ver-1;
			//~ revolution(mesh->vertices, countour, num_ver, revolutions, 1);
			break;
		case CLOSED:	//TERMINAR
			cout<<"el objeto es CLOSED"<<endl;
			mesh->num_ver = (num_ver-2)*revolutions+2;
			mesh->num_tri = 4*(num_ver-2)*revolutions;
			m = num_ver-2;
			//~ revolution(mesh->vertices, countour, num_ver, revolutions, 1);
			break;
	}
	revolution(mesh->vertices, countour, num_ver, revolutions, 1, plane, axis);
	cout<<"el eje de giro es "<<axis<<" el eje independiente es "<<ind_axis<<" y el plano es "<<plane<<endl;
	cout<<"el objeto tendrá "<<mesh->num_ver<<" vértices y "<<mesh->num_tri<<" triángulos"<<endl;
	
	/*
	 * si HOLLOW o CONCAVE:
	 * si axis = X
	 * x = countour[height]
	 * y = 0
	 * z = 0
	 * si axis = Y
	 * x = 0
	 * y = countour[height]
	 * z = 0
	 * si axis = Z
	 * x = 0
	 * y = 0
	 * z = countour[height]
	*/
	
	switch(topol){
		case HOLLOW:
		case CONCAVE:
			mesh->vertices[0][X] = 0;
			mesh->vertices[0][Y] = 0;
			mesh->vertices[0][Z] = 0;
			switch(axis){
				case X:
					mesh->vertices[0][X] = countour[0][X];
					break;
				case Y:
					mesh->vertices[0][Y] = countour[0][Y];
					break;
				case Z:
					mesh->vertices[0][Z] = countour[0][Z];
					break;
			}
			break;
		case CONVEX:
		case CLOSED:
			mesh->vertices[0][X] = countour[0][X];
			mesh->vertices[0][Y] = countour[0][Y];
			mesh->vertices[0][Z] = countour[0][Z];
			break;
	}
	
	//~ mesh->vertices[mesh->num_ver-1][X] = countour[0][X];
	//~ mesh->vertices[mesh->num_ver-1][X] = 0;
	switch(topol){
		case HOLLOW:
		case CONVEX:
			mesh->vertices[mesh->num_ver-1][X] = 0;	// esto si HOLLOW o CONVEX
			mesh->vertices[mesh->num_ver-1][Y] = 0;
			mesh->vertices[mesh->num_ver-1][Z] = 0;
			switch(axis){
				case X:
					mesh->vertices[mesh->num_ver-1][X] = countour[num_ver-1][X];
					break;
				case Y:
					mesh->vertices[mesh->num_ver-1][Y] = countour[num_ver-1][Y];
					break;
				case Z:
					mesh->vertices[mesh->num_ver-1][Z] = countour[num_ver-1][Z];
					break;
			}
			break;
		case CONCAVE:
		case CLOSED:
			mesh->vertices[mesh->num_ver-1][X] = countour[num_ver-1][X];
			mesh->vertices[mesh->num_ver-1][Y] = countour[num_ver-1][Y];
			mesh->vertices[mesh->num_ver-1][Z] = countour[num_ver-1][Z];
			break;
	}
	
	cout<<"el objeto TIENE "<<mesh->num_ver<<" vértices y "<<mesh->num_tri<<" triángulos"<<endl;
	
	//~ cout<<"su vertice inicial es X="<<mesh->vertices[0][X]<<", Y="<<mesh->vertices[0][Y]<<", Z="<<mesh->vertices[0][Z]<<endl;
	//~ cout<<"vertice antepenultimo numero "<<mesh->num_ver-3<<" es X="<<mesh->vertices[mesh->num_ver-3][X]<<", Y="<<mesh->vertices[mesh->num_ver-3][Y]<<", Z="<<mesh->vertices[mesh->num_ver-3][Z]<<endl;
	//~ cout<<"vertice penultimo numero "<<mesh->num_ver-2<<" es X="<<mesh->vertices[mesh->num_ver-2][X]<<", Y="<<mesh->vertices[mesh->num_ver-2][Y]<<", Z="<<mesh->vertices[mesh->num_ver-2][Z]<<endl;
	//~ cout<<"y su vertice final numero "<<mesh->num_ver-1<<" es X="<<mesh->vertices[mesh->num_ver-1][X]<<", Y="<<mesh->vertices[mesh->num_ver-1][Y]<<", Z="<<mesh->vertices[mesh->num_ver-1][Z]<<endl;
	
	// hay que rellenar los triangulos de la tapa superior...
	// distinto para HOLLOW-CONCAVE que para CONVEX-CLOSED
	make_triangles_fan(m, revolutions, 1, 0, 0, true);
	cout<<"el objeto TIENE "<<mesh->num_ver<<" vértices y "<<mesh->num_tri<<" triángulos"<<endl;
	// ...rellenar los triangulos de la malla...
	//~ make_triangles_grid(int m, int n, int ver_ind, int tri_ind);
	make_triangles_grid(m, revolutions, 1, revolutions);
	cout<<"el objeto TIENE "<<mesh->num_ver<<" vértices y "<<mesh->num_tri<<" triángulos"<<endl;
	// ...y por ultimo los de la tapa inferior
	//~ make_triangles_fan(int m, int n, int ver_ind, int tri_ind, int center_ind, bool ccw);
	make_triangles_fan(m, revolutions, m, mesh->num_tri-revolutions, mesh->num_ver-1, false);
	cout<<"el objeto TIENE "<<mesh->num_ver<<" vértices y "<<mesh->num_tri<<" triángulos"<<endl;
	cout<<"DANGER INTERNO"<<endl;
	this->test();
	cout<<"DANGER INTERNO"<<endl;
}

RevolutionModel::RevolutionModel(char *file, int plane, int revolutions, int axis){
	_file_ply ply_f;
	
	vector<float> ply_ver;
	vector<int> ply_tri;
	cout<<"COMIENZO A CREAR REV MODEL"<<endl;
	ply_f._file_ply::open(file);
	ply_f._file_ply::read(ply_ver, ply_tri);
	
	//~ cout<<"el tamanyo de tri es "<<ply_tri.size()<<"\n";

	//~ arrange(ply_ver, ply_tri);
	ply_f._file_ply::close();
	
	int num_ver = ply_ver.size()/3;
	cout<<"el perfil tiene "<<num_ver<<" vertices\n";
	Tuple3r *vertices = (Tuple3r*) malloc((num_ver)*sizeof(Tuple3r));
		
	for(int i=0; i<num_ver; i++){
		vertices[i][X] = ply_ver[i*3];
		vertices[i][Y] = ply_ver[i*3+1];
		vertices[i][Z] = ply_ver[i*3+2];
	}
	
	//~ int pre_plane = test_plane(vertices);
	
	RevolutionModel *another = new RevolutionModel(vertices, num_ver, plane, revolutions, axis);
	*this = *another;
	//~ *this = new RevolutionModel(vertices, num_ver, revolutions, axis);
	cout<<"DANGER"<<endl;
	this->test();
	cout<<"DANGER"<<endl;
}

int RevolutionModel::test_plane(Tuple3r *countour){
	int plane;
	
	if(countour[0][X] == 0 && countour[1][X] == 0)	plane = X;
	else{
		if(countour[0][Y] == 0 && countour[1][Y] == 0)	plane = Y;
		else
			plane = Z;
	}
	
	return plane;
}

Topology RevolutionModel::test_topology(Tuple3r *countour, int num_ver, int plane, int axis, int *ind_axis){
	// tengo que testear si el primer y el ultimo punto (0 y num_ver-1) están situados en el eje de rotación
	// ind_axis tiene que ser distinto que plane y axis
	
	//~ plane	axis	ind_axis
	//~ X	0	Y	1	Z	2
	//~ X	0	Z	2	Y	1
	//~ Y	1	X	0	Z	2
	//~ Y	1	Z	2	X	0
	//~ Z	2	X	0	Y	1
	//~ Z	2	Y	1	X	0

	//~ x*y+x+y	3-(x*y+x+y)
	//~ 1		
	//~ 2		
	//~ 1		
	//~ 5		
	//~ 2		
	//~ 5
	
	//~ x+y		ind_axis
	//~ 1		2
	//~ 2		1
	//~ 1		2
	//~ 3		0
	//~ 2		1
	//~ 3		0

	//~ x*y+x+y	3-(x*y+x+y)
	//~ 1		2
	//~ 2		1
	//~ 1		2
	//~ 4		-1
	//~ 2		1
	//~ 4		-1
	
	Topology topol;
	cout<<"plane = "<<plane<<" y axis = "<<axis<<", por lo que plane*axis = "<<plane*axis<<", plane*axis+plane+axis = "<<plane*axis+plane+axis<<endl;
	*ind_axis = 3-(plane + axis);
	if(*ind_axis == -1)	*ind_axis = 0;
	cout<<"eje independiente es "<<*ind_axis<<endl;
	if(countour[0][*ind_axis] == 0){	// puede ser CONVEX o CLOSED
		if(countour[num_ver-1][*ind_axis] == 0)	topol = CLOSED;
		else	topol = CONVEX;
	}
	else{	// puede ser CONCAVE o HOLLOW
		if(countour[num_ver-1][*ind_axis] == 0)	topol = CONVEX;
		else	topol = HOLLOW;
	}
	return topol;
}


//~ pre	pla	ind	+	3-(+)
//~ 0	1	2	1		0
//~ 1	0	2	1		0
//~ 0	2	1	2		1
//~ 2	0	1	2		1
//~ 1	2	0	3		0
//~ 2	1	0	3		0

void RevolutionModel::change_plane(Tuple3r *countour, int num_ver, int pre_plane, int plane, int axis){
	//~ int ind_plane = 3-pre_plane+plane;
	
	//~ Tuple3r val;
	//~ val[0] = 0.0f; val[1] = 0.0f; val[2] = 0.0f;
	cout<<"CAMBIAR DE PLANO "<<pre_plane<<" A PLANO "<<plane<<" CON EJE DE ROTACIÓN "<<axis<<endl;
	
	//~ plano Z
	//~ eje Y
	//~ x1 y1 z1
	//~ x2 y2 z2
	//~ x3 y3 z3
	//~ x1 y1 0
	//~ x2 y2 0
	//~ x3 y3 0
	
	
	//~ plano Y
	//~ eje X
	//~ ? 0 ?
	//~ ? 0 ?
	//~ ? 0 ?
	
	int ind_axis = 3-(plane+axis);
	cout<<"pre_plane="<<pre_plane<<" plane = "<<plane<<", axis="<<axis<<", ind_axis="<<ind_axis<<endl;
	float val;
	for(int i=0; i<num_ver; i++){
		cout<<"el vertice era x="<<countour[i][X]<<", y="<<countour[i][Y]<<", z="<<countour[i][Z]<<endl;
		//~ val = countour[i][ind_axis];
		//~ countour[i][ind_axis] = countour[i][axis];
		//~ countour[i][axis] = val;
		countour[i][pre_plane] = countour[i][axis];
		countour[i][axis] = countour[i][plane];
		countour[i][plane] = 0.0f;
		cout<<"el vertice ES x="<<countour[i][X]<<", y="<<countour[i][Y]<<", z="<<countour[i][Z]<<endl;
	}
	//~ for(int i=0; i<num_ver; i++){
		//~ val = countour[i][pre_plane];
		//~ countour[i][pre_plane] = countour[i][plane];
		//~ countour[i][plane] = val;
	//~ }
}

int RevolutionModel::getPlane(){	return plane;}

int RevolutionModel::getAxis(){	return axis;}

int RevolutionModel::getRevolutions(){	return revolutions;}

//~ void PlyModel::arrange(vector<float> ver, vector<int> tri){
	//~ mesh->num_ver = ver.size()/3;
	//~ mesh->num_tri = tri.size()/3;
	//~ mesh->vertices = (Tuple3r*) malloc((mesh->num_ver)*sizeof(Tuple3r));
	//~ mesh->triangles = (Tuple3n*) malloc((mesh->num_tri)*sizeof(Tuple3n));
	
	//~ for(int i=0; i<mesh->num_ver; i++){
		//~ mesh->vertices[i][X] = ver[i*3];
		//~ mesh->vertices[i][Y] = ver[i*3+1];
		//~ mesh->vertices[i][Z] = ver[i*3+2];
	//~ }
	//~ for(int i=0; i<mesh->num_tri; i++){
		//~ mesh->triangles[i][0] = tri[i*3];
		//~ mesh->triangles[i][1] = tri[i*3+1];
		//~ mesh->triangles[i][2] = tri[i*3+2];
	//~ }
//~ }
