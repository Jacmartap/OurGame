#pragma once

#include <_Common.h>
#include <cctype>
#include <unordered_map>
#include <vector>
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <_TxtLoader.h>
#include <algorithm>

#ifndef max
#define max(a,b) (((a) > (b)) ? (a) : (b))
#endif
#ifndef min
#define min(a,b) (((a) < (b)) ? (a) : (b))
#endif

// Structure to track VBO IDs for each loaded mesh
struct MeshVBO {
    unsigned int vboVertices;
    unsigned int vboNormals;
    unsigned int vboTexCoords;
    unsigned int eboIndices;
    unsigned int numIndices;
    bool hasTexCoords;
    bool hasNormals;
};

class _Anim3D
{
public:
    _Anim3D();
    ~_Anim3D();

    void modelInit(const char* fileName, GLuint ID);
    void evaluateBones(const aiAnimation* anim, const aiNode* nd, const aiMatrix4x4& parentTransform);
    void recursive_render(const aiScene* sc, const aiNode* nd, int specificFrame = -1);
    void display(float deltaT);

    GLuint texID;

private:
    const aiScene* scene;
    _TxtLoader* myTex;

    float timer;
    float angle;

    float currentAnimTime;
    int currentAnimIndex;

    // Stores the current frame's global transformation for each bone
    std::unordered_map<std::string, aiMatrix4x4> boneTransforms;
    aiVector3D modelCenter;
    float modelScale;

    // VBO storage mapped 1:1 with scene->mMeshes
    std::vector<MeshVBO> meshVBOs;
};