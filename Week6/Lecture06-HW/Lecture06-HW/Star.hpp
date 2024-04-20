#include "MObject.h"
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <ctime>

float SF = 0.5f;

class Star : public MObject
{
public:
    Star()
    {
        // ������ �õ带 �ʱ�ȭ (���α׷��� ���� �κп��� �� ���� ȣ��)
        static bool seeded = false;
        if (!seeded)
        {
            srand(time(NULL));
            seeded = true;
        }

        // ������ ��ġ ���� (-1.0���� 1.0 ����)
        posX = static_cast<float>(rand()) / RAND_MAX * 3.5 - 1.75;
        posY = static_cast<float>(rand()) / RAND_MAX * 3.5 - 1.75;

        // ������ ���� ����
        ColorR = static_cast<float>(rand()) / RAND_MAX;
        ColorG = static_cast<float>(rand()) / RAND_MAX;
        ColorB = static_cast<float>(rand()) / RAND_MAX;
    }
	void update()
	{

	}
	void render()
	{
		glBegin(GL_TRIANGLES);

        // ù��°
        glColor3f(ColorR, ColorG, ColorB);
        glVertex2f(0.0f + posX * SF, -0.05f + posY * SF);
        glVertex2f(0.05f + posX* SF, 0.05f + posY * SF);
        glVertex2f(-0.05f + posX * SF, 0.05f +posY * SF);

        // �ι�°
        glColor3f(ColorR, ColorG, ColorB);
        glVertex2f(0.0f + posX * SF, 0.1f + posY * SF);
        glVertex2f(0.0f + posX * SF, -0.05f + posY * SF);
        glVertex2f(-0.04f + posX * SF, -0.075f + posY * SF);

        // ����°
        glColor3f(ColorR, ColorG, ColorB);
        glVertex2f(0.0f + posX  * SF, 0.10f + posY * SF);
        glVertex2f(0.0f + posX * SF, -0.05f + posY * SF);
        glVertex2f(0.04f + posX * SF, -0.075f + posY * SF);

		glEnd();

	}
    private:
        float posX;
        float posY;
        float ColorR;
        float ColorG;
        float ColorB;
};