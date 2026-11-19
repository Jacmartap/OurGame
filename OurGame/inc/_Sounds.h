#pragma once
#include <_Common.h>

class _Sounds
{
public:
	_Sounds();
	~_Sounds();

	ISoundEngine* engine = createIrrKlangDevice();

	void initSnds();
	void playMusic(const char*);
	void playSnd(const char*);
	void pauseSnds(const char*);
	void stopMusic(const char*);
};

