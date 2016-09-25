#ifndef _PRISM_H
#define _PRISM_H

#include "model.h"

using namespace std;

class Prism: public Model{
protected:
public:
	Prism();
	~Prism();
	void draw(_render_mode mode, colorf color1, colorf color2 = NULL, int width = 0);
};

#endif
