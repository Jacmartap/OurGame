#include "_Collision.h"

_Collision::_Collision()
{}

_Collision::~_Collision()
{}

bool _Collision::isLinearCollision(vec2, vec2)
{
    return false;
}

bool _Collision::isHitplane(vec3, vec3)
{
    return false;
}

bool _Collision::isRadialCollion(vec3 p1, vec3 p2, float r1, float r2, float threshold)
{
    return ( abs( (r1 + r2) - ( sqrt(pow(p1.x - p2.x, 2)) + sqrt(pow(p1.y - p2.y, 2)) ) ) < threshold );
}

bool _Collision::isCubicCollision(_Player* p, _Model* c)
{
    float minX1 = p->pos.x - 0.17;
    float minY1 = p->pos.y;
    float minZ1 = p->pos.z - 0.12;

    float maxX1 = p->pos.x + 0.17;
    float maxY1 = p->pos.y + 0.62;
    float maxZ1 = p->pos.z + 0.12;

    float minX2 = c->pos.x - c->scale.x;
    float minY2 = c->pos.y - c->scale.y;
    float minZ2 = c->pos.z - c->scale.z;

    float maxX2 = c->pos.x + c->scale.x;
    float maxY2 = c->pos.y + c->scale.y;
    float maxZ2 = c->pos.z + c->scale.z;

    return ((maxX1 >= minX2 && maxX2 >= minX1) && (maxY1 >= minY2 && maxY2 >= minY1) && (maxZ1 >= minZ2 && maxZ2 >= minZ1));
}

bool _Collision::isSphereCollision(vec3 p1, vec3 p2, float r1, float r2, float threshold)
{
    return ( abs( (r1 + r2) - ( sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2) + pow(p1.z - p2.z, 2)) ) ) < threshold );
}
