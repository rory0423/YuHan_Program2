#pragma once
namespace Transform
{
	struct Vertex
	{
		float x;
		float y;
	};

	Vertex MoveVertex(Vertex point, float dx, float dy);
	Vertex RotateVertex(Vertex point, float angle_degree);
	Vertex ScaleVertex(Vertex point, float scaleX, float scaleY);
	Vertex RotateClockwise(Vertex point, float angle_degree);

};