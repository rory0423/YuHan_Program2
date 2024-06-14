#pragma once

#include "Transform.h"
#include <cmath>

namespace Transform
{
    Vertex MoveVertex(Vertex point, Vector meter)
    {
        point.x += meter.x_meter;
        point.y += meter.y_meter;
        return point;
    }

    Vertex RotateVertex(Vertex point, float angle_degree)
    {
        float M_PI = 3.141592f;
        float angle_rad = angle_degree * M_PI / 180.0f;
        float cos_theta = std::cos(angle_rad);
        float sin_theta = std::sin(angle_rad);

        Vertex rotated_point;
        rotated_point.x = point.x * cos_theta + point.y * sin_theta;
        rotated_point.y = -point.x * sin_theta + point.y * cos_theta;

        return rotated_point;
    }

    Vertex ScaleVertex(Vertex point, Vector meter)
    {
        point.x *= meter.x_meter;
        point.y *= meter.y_meter;
        return point;
    }
}