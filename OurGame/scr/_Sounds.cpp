#include "_Sounds.h"

_Sounds::_Sounds()
{}

_Sounds::~_Sounds()
{
	engine->drop();
}

void _Sounds::initSnds()
{
	if (!engine)
	{
		cout << "Could not setup engine sounds" << endl;
	}
}

void _Sounds::playMusic(const char* filename)
{
	engine->play2D(filename, true);
}

void _Sounds::playSnd(const char* filename)
{
	engine->play2D(filename, false, false);
}

void _Sounds::pauseSnds(const char* filename)
{
	engine->play2D(filename, true, false);
}

void _Sounds::stopMusic(const char*)
{}
