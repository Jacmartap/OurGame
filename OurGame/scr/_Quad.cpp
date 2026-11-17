#include "_Quad.h"

_Quad::_Quad()
{
    rot.x = rot.y = rot.z = 0;
    pos.x = pos.y = 0;
    pos.z = -8;
    scale.x = scale.y = scale.z = 0.25;
    brightness = 1.0;
}

_Quad::_Quad(float px, float py, float pz, float rx, float ry, float rz, float sx, float sy, float sz, float b)
{
    pos.x = px;
    pos.y = py;
    pos.z = pz;

    rot.x = rx;
    rot.y = ry;
    rot.z = rz;

    scale.x = sx;
    scale.y = sy;
    scale.z = sz;

    brightness = b;
}

_Quad::~_Quad()
{
    
}

void _Quad::initQuad(const char* fileName)
{
    glGenBuffers(1, &vboPos);
    glBindBuffer(GL_ARRAY_BUFFER, vboPos);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_DYNAMIC_DRAW);

    glGenBuffers(1, &vboTex);
    glBindBuffer(GL_ARRAY_BUFFER, vboTex);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texCoord), texCoord, GL_DYNAMIC_DRAW);

    myTex->loadTexture(fileName);
}

void _Quad::drawQuad()
{
    glPushMatrix();

    glDisable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);

    glColor3f(1.0 * brightness, 1.0 * brightness, 1.0 * brightness);           // set base color

    myTex->texBinder();

    glTranslatef(pos.x,pos.y,pos.z);  // place the object
    
    glRotatef(rot.x, 1, 0, 0);     // rotation around x
    glRotatef(rot.y, 0, 1, 0);     // rotation around y
    glRotatef(rot.z, 0, 0, 1);     // rotation around z
    
    glScalef(scale.x, scale.y, scale.z);// resize object

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, vboTex);
    glTexCoordPointer(2, GL_FLOAT, 0, (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, vboPos);
    glVertexPointer(3, GL_FLOAT, 0, (void*)0);

    glDrawArrays(GL_QUADS, 0, 4);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);

    glDisable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);

    glPopMatrix();
}

void _Quad::updateQuad()
{
     float texCoord[8] = {
                          xMax,yMin,
                          xMax,yMax,
                          xMin,yMax,
                          xMin,yMin
                         };
    
    glBindBuffer(GL_ARRAY_BUFFER,vboTex);
    glBufferSubData(GL_ARRAY_BUFFER,0,sizeof(texCoord),texCoord);
}
