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

RevolutionModel::RevolutionModel(Tuple3r *countour){
	
}

RevolutionModel::RevolutionModel(char *file){
	//~ _file_ply ply_f;
	
	//~ mesh = new Mesh();
	
	//~ vector<float> ply_ver;
	//~ vector<int> ply_tri;
	
	//~ ply_f._file_ply::open(file);
	//~ ply_f._file_ply::read(ply_ver, ply_tri);
	//~ cout<<"el tamanyo de ver es "<<ply_ver.size()<<"\n";
	//~ cout<<"el tamanyo de tri es "<<ply_tri.size()<<"\n";

	//~ arrange(ply_ver, ply_tri);
	//~ ply_f._file_ply::close();
}

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
