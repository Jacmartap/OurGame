#pragma once

#include <_Common.h>
#include <_Model.h>
#include <_SkyBox.h>
#include <_Camera.h>
#include <_PRLX.h>
#include <_Player.h>

class _KbMs
{
public:
	_KbMs();
	virtual ~_KbMs();

	void keyPressed(_Model *);
	void keyPressed(_SkyBox*);
	void keyPressed(_Camera*);
	void keyPressed(_PRLX*);
	void keyPressed(_Player*, float);   // Altered for movement - Jacob
	void keyPressed(_Camera* cm, float deltaT);   // Also Altered for movement - Jacob
	void keyUp();

	void mouseEventDown(_Model*, double, double);
	void mouseEventDown(_Camera*, double, double);
	void mouseEventUp();

	void mouseMove(_Model*, double, double);
	void mouseWheel(_Model*, double);

	void mouseMove(_SkyBox*, double, double);
	void mouseMove(_Camera*, double, double);

	double prevMx;
	double prevMy;

	bool isMsTranslate;
	bool isMsRotate;

	WPARAM wparam;

	bool up = false;		// New booleans to register movement - Jacob
	bool down = false;
	bool left = false;
	bool right = false;
	/*
	bool upLeft = false;
	bool upRight = false;
	bool downLeft = false;
	bool downRight = false;
	*/

private:

protected:

};



