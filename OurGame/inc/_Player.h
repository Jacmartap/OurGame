#pragma once
#include <_Common.h>
#include <_TxtLoader.h>
#include <_Anim3D.h>

class _Player
{
public:
	_Player();
	~_Player();

	void initPlayer(const char* filename, const char* skin, int trigger);
	void drawPlayer(float);
	int ActionTrigger = 0;

	_Anim3D myPlayer[5];
	_TxtLoader myTex[5];

	enum {IDLE, RUN, JUMP, CROUCH, CARTWHEEL};

	vec3 pos;
	vec3 rot;   // Tracks rotation - Jacob
	vec3 scale;
	bool isLive = true;
};

