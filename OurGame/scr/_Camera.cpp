#include "_Camera.h"

_Camera::_Camera() {};

_Camera::~_Camera() {};

void _Camera::camInit()
{
	eye.x = 0;
	eye.y = 2;   // Shifted values a bit - Jacob
	eye.z = 6;   //
	
	des.x = 0;
	des.y = 0;
	des.z = 0;
	
	up.x = 0;
	up.y = 1;
	up.z = 0;
	
	step = 0.5;
	
	rot.x = 0;
	rot.y = 0;
	rot.z = 0;

	//distance = sqrt(pow((des.x - eye.x), 2) + pow((des.x - eye.x), 2) + pow((des.y - eye.y), 2) + pow((des.z - eye.z), 2));





	distance = sqrt(pow(des.x - eye.x, 2) + pow(des.y - eye.y, 2) + pow(des.z - eye.z, 2));
}

void _Camera::camReset()
{
	eye.x = 0;
	eye.y = 0;
	eye.z = 10;
	
	des.x = 0;
	des.y = 0;
	des.z = 0;
	
	up.x = 0;
	up.y = 1;
	up.z = 0;
	
	step = 0.5;

	rot.x = 0;
	rot.y = 0;
	rot.z = 0;
	
	//distance = sqrt(pow((des.x - eye.x), 2) + pow((des.x - eye.x), 2) + pow((des.y - eye.y), 2) + pow((des.z - eye.z), 2));




	distance = sqrt(pow(des.x - eye.x, 2) + pow(des.y - eye.y, 2) + pow(des.z - eye.z, 2));
}

void _Camera::rotateXY()
{
	eye.x = des.x + distance * cos(rot.y * PI / 180.0) * sin(rot.x * PI / 180.0);
	eye.y = des.y + distance * sin(rot.y * PI / 180.0);
	eye.z = des.z + distance * cos(rot.y * PI / 180.0) * cos(rot.x * PI / 180.0);
}

void _Camera::rotateUD()
{


}

void _Camera::MvFdBd(int dir, float deltaT)
{
	eye.z += dir * deltaT;
	des.z += dir * deltaT;
}

void _Camera::MvLtRt(int dir, float deltaT)
{
	eye.x += dir * deltaT;
	des.x += dir * deltaT;
}

void _Camera::SetupCam()
{
	gluLookAt(eye.x, eye.y, eye.z, des.x, des.y, des.z, up.x, up.y, up.z);

}
