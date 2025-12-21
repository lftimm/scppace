#include "Cts.h"
#include "Circle.h"

#include <raymath.h>

Circle::Circle(float x, float y, float z, float r):
        SimObject(
            x,
            y,
            BoundingBox{
                Vector3{x-r,y-r,z-r}, Vector3{x+r,y+r,z+r}
            }
        ),
        m_radius(r)
{
}

void Circle::draw()
{
    DrawCircle(
        m_position.x,
        m_position.y,
        m_radius,
        RED
    );
}

void Circle::step(const double dT)
{
    auto dTf = static_cast<float>(dT);
    m_speed += {0,Cts::gravity*dTf,0};
    m_position += Vector3{
        0,
        m_speed.y*dTf + Cts::gravity*dTf*dTf/2,
        0,
    };
}
