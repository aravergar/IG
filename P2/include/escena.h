#ifndef _ESCENA_H
#define _ESCENA_H

#include "aux_definitions.h"
//~ #include "pyramid.h"
#include "tetrahedron.h"
//~ #include "prism.h"
#include "cube.h"
#include "torus.h"
#include "ply_model.h"
#include "revolution_model.h"

class Escena {
private:
// tamaño de los ejes
const static int AXIS_SIZE=5000;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Width,Height,Front_plane,Back_plane;

Pyramid *pyramid;
Tetrahedron *tetra;
Cube *cube;
Torus *torus;
PlyModel *ply_model;
RevolutionModel *rev_model;
int number_edges = 10;
int plane = 2;
int axis = 1;

char* rev_file_name = (char*)"perfil.ply";
char* file_name = (char*)"beethoven.ply";

Model *object;

_render_mode mode;

private:
	void clear_window();
	void draw_axis();
	void draw_objects();

//Transformación de cámara
	void change_projection();
	void change_observer();


public:
     Escena();
	void inicializar(int UI_window_width,int UI_window_height);
	void redimensionar(int newWidth,int newHeight) ;

	// Dibujar
	void dibujar() ;

	// Interacción con la escena
	int teclaPulsada(unsigned char Tecla1,int x,int y) ;
	void teclaEspecial(int Tecla1,int x,int y);
};
#endif
