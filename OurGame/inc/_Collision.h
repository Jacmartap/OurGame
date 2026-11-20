#pragma once
#include<_Common.h>
#include<_Player.h>
#include<_Model.h>

class _Collision
{
public:
	_Collision();
	~_Collision();

	bool isLinearCollision(vec2, vec2);  // linear comparison
	bool isHitplane(vec3, vec3);         // object with plane
	bool isRadialCollion(vec3, vec3, float, float, float);  //src,des,r1,r2,threshold

	bool isCubicCollision(_Player*, _Model*);
	bool isSphereCollision(vec3, vec3, float, float, float);//src,des,r1,r2,threshold
};

