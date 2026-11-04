#pragma once

#include <_Common.h>
#include <_TxtLoader.h>

class _Model
{
public:
	_Model();
	~_Model();

	vec3 pos; //use for possitioning the model
	vec3 rotate; //use for rotating the model
	vec3 scale;// use for scaling the model
	col4 color; // use for coloring the model

	_TxtLoader* myTex = new _TxtLoader();
	
	void initModel(const char*);
	void drawModel();
};

