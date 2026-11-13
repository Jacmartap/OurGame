#pragma once

#include <_Common.h>
#include <_Anim3D.h>
#include <_TxtLoader.h>

#define numActions 5

class _Enemy
{
public:
	_Enemy();
	~_Enemy();

	void initEnms(const char*, const char*, int); // Model Path, Skin Path Trigger
	void update(float, vec3&, vec3&);		  // Timer, Pos, Player Pos
	void drawEnms(float);						  // Timer

	_Anim3D Enms[numActions];
	_TxtLoader myTex[numActions];

	enum EnemyState {IDLE, RUN, ATTACK, DIE};

	vec3 pos;	// Position
	vec3 eSize; // Size
		
	bool active = false;

	EnemyState actionTrigger = IDLE;
};

