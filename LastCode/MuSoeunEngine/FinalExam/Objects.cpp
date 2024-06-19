#include "Object.h"
#include "main.h"
#include <GLFW/glfw3.h>
#include <cmath>

#pragma comment(lib, "Opengl32.lib")

Player::Player(float screenX, float screenY, float size)
    : size(size), velocityY(0.0f), width(size), height(size)
{
    // 생성자 구현
    x = screenToGLX(screenX);
    y = screenToGLY(screenY);
}

Floor::Floor(float screenX, float screenY, float screenWidth, float screenHeight)
    : width(screenWidth), height(screenHeight) {
    x = screenToGLX(screenX); // screenX를 OpenGL 좌표로 변환하여 x에 할당
    y = screenToGLY(screenY); // screenY를 OpenGL 좌표로 변환하여 y에 할당
}

//EnemyBlock::EnemyBlock(float screenX, float screenY, float width, float height)
//    : width(width), height(height)
//{
//    x = screenToGLX(screenX);
//    y = screenToGLY(screenY);
//}

EnemyBlock::EnemyBlock(float screenX, float screenY, float width, float height)
    : x(screenToGLX(screenX)), y(screenToGLY(screenY)), width(width), height(height), active(false) {}

// Player render function
void Player::Render() const {
    float glX = x;
    float glY = y;
    float glSizeX = screenToGLSizeX(size);
    float glSizeY = screenToGLSizeY(size);

    // 빨간색으로 내부를 채우는 사각형 그리기
    glColor3ub(255, 0, 0); // 빨간색
    glBegin(GL_QUADS);
    glVertex2f(glX - glSizeX / 2, glY - glSizeY / 2); // 좌측 하단
    glVertex2f(glX + glSizeX / 2, glY - glSizeY / 2); // 우측 하단
    glVertex2f(glX + glSizeX / 2, glY + glSizeY / 2); // 우측 상단
    glVertex2f(glX - glSizeX / 2, glY + glSizeY / 2); // 좌측 상단
    glEnd();

    // 검은색 테두리 그리기
    glLineWidth(3.0f); // 선 두께 설정
    glColor3ub(0, 0, 0); // 검은색
    glBegin(GL_LINE_LOOP);
    glVertex2f(glX - glSizeX / 2, glY - glSizeY / 2); // 좌측 하단
    glVertex2f(glX + glSizeX / 2, glY - glSizeY / 2); // 우측 하단
    glVertex2f(glX + glSizeX / 2, glY + glSizeY / 2); // 우측 상단
    glVertex2f(glX - glSizeX / 2, glY + glSizeY / 2); // 좌측 상단
    glEnd();
}

void Player::Update(float deltaTime) {
    // 중력 적용
    velocityY -= GRAVITY * deltaTime;

    // 속도에 따른 위치 업데이트
    y += velocityY * deltaTime;

    // 바닥 충돌 체크
    if (y < screenToGLY(460)) {
        y = screenToGLY(460);
        velocityY = 0;
    }
}

void Player::Jump() {
    if (y ==  screenToGLY(460)) { // 바닥에 있을 때만 점프 가능
        velocityY = JUMP_VELOCITY;
    }
}

// Floor의 Render 함수 구현

void Floor::Render() const {
    float glX = x;
    float glY = y;
    float glWidth = screenToGLSizeX(width);
    float glHeight = screenToGLSizeY(height);

    glColor3ub(255, 200, 15); // 황색
    glBegin(GL_QUADS);
    glVertex2f(glX - glWidth / 2, glY - glHeight / 2); // 좌측 하단
    glVertex2f(glX + glWidth / 2, glY - glHeight / 2); // 우측 하단
    glVertex2f(glX + glWidth / 2, glY + glHeight / 2); // 우측 상단
    glVertex2f(glX - glWidth / 2, glY + glHeight / 2); // 좌측 상단
    glEnd();
}

EnemyBlock::~EnemyBlock()
{
    // 아무 작업도 필요하지 않음
}

// EnemyBlock render function
void EnemyBlock::Render() const {
    float glX = x;
    float glY = y;
    float glWidth = screenToGLSizeX(width);
    float glHeight = screenToGLSizeY(height);

    glColor3ub(0, 255, 0); // 녹색
    glBegin(GL_QUADS);
    glVertex2f(glX - glWidth / 2, glY - glHeight / 2); // 좌측 하단
    glVertex2f(glX + glWidth / 2, glY - glHeight / 2); // 우측 하단
    glVertex2f(glX + glWidth / 2, glY + glHeight / 2); // 우측 상단
    glVertex2f(glX - glWidth / 2, glY + glHeight / 2); // 좌측 상단
    glEnd();
}

// AABB 충돌 검사 함수
bool PhysicsAABB(const Object& A, const Object& B) {
    // A 객체의 좌표를 OpenGL 좌표로 변환
    float AxMin = A.getX();
    float AxMax = A.getX() + A.getWidth();
    float AyMin = A.getY();
    float AyMax = A.getY() + A.getHeight();

    // B 객체의 좌표를 가져옴
    float BxMin = B.getX();
    float BxMax = B.getX() + B.getWidth();
    float ByMin = B.getY();
    float ByMax = B.getY() + B.getHeight();

    // A 객체의 OpenGL 좌표로 변환된 AABB
    //float AxMin = A.screenToGLX(A.getX());
    //float AxMax = A.screenToGLX(A.getX() + A.getWidth());
    //float AyMin = A.screenToGLY(A.getY());
    //float AyMax = A.screenToGLY(A.getY() + A.getHeight());

    //// B 객체의 OpenGL 좌표로 변환된 AABB
    //float BxMin = B.screenToGLX(B.getX());
    //float BxMax = B.screenToGLX(B.getX() + B.getWidth());
    //float ByMin = B.screenToGLY(B.getY());
    //float ByMax = B.screenToGLY(B.getY() + B.getHeight());

    // AABB 충돌 검사
    bool collisionX = AxMin > BxMax && AxMax < BxMin;
    bool collisionY = AyMin > ByMax && AyMax < ByMin;

    return collisionX && collisionY;
}