#ifndef _QUAD_H
#define _QUAD_H

#include<_Common.h>
#include<_TxtLoader.h>

class _Quad
{
    public:
        _Quad();
        _Quad(float px, float py, float pz, float rx, float ry, float rz, float sx, float sy, float sz, float b);
        _Quad(float inputScale);
        virtual ~_Quad();

        vec3 rot;
        vec3 pos;
        vec3 scale;
        float brightness;

        void initQuad(const char*);
        void drawQuad();
        void updateQuad();

        GLuint vboPos, vboTex;
        _TxtLoader *myTex = new _TxtLoader();

        float xMin = 0;
        float xMax = 1;
        float yMin = 0;
        float yMax = 1;

        float verticies[12]={1.0,1.0,0,  //top right
                             1.0,-1.0,0, //bottom right
                             -1.0,-1.0,0,//bottom left
                             -1.0,1.0,0  // top left
                              };

        float texCoord[8] = {xMax,yMin,
                             xMax,yMax,
                             xMin,yMax,
                             xMin,yMin
                             };

    protected:

    private:
};

#endif // _QUAD_H
