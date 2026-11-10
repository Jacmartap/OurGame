#include <_KbMs.h>

_KbMs::_KbMs()
{

	isMsTranslate = false;
	isMsRotate = false;
}
 
_KbMs::~_KbMs(){}

void _KbMs::keyPressed(_Model* mdl)
{
	switch (wparam)
	{
	case VK_LEFT:
		mdl->rotate.y += 1.0;
		break;
	
	case VK_RIGHT:
		mdl->rotate.y -= 1.0;
		break;
	
	case VK_UP:
		mdl->rotate.x += 1.0;
		break;
	
	case VK_DOWN:
		mdl->rotate.x -= 1.0;
		break;
	
	default:
		break;

	}
}

void _KbMs::keyPressed(_SkyBox* sky)
{
	switch (wparam)
	{
	case VK_LEFT:
		sky->rot.y += 1.0;
		break;
	
	case VK_RIGHT:
		sky->rot.y -= 1.0;
		break;
	
	case VK_UP:
		sky->rot.x += 1.0;
		break;
	
	case VK_DOWN:
		sky->rot.x -= 1.0;
		break;
	
	default:
		break;
	}
}

/*void _KbMs::keyPressed(_Camera* cm)     // Ignoring this variant of the camera rotation for now - Jacob
{
	switch (wparam)
	{
	case 0x57: //w
		cm->MvFdBd(-1);
		break;

	case 0x53: //s
		cm->MvFdBd(1);
		break;

	case 65: //a
		cm->MvLtRt(-1);
		break;

	case 68: //d
		cm->MvLtRt(1);
		break;

	case 73:  //i
		cm->rot.y -= 1;
		cm->rotateXY();
		break;
	
	case 74:  //j
		cm->rot.x += 1;
		cm->rotateXY();
		break;
	
	case 75:  //k
		cm->rot.y += 1;
		cm->rotateXY();
		break;
	
	case 76:  //l
		cm->rot.x -= 1;
		cm->rotateXY();
		break;

	case VK_SPACE:
		//cm->camReset();
		break;
	}

}*/

void _KbMs::keyPressed(_PRLX* prlx)
{
	switch (wparam)
	{
	case VK_LEFT:
		prlx->xMin += prlx->speed;
		prlx->xMax += prlx->speed;
		break;
	
	case VK_RIGHT:
		prlx->xMin -= prlx->speed;
		prlx->xMax -= prlx->speed;
		break;
	
	case VK_UP:
		prlx->yMin -= prlx->speed;
		prlx->yMax -= prlx->speed;
		break;
	
	case VK_DOWN:
		prlx->yMin += prlx->speed;
		prlx->yMax += prlx->speed;
		break;
	
	default:
		break;
	}

}

void _KbMs::keyPressed(_Player* mdl, _Camera* cm, float deltaT)   // New Version - Jacob
{
	float speed = 3.5;

	float yaw = cm->rot.x * PI / 180.0;

	float forwardX = -sin(yaw);
	float forwardZ = -cos(yaw);

	float rightX = cos(yaw);
	float rightZ = -sin(yaw);

	float xPos = 0;
	float zPos = 0;

	if (forward)
	{
		xPos += forwardX;
		zPos += forwardZ;
	}
	
	if (backward)
	{ 
		xPos -= forwardX;
		zPos -= forwardZ;
	}
	
	if (right)
	{
		xPos += rightX;
		zPos += rightZ;
	}
	
	if (left)
	{
		xPos -= rightX;
		zPos -= rightZ;
	}

	float length = sqrt(xPos * xPos + zPos * zPos);

	if (length > 0)
	{
		xPos /= length;
		zPos /= length;

		mdl->pos.x += xPos * speed * deltaT;
		mdl->pos.z += zPos * speed * deltaT;

		mdl->rot.y = atan2(xPos, zPos) * 180.0 / PI;

		mdl->ActionTrigger = mdl->RUN;
	}
	else
	{
		mdl->ActionTrigger = mdl->IDLE;
	}
}

void _KbMs::keyPressed(_Camera* cm, float deltaT)   // Old camera function kept the same - Jacob
{
	float speed = 3.5;

	if (forward)
	{
		cm->MvFdBd(-1, deltaT * speed);
	}

	if (right)
	{
		cm->MvLtRt(1, deltaT * speed);
	}

	if (backward)
	{
		cm->MvFdBd(1, deltaT * speed);
	}

	if (left)
	{
		cm->MvLtRt(-1, deltaT * speed);
	}

}

void _KbMs::keyUp(){
	switch (wparam)
	{
		default: break;
	}
}

void _KbMs::mouseEventDown(_Model* mdl, double x, double y)
{
	prevMx = x;
	prevMy = y;

	switch (wparam)
	{
	case MK_LBUTTON:
		isMsRotate = true;
		break;
	
	case MK_RBUTTON:
		isMsTranslate = true;
		break;
	
	case MK_MBUTTON:
		 break;
	
	default:
		break;
	}
}

void _KbMs::mouseEventDown(_Camera* cm, double x, double y)
{
	prevMx = x;
	prevMy = y;

	switch (wparam)
	{
	case MK_LBUTTON:
		isMsRotate = true;
		break;

	case MK_RBUTTON:
		isMsTranslate = true;
		break;

	case MK_MBUTTON:
		break;

	default:
		break;
	}
}

void _KbMs::mouseEventUp()
{

	isMsTranslate = false;
	isMsRotate = false;

}

void _KbMs::mouseMove(_Model* mdl, double x, double y) {
	if (isMsRotate)
	{

		mdl->rotate.y += (x - prevMx) / 3.0;
		mdl->rotate.x += (prevMy-y) / 3.0;
	}

	if (isMsTranslate)
	{

		mdl->pos.x += (x - prevMx) / 100.0;
		mdl->pos.y += (prevMy-y) / 100.0;
	}
	
	prevMx = x;
	prevMy = y;
}

void _KbMs::mouseWheel(_Model* mdl, double delta)
{
	mdl->pos.z += delta/ 100.0;
}

void _KbMs::mouseMove(_SkyBox* mdl, double x, double y)
{
	if (isMsRotate) {

		mdl->rot.y += (x - prevMx) / 3.0;
		mdl->rot.x += (prevMy - y) / 3.0;
	}

	if (isMsTranslate) {

		mdl->pos.x += (x - prevMx) / 100.0;
		mdl->pos.y += (prevMy - y) / 100.0;
	}
	
	prevMx = x;
	prevMy = y;
}

void _KbMs::mouseMove(_Camera* cm, double x, double y)
{
	if (isMsRotate) {
		cm->rot.x += (x - prevMx) / 10.0;
		cm->rot.y += (y - prevMy) / 10.0;

		if (cm->rot.y < 0)
		{
			cm->rot.y = 0;
		}

		if (cm->rot.y > 90)
		{
			cm->rot.y = 90;
		}

		cm->rotateXY();
	}

	prevMx = x;
	prevMy = y;
}
