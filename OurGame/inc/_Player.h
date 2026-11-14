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
	void initPlayer(const char* filename, const char* skin, const char* exoSkin, int trigger); // Player initialization overloading for extra model textures - Kyle
	void drawPlayer(float);
	int ActionTrigger = 0;

	_Anim3D myPlayer[4];
	_TxtLoader myTex[4];
	_TxtLoader myExoTex[4];

	enum {IDLE, RUN, PUNCH, DEFEAT};

	vec3 pos;
	vec3 rot;   // Tracks rotation - Jacob
	vec3 scale;
	bool isLive = true;
};

