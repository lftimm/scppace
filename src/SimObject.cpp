#include "SimObject.h"

SimObject::SimObject(float x, float y, BoundingBox bbox):
    m_position({x,y,0}),
    m_speed({0,0,0}),
    m_force({0,0,0}),
    m_mass(1.f),
    m_bbox(bbox)
{
}
