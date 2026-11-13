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

_Model::_Model(float posX, float posY, float posZ, float sclX, float sclY, float sclZ, float rotX, float rotY, float rotZ, float colR, float colG, float colB, float colA)
{
	pos.x = posX;
	pos.y = posY;
	pos.z = posZ;

	scale.x = sclX;
	scale.y = sclY;
	scale.z = sclZ;

	rotate.x = rotX;
	rotate.y = rotY;
	rotate.z = rotZ;

	color.r = colR;
	color.g = colB;
	color.b = colG;
	color.a = colA;
}

_Model::~_Model()
{}

void _Model::initModel(const char* fileName)
{
	myTex->loadTexture(fileName);
}

void _Model::drawModel()   // To draw cubes
{
	glPushMatrix();
	
	myTex->texBinder();
	
	glColor4f(color.r, color.g, color.b, color.a);
	
	glTranslatef(pos.x, pos.y, pos.z);
	
	glRotatef(rotate.x, 1, 0, 0);
	glRotatef(rotate.y, 0, 1, 0);
	glRotatef(rotate.z, 0, 0, 1);
	
	glScalef(scale.x, scale.y, scale.z);

	glBegin(GL_QUADS);


	// Front Face
	
	glTexCoord2f(0, 0);
	glVertex3f(-1.0, -1.0, 1.0);
	
	glTexCoord2f(1, 0);
	glVertex3f(1.0, -1.0, 1.0);
	
	glTexCoord2f(1, 1);
	glVertex3f(1.0, 1.0, 1.0);
	
	glTexCoord2f(0, 1);
	glVertex3f(-1.0, 1.0, 1.0);


	// Back Face
	
	glTexCoord2f(0, 0);
	glVertex3f(1.0, -1.0, -1.0);

	glTexCoord2f(1, 0);
	glVertex3f(-1.0, -1.0, -1.0);

	glTexCoord2f(1, 1);
	glVertex3f(-1.0, 1.0, -1.0);

	glTexCoord2f(0, 1);
	glVertex3f(1.0, 1.0, -1.0);


	// Top Face

	glTexCoord2f(0, 0);
	glVertex3f(-1.0, 1.0, 1.0);

	glTexCoord2f(1, 0);
	glVertex3f(1.0, 1.0, 1.0);

	glTexCoord2f(1, 1);
	glVertex3f(1.0, 1.0, -1.0);

	glTexCoord2f(0, 1);
	glVertex3f(-1.0, 1.0, -1.0);


	// Bottom Face

	glTexCoord2f(0, 0);
	glVertex3f(-1.0, -1.0, -1.0);

	glTexCoord2f(1, 0);
	glVertex3f(1.0, -1.0, -1.0);

	glTexCoord2f(1, 1);
	glVertex3f(1.0, -1.0, 1.0);

	glTexCoord2f(0, 1);
	glVertex3f(-1.0, -1.0, 1.0);


	// Right Face

	glTexCoord2f(0, 0);
	glVertex3f(1.0, -1.0, 1.0);

	glTexCoord2f(1, 0);
	glVertex3f(1.0, -1.0, -1.0);

	glTexCoord2f(1, 1);
	glVertex3f(1.0, 1.0, -1.0);

	glTexCoord2f(0, 1);
	glVertex3f(1.0, 1.0, 1.0);
	

	// Left Face
	
	glTexCoord2f(0, 0);
	glVertex3f(-1.0, -1.0, -1.0);

	glTexCoord2f(1, 0);
	glVertex3f(-1.0, -1.0, 1.0);

	glTexCoord2f(1, 1);
	glVertex3f(-1.0, 1.0, 1.0);

	glTexCoord2f(0, 1);
	glVertex3f(-1.0, 1.0, -1.0);
	
	glEnd();

	glPopMatrix();

}
