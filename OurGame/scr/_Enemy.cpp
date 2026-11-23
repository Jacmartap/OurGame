#include "_Enemy.h"

_Enemy::_Enemy()
{
	pos.x = 0.0;
	pos.y = 0.0;
	pos.z = 0.0;

	eSize.x = 1.0;
	eSize.y = 1.0;
	eSize.z = 1.0;

	rot.x = 0.0;
	rot.y = 0.0;
	rot.z = 0.0;
}

_Enemy::~_Enemy()
{

}

void _Enemy::initEnms(const char* filename, const char* skin, int trigger)
{
	myTex[trigger].loadTexture(skin);
	
	Enms[trigger].modelInit(filename, myTex[trigger].tex);
}

void _Enemy::update(float deltaT, vec3& pos, vec3& playerPos)
{

}

void _Enemy::drawEnms(float deltaT)
{
	glTranslatef(pos.x, pos.y, pos.z);

	glRotatef(rot.x, 1.0, 0.0, 0.0);
	glRotatef(rot.y, 0.0, 1.0, 0.0);
	glRotatef(rot.z, 0.0, 0.0, 1.0);

	glScalef(eSize.x, eSize.y, eSize.z);

	Enms[actionTrigger].display(deltaT);
}