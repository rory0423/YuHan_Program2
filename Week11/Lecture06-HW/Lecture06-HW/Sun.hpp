#include "MObject.h"
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <ctime>

const float PI = 3.14159265358979323846f;

class Sun : public MObject
{
public:
    Sun()
    {
        SF = 1.0f;
        posX = 0;
        posY = 0;

    }
	void update()
	{

	}
	void render()
	{
		glBegin(GL_TRIANGLES);

        // 첫번째
        glColor3f(ColorR, ColorG, ColorB);
        glVertex2f(0.0f + posX * SF, -0.05f + posY * SF);
        glVertex2f(0.05f + posX* SF, 0.05f + posY * SF);
        glVertex2f(-0.05f + posX * SF, 0.05f +posY * SF);

        // 두번째
        glColor3f(ColorR, ColorG, ColorB);
        glVertex2f(0.0f + posX * SF, 0.1f + posY * SF);
        glVertex2f(0.0f + posX * SF, -0.05f + posY * SF);
        glVertex2f(-0.04f + posX * SF, -0.075f + posY * SF);

        // 세번째
        glColor3f(ColorR, ColorG, ColorB);
        glVertex2f(0.0f + posX  * SF, 0.10f + posY * SF);
        glVertex2f(0.0f + posX * SF, -0.05f + posY * SF);
        glVertex2f(0.04f + posX * SF, -0.075f + posY * SF);

		glEnd();

	}
    private:
        float posX;
        float posY;
        float radius;
        float SF;
        int NUM_TRIANGLES;
};