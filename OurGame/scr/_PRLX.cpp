#include "_PRLX.h"

_PRLX::_PRLX()
{
	xMin = 0.0;
	yMin = 0.0;
	xMax = 1.0;
	yMax = 1.0;
}

_PRLX::~_PRLX()
{}

void _PRLX::drawBkGrnd(float width, float height)
{
	bTex->texBinder();

	glDisable(GL_LIGHTING);

	glBegin(GL_POLYGON);
	glTexCoord2f(xMin, yMax);
	glVertex3f(-width / height, -1, -10);

	glTexCoord2f(xMax, yMax);
	glVertex3f(width / height, -1, -10);

	glTexCoord2f(xMax, yMin);
	glVertex3f(width / height, 1, -10);

	glTexCoord2f(xMin, yMin);
	glVertex3f(-width / height, 1, -10);

	glEnd();

	glEnable(GL_LIGHTING);
}

void _PRLX::initPRLX(const char* fileName)
{

	bTex->loadTexture(fileName);

}

void _PRLX::scrollPRLX(bool Auto, string dir, float speed, float delta)
{
	timer += delta;

	if (Auto && timer > 0.01)
	{
		if (dir == "left")
		{
			xMin += speed;
			xMax += speed;
		}

		if (dir == "right")
		{
			xMin -= speed;
			xMax -= speed;
		}

		if (dir == "forward")
		{
			yMin -= speed;
			yMax -= speed;
		}

		if (dir == "backward")
		{
			yMin += speed;
			yMax += speed;
		}

		timer = 0;
	}
}
