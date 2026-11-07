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
	void keyPressed(_Player*, float&, float&);
	void keyUp();

	void mouseEventDown(_Model*, double, double);
	void mouseEventUp();

	void mouseMove(_Model*, double, double);
	void mouseWheel(_Model*, double);

	void mouseMove(_SkyBox*, double, double);

	double prevMx;
	double prevMy;

	bool isMsTranslate;
	bool isMsRotate;

	WPARAM wparam;

private:

protected:

};



