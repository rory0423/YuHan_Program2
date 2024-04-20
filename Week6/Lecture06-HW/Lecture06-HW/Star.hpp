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
        // 무작위 시드를 초기화 (프로그램의 시작 부분에서 한 번만 호출)
        static bool seeded = false;
        if (!seeded)
        {
            srand(time(NULL));
            seeded = true;
        }

        // 무작위 위치 설정 (-1.0에서 1.0 사이)
        posX = static_cast<float>(rand()) / RAND_MAX * 3.5 - 1.75;
        posY = static_cast<float>(rand()) / RAND_MAX * 3.5 - 1.75;

        // 무작위 색상 설정
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
        float ColorR;
        float ColorG;
        float ColorB;
};