#include "_Player.h"

_Player::_Player()
{
	pos.x = 0.0;
	pos.y = -2.0;
	pos.z = 0.0;

	rot.x = 0.0;   // Initaializing rotation - Jacob
	rot.y = 0.0;   //
	rot.z = 0.0;   //
}

_Player::~_Player()
{

}

void _Player::initPlayer(const char* filename, const char* skin, int trigger)
{
	myTex[trigger].loadTexture(skin);
	myPlayer[trigger].modelInit(filename, myTex[trigger].tex);
}

void _Player::drawPlayer(float deltaT)
{
	glTranslatef(pos.x, pos.y, pos.z);

	glRotatef(rot.x, 1.0, 0.0, 0.0);   // Rotation is now part of drawing the player - Jacob
	glRotatef(rot.y, 0.0, 1.0, 0.0);   //
	glRotatef(rot.z, 0.0, 0.0, 1.0);   //

	myPlayer[ActionTrigger].display(deltaT);
}
