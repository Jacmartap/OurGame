#include "_Player.h"

_Player::_Player()
{
	pos.x = 0.0;
	pos.y = 0.0;
	pos.z = 0.0;
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
	myPlayer[ActionTrigger].display(deltaT);
}
