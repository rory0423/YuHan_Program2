#include "Transform.h"
#include <cmath>

namespace Transform {

    Vertex MoveVertex(Vertex point, float dx, float dy)
    {
        Vertex movedPoint;
        movedPoint.x = point.x + dx;
        movedPoint.y = point.y + dy;
        return movedPoint;
    }

    Vertex RotateVertex(Vertex point, float angle_degree) {
        // 각도를 라디안으로 변환
        float angle_rad = angle_degree * 3.14159265359f / 180.0f;

        Vertex rotatedPoint;
        rotatedPoint.x = point.x * cos(angle_rad) - point.y * sin(angle_rad);
        rotatedPoint.y = point.x * sin(angle_rad) + point.y * cos(angle_rad);
        return rotatedPoint;
    }

    // 시계 방향으로 각도 단위 회전하는 함수
    Vertex RotateClockwise(Vertex point, float angle_degree) {
        // 각도를 라디안으로 변환하고 음수로 변환하여 시계 방향 회전 적용
        float angle_rad = -angle_degree * 3.14159265359f / 180.0f;

        Vertex rotatedPoint;
        rotatedPoint.x = point.x * cos(angle_rad) - point.y * sin(angle_rad);
        rotatedPoint.y = point.x * sin(angle_rad) + point.y * cos(angle_rad);
        return rotatedPoint;

        // 시계 방향 회전을 위해 각도를 음수로 처리
        // return RotateVertex(point, -angle_degree);

    }
    
    Vertex ScaleVertex(Vertex point, float scaleX, float scaleY) {
        Vertex scaledPoint;
        scaledPoint.x = point.x * scaleX;
        scaledPoint.y = point.y * scaleY;
        return scaledPoint;
    }
}