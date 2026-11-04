#pragma once

#include <_Common.h>
#include <SOIL.h>

class _TxtLoader
{
public:
	  _TxtLoader();
	  ~_TxtLoader();

	  int width, height;     // keep image width & height
	  unsigned char* image;  // to store image data
	  GLuint tex;

	  void loadTexture(const char*);
	  void texBinder();

private:

protected:

};

