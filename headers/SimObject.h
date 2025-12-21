#pragma once
#include <raylib.h>
#include <raymath.h>

class SimObject {
protected:
    Vector3 m_position{};
    Vector3 m_speed{};
    Vector3 m_force{};
    float m_mass{};
    BoundingBox m_bbox{};

public:
    SimObject(float x, float y, BoundingBox bbox);
        
    virtual ~SimObject() = default;
    virtual void draw() = 0;
    virtual void step(const double dT) = 0;
};
