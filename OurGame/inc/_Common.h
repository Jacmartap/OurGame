#pragma once

#include<GL/glew.h>
#include<Windows.h>
#include<iostream>
#include<gl/GL.h>
#include<time.h>
#include<math.h>
#include <stdlib.h>
#include<SOIL.h>
#include<SNDS/irrKlang.h>

#pragma comment(lib, "irrKlang.lib")

#define PI 3.14159
#define GLEW_STATIC

using namespace irrklang;

typedef struct {
	GLdouble x;
	GLdouble y;
	GLdouble z;
}vec3;

typedef struct {
	float x;
	float y;
}vec2;

typedef struct {
	float r;
	float g;
	float b;
	float a;
}col4;

using namespace std;
