#pragma once
#include <_Common.h>
#include <_TxtLoader.h>
#include <_Anim3D.h>
#include <_Sounds.h>

class _Player
{
public:
	_Player();
	~_Player();

	void initPlayer(const char* filename, const char* skin, int trigger);
	void initPlayer(const char* filename, const char* skin, const char* exoSkin, int trigger); // Player initialization overloading for extra model textures - Kyle
	void drawPlayer(float);

	// Action management - Kyle
	// Note: triggerAction(action name, animation duration time) instead of using ActionTrigger now
	// Surround it in a if (!mdl->isActionActive) to prevent other actions from interfering
	
	void triggerAction(int action, float duration);
	void updateAction(float deltaT);
	void setMovementAction(int action);

	int ActionTrigger = 0;			// Currently selected animation

	float ActionTimer = 0.0f;		// Time remaining for current action
	float ActionDuration = 0.0f;	// Original duration of the action
	bool isActionActive = false;	// Prevents movement animations from stopping an action

	enum { IDLE, RUN, PUNCH, DEFEAT };
	//

	_Anim3D myPlayer[4];
	_TxtLoader myTex[4];
	_TxtLoader myExoTex[4];

	_Sounds* playerSounds = new _Sounds();

	vec3 pos;
	vec3 rot;   // Tracks rotation - Jacob
	vec3 scale;
	bool isLive = true;
};

