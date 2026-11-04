#include "_ModelLoader.h"

_ModelLoader::_ModelLoader()
{

}

_ModelLoader::~_ModelLoader()
{
	aiReleaseImport(scene);
}

void _ModelLoader::modelInit(const char* fileName, const char* skin)
{
    const char* filePath = fileName; // Replace with your model path
    
    scene = aiImportFile(filePath, aiProcessPreset_TargetRealtime_Quality | aiProcess_Triangulate);

    myTex->loadTexture(skin);

    if (!scene) {
        std::cerr << "Error loading model: " << aiGetErrorString() << std::endl;
        //return -1;
    }
}

void _ModelLoader::recursive_render(const aiScene * sc, const aiNode * nd)
{
    unsigned int i;
    
    aiMatrix4x4 m = nd->mTransformation;

    // Transpose matrix for OpenGL column-major order
    aiTransposeMatrix4(&m);
    glPushMatrix();
    glMultMatrixf((float*)&m);

    glEnable(GL_TEXTURE_2D);
    myTex->texBinder();

    // Draw all meshes assigned to this node
    for (int n = 0; n < nd->mNumMeshes; ++n) {
        const aiMesh* mesh = sc->mMeshes[nd->mMeshes[n]];

        for (unsigned int t = 0; t < mesh->mNumFaces; ++t)
        {
            const aiFace* face = &mesh->mFaces[t];
            GLenum face_mode;

            switch (face->mNumIndices)
            {
                case 1:
                    face_mode = GL_POINTS;
                    break;
                
                case 2:
                    face_mode = GL_LINES;
                    break;
                
                case 3:
                    face_mode = GL_TRIANGLES;
                    break;
                
                default:
                    face_mode = GL_POLYGON;
                    break;
            }

            glBegin(face_mode);
            
            for (unsigned int i = 0; i < face->mNumIndices; i++)
            {
                int index = face->mIndices[i];

                if (mesh->HasTextureCoords(0))
                {
                    // Assimp supports 3D texture vectors, legacy OpenGL expects 2D (u, v)
                    glTexCoord2f(mesh->mTextureCoords[0][index].x, mesh->mTextureCoords[0][index].y);
                }
               
                if (mesh->mNormals)
                {
                    glNormal3fv(&mesh->mNormals[index].x);
                }
                
                glVertex3fv(&mesh->mVertices[index].x);
            }
            
            glEnd();
        }
    }

    // Draw children
    for (i = 0; i < nd->mNumChildren; ++i)
    {
        recursive_render(sc, nd->mChildren[i]);
    }

    glPopMatrix();

}

void _ModelLoader::display(float deltaT)
{
    timer += deltaT;
    
    if (timer > 0.05)
    {
        angle += 1.0;
        timer = 0;
    }

    glRotatef(angle, 0.0f, 1.0f, 0.0f);
    

    if (scene)
    {
        recursive_render(scene, scene->mRootNode);
    }

}


