#pragma once

#include <_Common.h>
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <_TxtLoader.h>

class _ModelLoader
{
public:
	const aiScene* scene = nullptr;
	
	float angle = 0.0f;
	float timer = 0;

	_TxtLoader* myTex = new _TxtLoader();

	_ModelLoader();
	~_ModelLoader();
	
	void modelInit(const char*, const char*);
	void modelInit(const char*, GLuint, GLuint);				// Overloading modelinit for extra player textures - Kyle
	void recursive_render(const aiScene* sc, const aiNode* nd);
	void display(float);
};

