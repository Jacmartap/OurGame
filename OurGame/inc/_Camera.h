#pragma once

#include <_Common.h>

class _Camera
{
public:

	_Camera();
	~_Camera();

	vec3 eye;  // camera location
	vec3 des;  // where you looking at
	vec3 up;   // Head orientation

	float step; // speed of movement
	vec3 rot;   // rotate camera
	float distance; // distance from camera to the viwing point

	void camInit();
	void camReset();

	void rotateXY();
	void rotateUD();
	void MvFdBd(int dir, float deltaT);
	void MvLtRt(int dir, float deltaT);

	void SetupCam();


protected:

private:
};

