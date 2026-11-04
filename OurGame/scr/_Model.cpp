#include "_Model.h"

_Model::_Model()
{
	pos.x = 0.0;
	pos.y = 0.0;
	pos.z = -8.0;

	scale.x = scale.y = scale.z = 1.0;
	rotate.x = rotate.y = rotate.z = 0.0;

	color.r = 1.0;
	color.g = 1.0;
	color.b = 1.0;
	color.a = 1.0;

}

_Model::~_Model()
{}

void _Model::initModel(const char* fileName)
{
	myTex->loadTexture(fileName);
}

void _Model::drawModel()
{
	glPushMatrix();
	
	myTex->texBinder();
	
	glColor4f(color.r, color.g, color.b, color.a);
	
	glTranslatef(pos.x, pos.y, pos.z);
	
	glRotatef(rotate.x, 1, 0, 0);
	glRotatef(rotate.y, 0, 1, 0);
	glRotatef(rotate.z, 0, 0, 1);
	
	glScalef(scale.x, scale.y, scale.z);

	//glutSolidTeapot(2.0);

	glPopMatrix();

}
