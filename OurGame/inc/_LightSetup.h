#pragma once
#include <_Common.h>

class _LightSetup
{
public:

	_LightSetup();
	~_LightSetup();

	const float Light_Ambient[4] = { 0.4, 0.4, 0.4, 1.0 };
	const float Light_Diffuse[4] = { 1.0, 1.4, 1.4, 1.0 };
	const float Light_Specular[4] = { 1.0, 1.0, 1.0, 1.0 };
	const float Light_Position[4] = { 1.0, 2.4, 7.4, 1.0 };

	const float Matte_Diffuse[4] = { 1.0, 1.4, 1.4, 1.0 };
	const float Matte_Specular[4] = { 1.0, 1.0, 1.0, 1.0 };
	const float Matte_Ambient[4] = { 1.0, 2.4, 7.4, 1.0 };

	const float High_Shininess[2] = { 100, 0.0 };

	void setLight(GLenum);
	
	void moveLight(float); // Pass Timer
	
	float angle = 0;
	float timer = 0;
	
	GLenum light0;         // Default Light
};

