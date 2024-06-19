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
        // ������ �������� ��ȯ
        float angle_rad = angle_degree * 3.14159265359f / 180.0f;

        Vertex rotatedPoint;
        rotatedPoint.x = point.x * cos(angle_rad) - point.y * sin(angle_rad);
        rotatedPoint.y = point.x * sin(angle_rad) + point.y * cos(angle_rad);
        return rotatedPoint;
    }

    // �ð� �������� ���� ���� ȸ���ϴ� �Լ�
    Vertex RotateClockwise(Vertex point, float angle_degree) {
        // ������ �������� ��ȯ�ϰ� ������ ��ȯ�Ͽ� �ð� ���� ȸ�� ����
        float angle_rad = -angle_degree * 3.14159265359f / 180.0f;

        Vertex rotatedPoint;
        rotatedPoint.x = point.x * cos(angle_rad) - point.y * sin(angle_rad);
        rotatedPoint.y = point.x * sin(angle_rad) + point.y * cos(angle_rad);
        return rotatedPoint;

        // �ð� ���� ȸ���� ���� ������ ������ ó��
        // return RotateVertex(point, -angle_degree);

    }
    
    Vertex ScaleVertex(Vertex point, float scaleX, float scaleY) {
        Vertex scaledPoint;
        scaledPoint.x = point.x * scaleX;
        scaledPoint.y = point.y * scaleY;
        return scaledPoint;
    }
}