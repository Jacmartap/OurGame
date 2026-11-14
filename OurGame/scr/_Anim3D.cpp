#include "_Anim3D.h"
#include <iostream>

using namespace std;

_Anim3D::_Anim3D()
{
    currentAnimTime = 0.0f;
    currentAnimIndex = 0;
    timer = 0;
    angle = 0;
    myTex = new _TxtLoader();
    scene = nullptr;
}

_Anim3D::~_Anim3D()
{
    // Clean forward GPU memory
    for (auto& vbo : meshVBOs) {
        glDeleteBuffers(1, &vbo.vboVertices);
        if (vbo.hasNormals) glDeleteBuffers(1, &vbo.vboNormals);
        if (vbo.hasTexCoords) glDeleteBuffers(1, &vbo.vboTexCoords);
        glDeleteBuffers(1, &vbo.eboIndices);
    }

    if (scene) {
        aiReleaseImport(scene);
    }
    delete myTex;
}

void _Anim3D::modelInit(const char* fileName, GLuint ID) {
    scene = aiImportFile(fileName,
        aiProcess_Triangulate |
        aiProcess_GenSmoothNormals |
        aiProcess_FlipUVs |
        aiProcess_LimitBoneWeights);

    texID = ID;

    if (!scene) {
        std::cerr << "Error loading model: " << aiGetErrorString() << std::endl;
        return;
    }

    cout << "Model Loaded" << endl;

    // --- Generate VBOs for each Mesh ---
    meshVBOs.resize(scene->mNumMeshes);
    for (unsigned int m = 0; m < scene->mNumMeshes; ++m) {
        aiMesh* mesh = scene->mMeshes[m];
        MeshVBO& vbo = meshVBOs[m];

        // Vertices (GL_DYNAMIC_DRAW because CPU skinning updates them every frame)
        glGenBuffers(1, &vbo.vboVertices);
        glBindBuffer(GL_ARRAY_BUFFER, vbo.vboVertices);
        glBufferData(GL_ARRAY_BUFFER, mesh->mNumVertices * sizeof(aiVector3D), mesh->mVertices, GL_DYNAMIC_DRAW);

        // Normals (GL_DYNAMIC_DRAW)
        vbo.hasNormals = mesh->HasNormals();
        if (vbo.hasNormals) {
            glGenBuffers(1, &vbo.vboNormals);
            glBindBuffer(GL_ARRAY_BUFFER, vbo.vboNormals);
            glBufferData(GL_ARRAY_BUFFER, mesh->mNumVertices * sizeof(aiVector3D), mesh->mNormals, GL_DYNAMIC_DRAW);
        }

        // Texture Coordinates (GL_STATIC_DRAW since UVs rarely change)
        vbo.hasTexCoords = mesh->HasTextureCoords(0);
        if (vbo.hasTexCoords) {
            std::vector<float> texCoords;
            texCoords.reserve(mesh->mNumVertices * 2);
            for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
                texCoords.push_back(mesh->mTextureCoords[0][i].x);
                texCoords.push_back(mesh->mTextureCoords[0][i].y);
            }
            glGenBuffers(1, &vbo.vboTexCoords);
            glBindBuffer(GL_ARRAY_BUFFER, vbo.vboTexCoords);
            glBufferData(GL_ARRAY_BUFFER, texCoords.size() * sizeof(float), texCoords.data(), GL_STATIC_DRAW);
        }

        // Indices (GL_STATIC_DRAW)
        std::vector<unsigned int> indices;
        for (unsigned int t = 0; t < mesh->mNumFaces; ++t) {
            aiFace* face = &mesh->mFaces[t];
            for (unsigned int i = 0; i < face->mNumIndices; i++) {
                indices.push_back(face->mIndices[i]);
            }
        }
        vbo.numIndices = indices.size();
        glGenBuffers(1, &vbo.eboIndices);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo.eboIndices);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
    }

    // Unbind buffers
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // --- Calculate Bounding Box for Automatic Scaling & Centering ---
    aiVector3D minB(1e10f, 1e10f, 1e10f);
    aiVector3D maxB(-1e10f, -1e10f, -1e10f);
    for (unsigned int m = 0; m < scene->mNumMeshes; ++m) {
        aiMesh* mesh = scene->mMeshes[m];
        for (unsigned int v = 0; v < mesh->mNumVertices; ++v) {
            aiVector3D pt = mesh->mVertices[v];
            if (pt.x < minB.x) minB.x = pt.x;
            if (pt.y < minB.y) minB.y = pt.y;
            if (pt.z < minB.z) minB.z = pt.z;
            if (pt.x > maxB.x) maxB.x = pt.x;
            if (pt.y > maxB.y) maxB.y = pt.y;
            if (pt.z > maxB.z) maxB.z = pt.z;
        }
    }
    aiVector3D size = maxB - minB;
    float maxDim = max(size.x, max(size.y, size.z));
    modelScale = (maxDim > 0.0001f) ? (2.0f / maxDim) : 1.0f;
    modelCenter = (minB + maxB) * 0.5f;
}

void _Anim3D::modelInit(const char* fileName, GLuint bodyID, GLuint exoID)      // overloaded modelInit to load two textures using existing function - Kyle
{
    modelInit(fileName, bodyID);

    exoTexID = exoID;
    useSecondTexture = true;
}

void _Anim3D::evaluateBones(const aiAnimation* anim, const aiNode* nd, const aiMatrix4x4& parentTransform) {
    std::string nodeName(nd->mName.C_Str());
    aiMatrix4x4 localTransform = nd->mTransformation;

    if (anim) {
        const aiNodeAnim* channel = nullptr;
        for (unsigned int i = 0; i < anim->mNumChannels; ++i) {
            if (nodeName == anim->mChannels[i]->mNodeName.C_Str()) {
                channel = anim->mChannels[i];
                break;
            }
        }

        if (channel) {
            float ticksPerSec = (anim->mTicksPerSecond != 0.0) ? (float)anim->mTicksPerSecond : 25.0f;
            float duration = (anim->mDuration > 0.0) ? (float)anim->mDuration : 1.0f;
            float skeletalTime = std::fmod(currentAnimTime * ticksPerSec, duration);

            unsigned int posIdx = 0, rotIdx = 0, sclIdx = 0;
            for (unsigned int i = 0; i < channel->mNumPositionKeys - 1; ++i)
                if (skeletalTime >= channel->mPositionKeys[i + 1].mTime) posIdx = i + 1;
            for (unsigned int i = 0; i < channel->mNumRotationKeys - 1; ++i)
                if (skeletalTime >= channel->mRotationKeys[i + 1].mTime) rotIdx = i + 1;
            for (unsigned int i = 0; i < channel->mNumScalingKeys - 1; ++i)
                if (skeletalTime >= channel->mScalingKeys[i + 1].mTime) sclIdx = i + 1;

            aiMatrix4x4 matRot = aiMatrix4x4(channel->mRotationKeys[rotIdx].mValue.GetMatrix());
            aiMatrix4x4 matScl, matPos;
            aiMatrix4x4::Scaling(channel->mScalingKeys[sclIdx].mValue, matScl);
            aiMatrix4x4::Translation(channel->mPositionKeys[posIdx].mValue, matPos);

            localTransform = matPos * matRot * matScl;
        }
    }

    aiMatrix4x4 globalTransform = parentTransform * localTransform;
    boneTransforms[nodeName] = globalTransform;

    for (unsigned int i = 0; i < nd->mNumChildren; ++i) {
        evaluateBones(anim, nd->mChildren[i], globalTransform);
    }
}

void _Anim3D::recursive_render(const aiScene* sc, const aiNode* nd, int specificFrame) {
    aiMatrix4x4 m = nd->mTransformation;

    if (sc->HasAnimations() && sc->mMeshes && sc->mMeshes[0]->mNumBones > 0) {
        m = aiMatrix4x4();
    }
    else if (sc->HasAnimations()) {
        m = boneTransforms[nd->mName.C_Str()];
    }

    aiTransposeMatrix4(&m);
    glMultMatrixf((float*)&m);

    aiMatrix4x4 globalInverse = sc->mRootNode->mTransformation;
    globalInverse.Inverse();

    for (unsigned int n = 0; n < nd->mNumMeshes; ++n) {
        unsigned int meshIndex = nd->mMeshes[n];
        const aiMesh* mesh = sc->mMeshes[meshIndex];
        MeshVBO& vbo = meshVBOs[meshIndex];


        //============ added this for extra model texture fix - Kyle
        // Select texture based on material index
        if (useSecondTexture && mesh->mMaterialIndex == 1)
        {
            glBindTexture(GL_TEXTURE_2D, exoTexID);
        }
        else
        {
            glBindTexture(GL_TEXTURE_2D, texID);
        }
        //============

        bool isSkeletal = mesh->mNumBones > 0;
        bool isMorphAnim = mesh->mNumAnimMeshes > 0;

        std::vector<aiVector3D> finalVertices(mesh->mNumVertices, aiVector3D(0.0f, 0.0f, 0.0f));
        std::vector<aiVector3D> finalNormals(mesh->mNumVertices, aiVector3D(0.0f, 0.0f, 0.0f));

        // 1. CPU Skeletal Skinning
        if (isSkeletal) {
            for (unsigned int b = 0; b < mesh->mNumBones; ++b) {
                aiBone* bone = mesh->mBones[b];
                std::string boneName(bone->mName.C_Str());

                aiMatrix4x4 finalBoneMat = globalInverse * boneTransforms[boneName] * bone->mOffsetMatrix;
                aiMatrix3x3 normalMat = aiMatrix3x3(finalBoneMat);

                for (unsigned int w = 0; w < bone->mNumWeights; ++w) {
                    int vId = bone->mWeights[w].mVertexId;
                    float weight = bone->mWeights[w].mWeight;

                    finalVertices[vId] += (finalBoneMat * mesh->mVertices[vId]) * weight;
                    if (mesh->mNormals) {
                        finalNormals[vId] += (normalMat * mesh->mNormals[vId]) * weight;
                    }
                }
            }
        }
        // 2. CPU Morph Targets
        else if (isMorphAnim) {
            int numFrames = mesh->mNumAnimMeshes;
            float fps = 10.0f;
            float frameTime = currentAnimTime * fps;

            int frame1 = static_cast<int>(frameTime) % numFrames;
            int frame2 = (frame1 + 1) % numFrames;
            float blendFactor = frameTime - std::floor(frameTime);

            aiAnimMesh* am1 = mesh->mAnimMeshes[frame1];
            aiAnimMesh* am2 = mesh->mAnimMeshes[frame2];

            for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
                if (am1->mVertices && am2->mVertices) {
                    finalVertices[i] = am1->mVertices[i] + (am2->mVertices[i] - am1->mVertices[i]) * blendFactor;
                }
                if (am1->mNormals && am2->mNormals) {
                    finalNormals[i] = am1->mNormals[i] + (am2->mNormals[i] - am1->mNormals[i]) * blendFactor;
                }
            }
        }
        // 3. Static Mesh Fallback (Fill buffers natively so they can still be drawn via VBO)
        else {
            for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
                finalVertices[i] = mesh->mVertices[i];
                if (mesh->mNormals) finalNormals[i] = mesh->mNormals[i];
            }
        }

        // --- Upload Dynamically Updated Data to VBOs ---
        glBindBuffer(GL_ARRAY_BUFFER, vbo.vboVertices);
        glBufferSubData(GL_ARRAY_BUFFER, 0, finalVertices.size() * sizeof(aiVector3D), finalVertices.data());

        if (vbo.hasNormals) {
            glBindBuffer(GL_ARRAY_BUFFER, vbo.vboNormals);
            glBufferSubData(GL_ARRAY_BUFFER, 0, finalNormals.size() * sizeof(aiVector3D), finalNormals.data());
        }

        // --- Render via Client States and Element Arrays ---
        glEnableClientState(GL_VERTEX_ARRAY);
        glBindBuffer(GL_ARRAY_BUFFER, vbo.vboVertices);
        glVertexPointer(3, GL_FLOAT, 0, (void*)0);

        if (vbo.hasNormals) {
            glEnableClientState(GL_NORMAL_ARRAY);
            glBindBuffer(GL_ARRAY_BUFFER, vbo.vboNormals);
            glNormalPointer(GL_FLOAT, 0, (void*)0);
        }

        if (vbo.hasTexCoords) {
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            glBindBuffer(GL_ARRAY_BUFFER, vbo.vboTexCoords);
            glTexCoordPointer(2, GL_FLOAT, 0, (void*)0);
        }

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo.eboIndices);
        glDrawElements(GL_TRIANGLES, vbo.numIndices, GL_UNSIGNED_INT, (void*)0);

        // --- Cleanup State ---
        glDisableClientState(GL_VERTEX_ARRAY);
        if (vbo.hasNormals) glDisableClientState(GL_NORMAL_ARRAY);
        if (vbo.hasTexCoords) glDisableClientState(GL_TEXTURE_COORD_ARRAY);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    for (unsigned int i = 0; i < nd->mNumChildren; ++i) {
        recursive_render(sc, nd->mChildren[i], specificFrame);
    }
}

void _Anim3D::display(float deltaT) {
    if (scene) {
        glEnable(GL_TEXTURE_2D);

        //Commented line under for model extra texture fix - Kyle
        //glBindTexture(GL_TEXTURE_2D, texID);

        glPushMatrix();

        glScalef(modelScale, modelScale, modelScale);

        currentAnimTime += deltaT;

        aiAnimation* anim = scene->HasAnimations() ? scene->mAnimations[currentAnimIndex] : nullptr;
        evaluateBones(anim, scene->mRootNode, aiMatrix4x4());

        recursive_render(scene, scene->mRootNode, -1);

        glPopMatrix();
    }
}