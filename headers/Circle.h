#pragma once

#include "SimObject.h"

class Circle : public SimObject {
private:
    float m_radius;

public:
    void draw() override;
    void step(const double dT) override;

    Circle(float x, float y, float z, float r);
};
