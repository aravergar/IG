#ifndef _PYRAMID_H
#define _PYRAMID_H

#include <GL/gl.h>
#include <GL/glut.h>
#include "model.h"

using namespace std;

// Class Prism
//
// Define un objeto 3D con forma piramidal a partir de 3 parámetros:
// * radio (distancia entre una esquina y el centro proyectado en base
// * altura (distancia desde la base hasta el vértice)
// * número de caras (a partir de 3)
// Por tanto, una pirámide de número de caras muy alto puede equivaler
//   a un cono, puesto que su base parecerá un círculo
class Pyramid: public Model{
protected:
	float height, radius;
	int faces;
	Tuple3n* alternate(bool alternate_A);
public:
	Pyramid(float height = 100.0f, float radius = 40.0f, int faces = 3);
	~Pyramid();
	void draw(_render_mode mode, Color3r color1, Color3r color2 = NULL, int width = 0);
};

#endif
