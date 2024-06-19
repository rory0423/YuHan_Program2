#pragma comment(lib, "Opengl32.lib")

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#else
#define DBG_NEW new
#endif

#include <iostream>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <chrono>
#include <thread>
#include <cmath>

#include "Object.h"
#include "main.h"
#include "Transform.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

const float obstacleSpawnInterval = 2.0f;
float obstacleSpawnTimer = 0.0f;

float deltaTime = 0.16f; // 약 60FPS
const int NUM_BLOCKS = 3;

// 전역 EnemyBlock 배열
EnemyBlock blocks[NUM_BLOCKS] = {
EnemyBlock(800, 440, 50, 100),
EnemyBlock(1800, 340, 50, 300),
EnemyBlock(2800, 440, 50, 100)
};

Player player(400, 460, 50);  // 위치 (400, 300), 크기 50

//EnemyBlock* blocks[NUM_BLOCKS] = {}; // 동적 배열로 선언

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
	else if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{
		// 플레이어 점프
		player.Jump();
	}
}

void updateDeltaTime()
{
	static auto lastTime = std::chrono::high_resolution_clock::now();
	auto currentTime = std::chrono::high_resolution_clock::now();
	deltaTime = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - lastTime).count();
	lastTime = currentTime;
}

// 스크린 좌표계를 OpenGL 좌표계로 변환하는 함수
float screenToGLX(int screenX) {
	float normalizedX = static_cast<float>(screenX) / SCREEN_WIDTH; // 스크린 X를 [0, 1] 범위로 정규화
	return 2.0f * normalizedX - 1.0f; // OpenGL 좌표계로 변환
}
// 스크린 좌표계를 OpenGL 좌표계로 변환하는 함수
float screenToGLY(int screenY) {
	float normalizedY = 1.0f - static_cast<float>(screenY) / SCREEN_HEIGHT; // 스크린 Y를 [0, 1] 범위로 정규화
	return 2.0f * normalizedY - 1.0f; // OpenGL 좌표계로 변환
}

// OpenGL 좌표계를 스크린 좌표계로 변환하는 함수
int glToScreenX(float glX) {
	return static_cast<int>((glX + 1.0f) * (SCREEN_WIDTH / 2.0f));
}
// OpenGL 좌표계를 스크린 좌표계로 변환하는 함수
int glToScreenY(float glY) {
	return static_cast<int>((1.0f - glY) * (SCREEN_HEIGHT / 2.0f));
}

// 스크린 크기를 OpenGL 크기로 변환하는 함수
float screenToGLSizeX(int screenWidth) {
	return static_cast<float>(screenWidth) / SCREEN_WIDTH * 2.0f;
}

// 스크린 크기를 OpenGL 크기로 변환하는 함수
float screenToGLSizeY(int screenHeight) {
	return static_cast<float>(screenHeight) / SCREEN_HEIGHT * 2.0f;
}

//void UpdateEnemy(float speed, float deltaTime)
//{
//	for (int i = 0; i < NUM_BLOCKS; ++i)
//	{
//		if (blocks[i] != nullptr && blocks[i]->isActive())
//		{
//			// 현재 블록의 좌표를 가져옴
//			float currentX = blocks[i]->getX();
//			float currentY = blocks[i]->getY();
//
//			// 새로운 위치 계산
//			Transform::Vertex newPosition = Transform::MoveVertex({ currentX, currentY }, -speed * deltaTime, 0.0f);
//
//			// 새로운 위치를 블록에 설정
//			blocks[i]->setX(newPosition.x);
//			blocks[i]->setY(newPosition.y);
//
//			// 화면을 벗어나면 다시 우측에서 나타나도록 설정
//			if (blocks[i]->getX() + blocks[i]->getWidth() / 2 < 0.0f)
//			{
//				blocks[i]->setX(SCREEN_WIDTH + blocks[i]->getWidth() / 2);
//			}
//		}
//	}
//}

void UpdateEnemy(EnemyBlock* blocks, int numBlocks, float speed, float deltaTime)
{
	for (int i = 0; i < numBlocks; ++i)
	{
		// 현재 블록의 좌표를 가져옴
		float currentX = blocks[i].getX();
		float currentY = blocks[i].getY();

		// 새로운 위치 계산
		Transform::Vertex newPosition = Transform::MoveVertex({ currentX, currentY }, -speed * deltaTime, 0.0f);

		// 새로운 위치를 블록에 설정
		blocks[i].setX(newPosition.x);
		blocks[i].setY(newPosition.y);

		if (blocks[i].getX() < -1.0f)
		{
			blocks[i].setX(2.0f);
		}
	}
}

//void SpawnEnemy()
//{
//	obstacleSpawnTimer += deltaTime;
//
//	// 일정 간격으로 새로운 EnemyBlock 생성
//	if (obstacleSpawnTimer >= obstacleSpawnInterval)
//	{
//		bool spawned = false;
//
//		// 새로운 EnemyBlock 생성
//		for (int i = 0; i < NUM_BLOCKS; ++i)
//		{
//			if (blocks[i] == nullptr)
//			{
//				// 새로운 EnemyBlock을 생성
//				blocks[i] = new EnemyBlock(SCREEN_WIDTH + 50, SCREEN_HEIGHT / 2, 50, 100);
//				printf("Spawned new enemy block. Index: %d\n", i); // 디버깅용 출력
//				spawned = true;
//				break;
//			}
//			else if (!blocks[i]->isActive())
//			{
//				// 기존의 비활성화된 EnemyBlock을 활성화하고 초기 위치 설정
//				blocks[i]->setX(SCREEN_WIDTH + 50);
//				blocks[i]->setY(SCREEN_HEIGHT / 2);
//				blocks[i]->setActive(true);
//				spawned = true;
//				break;
//			}
//		}
//
//		if (spawned)
//			obstacleSpawnTimer = 0.0f; // 타이머 초기화
//	}
//}

int Physics()
{
	// 예시로 충돌 검사
	for (int i = 0; i < NUM_BLOCKS; ++i) {
		bool isColliding = PhysicsAABB(player, blocks[i]);
		std::cout << "Collision: " << std::boolalpha << isColliding << std::endl;
	}

	return 0;
}

int Initialize()
{
	return 0;
}

int Update()
{
	UpdateEnemy(blocks, NUM_BLOCKS, 1.0f, deltaTime); // 적 업데이트 함수 호출
	//UpdateEnemy(0.5f, deltaTime); // 적 업데이트 함수 호출
	//SpawnEnemy();

	player.Update(deltaTime);

	return 0;
}

int Render()
{
	glClearColor(0.0f, 0.1176f, 0.3922f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// renderSquare(300, 200, 50);

	// 플레이어 렌더링 (스크린 좌표 기준)
	player.Render();

	Floor floor(400, 560, 800, 145);  // 위치 (x, y), 크기 (width, height)
	floor.Render();

	//EnemyBlock block1(200, 440, 50, 100); // 위치 (200, 300), 너비 50, 높이 100
	//block1.Render();

	//EnemyBlock block2(300, 340, 50, 300); // 위치 (600, 300), 너비 50, 높이 300
	//block2.Render();

	for (int i = 0; i < NUM_BLOCKS; i++)
	{
		blocks[i].Render();
	}
	//void (EnemyBlock:: * renderFunc)() const = &EnemyBlock::Render; // 멤버 함수 포인터 정의

	//for (int i = 0; i < NUM_BLOCKS; ++i)
	//{
	//	if (blocks[i] != nullptr && blocks[i]->isActive())
	//	//if (blocks[i] != nullptr)
	//	{
	//		(blocks[i]->*renderFunc)(); // 함수 포인터를 사용하여 호출
	//		printf("a");
	//	}
	//}

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
		updateDeltaTime();

		glfwPollEvents();

		Physics();
		Update();

		Render();

		// FPS 제한 (60fps로 제한)
		std::this_thread::sleep_for(std::chrono::milliseconds(16)); // 1초 / 60 = 16.67ms

		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;

}