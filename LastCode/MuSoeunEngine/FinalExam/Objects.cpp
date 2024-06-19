#include "Object.h"
#include "main.h"
#include <GLFW/glfw3.h>
#include <cmath>

#pragma comment(lib, "Opengl32.lib")

Player::Player(float screenX, float screenY, float size)
    : size(size), velocityY(0.0f), width(size), height(size)
{
    // ������ ����
    x = screenToGLX(screenX);
    y = screenToGLY(screenY);
}

Floor::Floor(float screenX, float screenY, float screenWidth, float screenHeight)
    : width(screenWidth), height(screenHeight) {
    x = screenToGLX(screenX); // screenX�� OpenGL ��ǥ�� ��ȯ�Ͽ� x�� �Ҵ�
    y = screenToGLY(screenY); // screenY�� OpenGL ��ǥ�� ��ȯ�Ͽ� y�� �Ҵ�
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

    // ���������� ���θ� ä��� �簢�� �׸���
    glColor3ub(255, 0, 0); // ������
    glBegin(GL_QUADS);
    glVertex2f(glX - glSizeX / 2, glY - glSizeY / 2); // ���� �ϴ�
    glVertex2f(glX + glSizeX / 2, glY - glSizeY / 2); // ���� �ϴ�
    glVertex2f(glX + glSizeX / 2, glY + glSizeY / 2); // ���� ���
    glVertex2f(glX - glSizeX / 2, glY + glSizeY / 2); // ���� ���
    glEnd();

    // ������ �׵θ� �׸���
    glLineWidth(3.0f); // �� �β� ����
    glColor3ub(0, 0, 0); // ������
    glBegin(GL_LINE_LOOP);
    glVertex2f(glX - glSizeX / 2, glY - glSizeY / 2); // ���� �ϴ�
    glVertex2f(glX + glSizeX / 2, glY - glSizeY / 2); // ���� �ϴ�
    glVertex2f(glX + glSizeX / 2, glY + glSizeY / 2); // ���� ���
    glVertex2f(glX - glSizeX / 2, glY + glSizeY / 2); // ���� ���
    glEnd();
}

void Player::Update(float deltaTime) {
    // �߷� ����
    velocityY -= GRAVITY * deltaTime;

    // �ӵ��� ���� ��ġ ������Ʈ
    y += velocityY * deltaTime;

    // �ٴ� �浹 üũ
    if (y < screenToGLY(460)) {
        y = screenToGLY(460);
        velocityY = 0;
    }
}

void Player::Jump() {
    if (y ==  screenToGLY(460)) { // �ٴڿ� ���� ���� ���� ����
        velocityY = JUMP_VELOCITY;
    }
}

// Floor�� Render �Լ� ����

void Floor::Render() const {
    float glX = x;
    float glY = y;
    float glWidth = screenToGLSizeX(width);
    float glHeight = screenToGLSizeY(height);

    glColor3ub(255, 200, 15); // Ȳ��
    glBegin(GL_QUADS);
    glVertex2f(glX - glWidth / 2, glY - glHeight / 2); // ���� �ϴ�
    glVertex2f(glX + glWidth / 2, glY - glHeight / 2); // ���� �ϴ�
    glVertex2f(glX + glWidth / 2, glY + glHeight / 2); // ���� ���
    glVertex2f(glX - glWidth / 2, glY + glHeight / 2); // ���� ���
    glEnd();
}

EnemyBlock::~EnemyBlock()
{
    // �ƹ� �۾��� �ʿ����� ����
}

// EnemyBlock render function
void EnemyBlock::Render() const {
    float glX = x;
    float glY = y;
    float glWidth = screenToGLSizeX(width);
    float glHeight = screenToGLSizeY(height);

    glColor3ub(0, 255, 0); // ���
    glBegin(GL_QUADS);
    glVertex2f(glX - glWidth / 2, glY - glHeight / 2); // ���� �ϴ�
    glVertex2f(glX + glWidth / 2, glY - glHeight / 2); // ���� �ϴ�
    glVertex2f(glX + glWidth / 2, glY + glHeight / 2); // ���� ���
    glVertex2f(glX - glWidth / 2, glY + glHeight / 2); // ���� ���
    glEnd();
}

// AABB �浹 �˻� �Լ�
bool PhysicsAABB(const Object& A, const Object& B) {
    // A ��ü�� ��ǥ�� OpenGL ��ǥ�� ��ȯ
    float AxMin = A.getX();
    float AxMax = A.getX() + A.getWidth();
    float AyMin = A.getY();
    float AyMax = A.getY() + A.getHeight();

    // B ��ü�� ��ǥ�� ������
    float BxMin = B.getX();
    float BxMax = B.getX() + B.getWidth();
    float ByMin = B.getY();
    float ByMax = B.getY() + B.getHeight();

    // A ��ü�� OpenGL ��ǥ�� ��ȯ�� AABB
    //float AxMin = A.screenToGLX(A.getX());
    //float AxMax = A.screenToGLX(A.getX() + A.getWidth());
    //float AyMin = A.screenToGLY(A.getY());
    //float AyMax = A.screenToGLY(A.getY() + A.getHeight());

    //// B ��ü�� OpenGL ��ǥ�� ��ȯ�� AABB
    //float BxMin = B.screenToGLX(B.getX());
    //float BxMax = B.screenToGLX(B.getX() + B.getWidth());
    //float ByMin = B.screenToGLY(B.getY());
    //float ByMax = B.screenToGLY(B.getY() + B.getHeight());

    // AABB �浹 �˻�
    bool collisionX = AxMin > BxMax && AxMax < BxMin;
    bool collisionY = AyMin > ByMax && AyMax < ByMin;

    return collisionX && collisionY;
}