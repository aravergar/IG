#include <cstdio>
#include <iostream>
#include <GL/gl.h>
    #include <GL/glut.h>
#include "escena.h"

Escena::Escena(){
    Front_plane=50;
    Back_plane=2000;
    Observer_distance = 4*Front_plane;
    Observer_angle_x = Observer_angle_y=0;
    
}

void Escena::inicializar(int UI_window_width,int UI_window_height) {

cout<<"VOY A CREAR UNA PIRAMIDE\n";
    tetra = new Tetrahedron(100);
    cube = new Cube(100);
    torus = new Torus();
    char* file_name = (char*)"beethoven.ply";
    ply_model = new PlyModel(file_name);
    char* rev_file_name = (char*)"perfil.ply";
    rev_model = new RevolutionModel(rev_file_name, 10, X);
    cout<<"?"<<endl;
    rev_model->test();
    cout<<"?"<<endl;
    object = tetra;
    mode = VERTICES;
    cout<<"HA IDO BIEN\n";

	glClearColor(1,1,1,1);// se indica cual sera el color para limpiar la ventana	(r,v,a,al)

	glEnable(GL_DEPTH_TEST);	// se habilita el z-bufer

	this->change_projection();
	Width=UI_window_width/10;
	Height=UI_window_height/10;
	glViewport(0,0,UI_window_width,UI_window_height);

}


//**************************************************************************
// Funcion que dibuja objetos en la escena
//***************************************************************************
void Escena::draw_objects() {
    //~ tetra->draw();
    Color3r color1= {1.0f, 0.0f, 0.0f};
    Color3r color2= {0.0f, 1.0f, 0.0f};
    
    object->draw(mode, color1, color2, 2);
    
    //~ tetra->draw(mode, color1, NULL, 2);
    //~ tetra->draw(EDGES, color1, NULL, 2);
    //~ tetra->draw(SOLID, color1, NULL, 2);
    //~ tetra->draw(CHECKERED, color1, color2, 2);
    
    //~ cube->draw(VERTICES, color1, NULL, 2);
    //~ cube->draw(EDGES, color1, NULL, 2);
    //~ cube->draw(SOLID, color1, NULL, 2);
    //~ cube->draw(CHECKERED, color1, color2, 2);
}



void Escena::dibujar() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
	change_observer();
	draw_axis();
	draw_objects();
}

int Escena::teclaPulsada(unsigned char Tecla1,int x,int y) {

    std::cout << "Tecla "<< Tecla1<< std::endl;
    switch(Tecla1){
	case '1':
		object = tetra;
		break;
	case '2':
		object = cube;
		break;
	case '3':
		object = torus;
		break;
	case '4':
		break;
	case '5':
		object = ply_model;
		break;
	case '6':
		object = rev_model;
		object->test();
		rev_model->test();
		break;
	}
	if (toupper(Tecla1)=='Q') return 1;
	else return 0;
}

void Escena::teclaEspecial(int Tecla1,int x,int y) {
switch (Tecla1){
	case GLUT_KEY_LEFT:Observer_angle_y--;break;
	case GLUT_KEY_RIGHT:Observer_angle_y++;break;
	case GLUT_KEY_UP:Observer_angle_x--;break;
	case GLUT_KEY_DOWN:Observer_angle_x++;break;
	case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
	case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;
	
	case GLUT_KEY_F1:mode=VERTICES;break;
	case GLUT_KEY_F2:mode=EDGES;break;
	case GLUT_KEY_F3:mode=SOLID;break;
	case GLUT_KEY_F4:mode=CHECKERED;break;
	}

	std::cout << Observer_distance << std::endl;
}


//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void Escena::change_projection()  {
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glFrustum(-Width,Width,-Height,Height,Front_plane,Back_plane);
}


void Escena::redimensionar(int newWidth,int newHeight) {
change_projection();
Width=newWidth/10;
Height=newHeight/10;
glViewport(0,0,newWidth,newHeight);
}


//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************



void Escena::change_observer() {

// posicion del observador
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glTranslatef(0,0,-Observer_distance);
glRotatef(Observer_angle_x,1,0,0);
glRotatef(Observer_angle_y,0,1,0);
}


//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void Escena::draw_axis()
{
glLineWidth(1);
glBegin(GL_LINES);
// eje X, color rojo
glColor3f(1,0,0);
glVertex3f(-AXIS_SIZE,0,0);
glVertex3f(AXIS_SIZE,0,0);
// eje Y, color verde
glColor3f(0,1,0);
glVertex3f(0,-AXIS_SIZE,0);
glVertex3f(0,AXIS_SIZE,0);
// eje Z, color azul
glColor3f(0,0,1);
glVertex3f(0,0,-AXIS_SIZE);
glVertex3f(0,0,AXIS_SIZE);
glEnd();
}




