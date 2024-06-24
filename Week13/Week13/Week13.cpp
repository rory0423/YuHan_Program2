#pragma comment(lib, "Opengl32.lib")

#include <GLFW/glfw3.h>
#include <iostream>
#include <chrono>
#include <thread>

float BoxPosY = 0.0f;
float BoxVelY = 0.0f;

float gravity = -6.8f;
const float deltaTime = 0.01f;

void errorCallback(int error, const char* description)
{
	std::cerr << "GLFW Error: " << description << std::endl;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
	else if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) // 스페이스바 입력 감지
	{
		if (BoxPosY <= -0.8f) // 바닥에 있는 경우에만 점프 가능하도록
		{
			BoxVelY = 5.0f; // 점프할 때 상자의 초기 속도 설정 (예: 5m/s)
		}
	}
}

void DrawPlane()
{
	glBegin(GL_QUADS);

	glColor3f(0.7f, 0.8f, 0.85f);
	glVertex2f(2.0f, -0.8f);
	glVertex2f(-2.0f, -0.8f);
	glVertex2f(-2.0f, -1.0f);
	glVertex2f(2.0f, -1.0f);


	glEnd();
}

void DrawBox()
{
	glBegin(GL_QUADS);

	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(0.2f, 0.0f + BoxPosY);
	glVertex2f(-0.2f, 0.0f + BoxPosY);
	glVertex2f(-0.2f, 0.4f + BoxPosY);
	glVertex2f(0.2f, 0.4f + BoxPosY);

	glEnd();
}

void UpdateBoxPosition()
{
	// 중력에 따라 속도 갱신
	BoxVelY += gravity * deltaTime;

	// 상자의 위치 갱신
	BoxPosY += BoxVelY * deltaTime;

	// 바닥에 닿았을 때 속도를 반전시키고 위치를 보정
	if (BoxPosY <= -0.8f)
	{
		BoxPosY = -0.8f;
		BoxVelY = -BoxVelY * 0.6f; // 탄성 계수 적용
	}
}

int render()
{
	DrawPlane();
	DrawBox();

	return 0;
}

int main(void)
{
	//glfw라이브러리 초기화
	if (!glfwInit())
		return -1;

	GLFWwindow* window;
	window = glfwCreateWindow(1280, 1280, "MuSoeunEngine", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glfwSetErrorCallback(errorCallback);
	glfwSetKeyCallback(window, keyCallback);

	while (!glfwWindowShouldClose(window))
	{
		auto startTime = std::chrono::steady_clock::now(); // 현재 시간 기록

		glfwPollEvents();
		glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		UpdateBoxPosition();

		render();

		glfwSwapBuffers(window);

		auto endTime = std::chrono::steady_clock::now(); // 현재 시간 기록
		auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count(); // 경과 시간 계산

		if (elapsedTime < deltaTime * 1000) // 경과 시간이 프레임 간격보다 작을 경우 대기
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<long>(deltaTime * 1000 - elapsedTime)));
		}
	}

	glfwTerminate();
	return 0;

}