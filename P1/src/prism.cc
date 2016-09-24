#include "prism.h"

using namespace std;

class Prism: public Model{
protected:
	mesh_struct *mesh;
public:
	virtual Prism();
	virtual ~Prism();
	virtual draw(_render_mode mode, colorf color1, colorf color2 = NULL, int width = 0);
};
