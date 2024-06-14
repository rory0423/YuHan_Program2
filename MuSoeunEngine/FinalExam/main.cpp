#pragma comment(lib, "Opengl32.lib")

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#else
#define DBG_NEW new
#endif

#include <GLFW/glfw3.h>
#include <stdio.h>
#include <chrono>
#include <thread>
#include <cmath>

#include "Object.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

const float obstacleSpawnInterval = 2.0f; 
float obstacleSpawnTimer = 0.0f;

// 스크린 좌표계에서 코드 내부 좌표계로 변환하는 함수
float screenToCodeX(int screenX) {
	return 4.0f * (screenX / static_cast<float>(SCREEN_WIDTH)) - 2.0f;
}

float screenToCodeY(int screenY) {
	return 2.0f - 4.0f * (screenY / static_cast<float>(SCREEN_HEIGHT));
}

// 코드 내부 좌표계에서 스크린 좌표계로 변환하는 함수
int codeToScreenX(float codeX) {
	return static_cast<int>((codeX + 2.0f) * (SCREEN_WIDTH / 4.0f));
}

int codeToScreenY(float codeY) {
	return static_cast<int>((2.0f - codeY) * (SCREEN_HEIGHT / 4.0f));
}

void errorCallback(int error, const char* description)
{
	printf("GLFW Error: %s", description);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

void Player::Render() const {
	// 내부를 채우는 사각형 그리기
	glColor3f(1.0f, 0.0f, 0.0f); // 빨간색

	float halfWidth = width / 2.0f;
	float halfHeight = height / 2.0f;

	glBegin(GL_QUADS);
	glVertex2f(x - halfWidth, y - halfHeight); // 좌측 하단
	glVertex2f(x + halfWidth, y - halfHeight); // 우측 하단
	glVertex2f(x + halfWidth, y + halfHeight); // 우측 상단
	glVertex2f(x - halfWidth, y + halfHeight); // 좌측 상단
	glEnd();

	// 테두리를 그리는 사각형 그리기
	glLineWidth(3.0f); // 선 두께 설정
	glColor3f(0.0f, 0.0f, 0.0f); // 검은색 테두리

	glBegin(GL_LINE_LOOP);
	glVertex2f(x - halfWidth, y - halfHeight); // 좌측 하단
	glVertex2f(x + halfWidth, y - halfHeight); // 우측 하단
	glVertex2f(x + halfWidth, y + halfHeight); // 우측 상단
	glVertex2f(x - halfWidth, y + halfHeight); // 좌측 상단
	glEnd();
}

void Floor::Render() const {
	// OpenGL을 사용하여 바닥을 그리는 코드 작성

	float halfWidth = width / 2.0f;
	float halfHeight = height / 2.0f;

	glColor3ub(255, 200, 15); // 황색

	glBegin(GL_QUADS);
	glVertex2f(x - halfWidth, y - halfHeight); // 좌측 하단
	glVertex2f(x + halfWidth, y - halfHeight); // 우측 하단
	glVertex2f(x + halfWidth, y + halfHeight); // 우측 상단
	glVertex2f(x - halfWidth, y + halfHeight); // 좌측 상단
	glEnd();
}

void EnemyBlock::Render() const {
	// OpenGL을 사용하여 장애물을 그리는 코드 작성
	glColor3ub(0, 255, 0); // 녹색

	float halfWidth = width / 2.0f;
	float halfHeight = height;

	glBegin(GL_QUADS);
	glVertex2f(x - halfWidth, y - halfHeight); // 좌측 하단
	glVertex2f(x + halfWidth, y - halfHeight); // 우측 하단
	glVertex2f(x + halfWidth, y + halfHeight); // 우측 상단
	glVertex2f(x - halfWidth, y + halfHeight); // 좌측 상단
	glEnd();
}

void renderSquare(int screenX, int screenY, float size) {
	float codeX = screenToCodeX(screenX);
	float codeY = screenToCodeY(screenY);
	float halfSize = size / 2.0f;

	glBegin(GL_QUADS);
	glVertex2f(codeX - halfSize, codeY - halfSize);
	glVertex2f(codeX + halfSize, codeY - halfSize);
	glVertex2f(codeX + halfSize, codeY + halfSize);
	glVertex2f(codeX - halfSize, codeY + halfSize);
	glEnd();
}

int Physics()
{
	return 0;
}

int Initialize()
{
	return 0;
}

int Update()
{

	return 0;
}

int Render()
{
	glClearColor(0.0f, 0.1176f, 0.3922f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	//Player player(-0.5f, -0.66f, 0.125f); // 예시: 위치 (0, 0), 크기 50
	//Floor floor(0.0f, -0.8f, 2.0f, 0.15f);
	//EnemyBlock obstacle1(0.6f, -0.56f, 0.125f, 0.166f); // 첫 번째 장애물 (가로 50cm, 높이 100cm)
	//EnemyBlock obstacle2(0.8f, -0.23f, 0.125f, 0.5f); // 두 번째 장애물 (가로 50cm, 높이 300cm)

	renderSquare(400, 300, 0.2);

	//player.Render();
	//floor.Render();

	//obstacle1.Render();
	//obstacle2.Render();

	return 0;
}


int main(void)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);


	//glfw라이브러리 초기화
	if (!glfwInit())
		return -1;

	GLFWwindow* window;
	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Google Dino Run Copy Game", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetErrorCallback(errorCallback);
	glfwSetKeyCallback(window, keyCallback);

	Initialize();

	while (!glfwWindowShouldClose(window))
	{

		glfwPollEvents();
		Physics();
		Update();
		Render();
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;

}