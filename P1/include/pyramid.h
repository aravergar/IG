#ifndef _PYRAMID_H
#define _PYRAMID_H

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
class Prism: public Model{
protected:
	float height, radius;
	int faces;
public:
	Pyramid(height = 10.0f, radius = 4.0f, faces = 3);
	~Pyramid();
	draw(_render_mode mode, colorf color1, colorf color2 = NULL, int width = 0);
};

#endif
