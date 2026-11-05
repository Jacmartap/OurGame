#pragma once

#include <_Common.h>
#include <_TxtLoader.h>

class _PRLX
{
public:
	_PRLX();
	~_PRLX();

	void drawBkGrnd(float, float);						// Draw : pass width and height
	void initPRLX(const char*);							// Load with file Name
	void scrollPRLX(bool Auto,string, float, float);	// Pass direction to scroll, speed, time

    _TxtLoader* bTex = new _TxtLoader();
	
	float xMin, xMax, yMin, yMax;
	float speed = 0.005;
	float timer = 0;
};

