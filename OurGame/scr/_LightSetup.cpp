#include "_LightSetup.h"

_LightSetup::_LightSetup()
{

}

_LightSetup::~_LightSetup()
{

}

void _LightSetup::setLight(GLenum light)
{
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	glEnable(GL_LIGHTING);
	glEnable(light);

	glLightfv(light, GL_AMBIENT, Light_Ambient);
	glLightfv(light, GL_DIFFUSE, Light_Diffuse);
	glLightfv(light, GL_SPECULAR, Light_Specular);
	glLightfv(light, GL_POSITION, Light_Position);
	
	glMaterialfv(GL_FRONT, GL_AMBIENT, Matte_Ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, Matte_Specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, Matte_Diffuse);

	glMaterialfv(GL_FRONT, GL_SHININESS, High_Shininess);

	light0 = light; // Keep A Copy Of Light
}

void _LightSetup::moveLight(float deltaT)
{
	timer += deltaT;

	if (timer > 0.05)
	{
		angle += 5.0;
		timer = 0;
	}
	
	glPushMatrix();

	glRotatef(angle, 0.0, 1.0, 0.0);

	glLightfv(light0, GL_POSITION, Light_Position);

	glPopMatrix();
}
