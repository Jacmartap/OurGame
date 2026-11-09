#include "_SkyBox.h"

_SkyBox::_SkyBox()
{
	rot.x = rot.y = rot.z = 0;
	scale.x = scale.y = scale.z = 50.0;
	pos.x = pos.y = 0;
	pos.z = -8;

}

_SkyBox::~_SkyBox()
{}

void _SkyBox::initSkyBox()
{
	glGenBuffers(1, &vboVert);
	glBindBuffer(GL_ARRAY_BUFFER, vboVert);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &vboNorm);
	glBindBuffer(GL_ARRAY_BUFFER, vboNorm);
	glBufferData(GL_ARRAY_BUFFER, sizeof(normals), normals, GL_STATIC_DRAW);

	glGenBuffers(1, &vboTex);
	glBindBuffer(GL_ARRAY_BUFFER, vboTex);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_STATIC_DRAW);

	glGenBuffers(1, &eboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,eboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void _SkyBox::drawSkyBox()
{
	glDisable(GL_LIGHTING);
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(pos.x, pos.y, pos.z);

	glRotatef(rot.x, 1, 0, 0);
	glRotatef(rot.y, 0, 1, 0);
	glRotatef(rot.z, 0, 0, 1);

	glScalef(scale.x, scale.y, scale.z);

	glEnableClientState(GL_VERTEX_ARRAY); // activate vertex buffer
	glEnableClientState(GL_NORMAL_ARRAY); // activate normal buffer
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);// activate text coord buffer

	glBindBuffer(GL_ARRAY_BUFFER, vboTex);        // set tex pointer
	glTexCoordPointer(2, GL_FLOAT, 0, (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, vboNorm);       // normal pointer
	glNormalPointer(GL_FLOAT, 0, (void*)0);       // Safely cast to (void*)0

	glBindBuffer(GL_ARRAY_BUFFER, vboVert);       // set vertex pointer
	glVertexPointer(3, GL_FLOAT, 0, (void*)0);    // Safely cast to (void*)0

	// FIX: Bind the Element Buffer Object before calling glDrawElements
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);

	myTex[0].texBinder();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0); // front face

	myTex[1].texBinder();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(6 * sizeof(unsigned int))); //back face

	myTex[2].texBinder();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(12 * sizeof(unsigned int)));//top face

	myTex[3].texBinder();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(18 * sizeof(unsigned int)));//bottom face

	myTex[4].texBinder();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(24 * sizeof(unsigned int)));//left face

	myTex[5].texBinder();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(30 * sizeof(unsigned int)));//right face

	glDisableClientState(GL_VERTEX_ARRAY); // deactivate vertex buffer
	glDisableClientState(GL_NORMAL_ARRAY); // deactivate normal buffer
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);// deactivate text coord buffer

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glPopMatrix();
	glEnable(GL_LIGHTING);
}
