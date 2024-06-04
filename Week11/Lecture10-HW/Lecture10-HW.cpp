#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

#pragma comment(lib, "Opengl32.lib")

float radius;
float x_offset;
float y_offset;
float Angle = 0;
float Angle2 = 0;
float Angle3 = 0;

float M_PI = 3.14;

// 오류 콜백 함수
void errorCallback(int error, const char* description)
{
    std::cerr << "GLFW Error: " << description << std::endl;
}

// 키 콜백 함수 (사용하지 않으므로 빈 함수로 남겨둠)
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
}

int setVertexRotation(float x, float y, float angle_degree)
{
    float angle = angle_degree / 180 * M_PI;
    glVertex2f(x * cos(angle) - (y * sin(angle)), x * sin(angle) + (y * cos(angle)));
    return 0;
}

void DrawSun()
{
    // 원 외곽 그리기
    radius = 0.2f;

    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0f, 0.5f, 0.0f); // 주황색
    glVertex2f(0.0f, 0.0f); // 원의 중심
    for (int i = 0; i <= 360; ++i)
    {
        float angle = i * M_PI / 180.0f;
        glVertex2f(radius * cos(angle), radius * sin(angle));
    }
    glEnd();

    // 원 내부 채우기
    radius = 0.19f;

    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.7f, 1.0f, 0.3f); // 노란색
    glVertex2f(0.0f, 0.0f); // 원의 중심
    for (int i = 0; i <= 360; ++i)
    {
        float M_PI = 3.14f; // 파이 값 설정
        float angle = i * M_PI / 180.0f;
        glVertex2f(radius * cos(angle), radius * sin(angle));
    }
    glEnd();

    // 원 무늬A 그리기
    radius = 0.08f;
    x_offset = -0.08f;

    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0f, 1.0f, 0.4f); // 노란색
    // glVertex2f(x_offset + 0.0f, 0.0f); // 원의 중심
    setVertexRotation(x_offset + 0.0f, 0.0f, Angle);
    for (int i = 0; i <= 360; ++i)
    {
        float M_PI = 3.14f; // 파이 값 설정
        float angle = i * M_PI / 180.0f;
        // glVertex2f(x_offset + radius * cos(angle), radius * sin(angle));
        setVertexRotation(x_offset + radius * cos(angle), radius * sin(angle), Angle);
    }
    glEnd();

    Angle += 0.1;

    // 원 무늬B 그리기
    radius = 0.04f;
    x_offset = 0.1f;
    y_offset = -0.11f;

    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0f, 1.0f, 0.4f); // 노란색
    // glVertex2f(x_offset + 0.0f, y_offset + 0.0f); // 원의 중심
    setVertexRotation(x_offset + 0.0f, y_offset + 0.0f, Angle);
    for (int i = 0; i <= 360; ++i)
    {
        float M_PI = 3.14f; // 파이 값 설정
        float angle = i * M_PI / 180.0f;
        setVertexRotation(x_offset + radius * cos(angle), y_offset + radius * sin(angle), Angle);
    }
    glEnd();
}

void DrawEarth()
{
    x_offset = 0.5f;
    y_offset = 0.1f;

    float size = 0.05f;


    glRotatef(Angle2, 0.0f, 0.0f, 1.0f); // 사각형을 자신을 중심으로 회전

    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 0.4f);
    setVertexRotation(x_offset + size, y_offset + size, Angle2);
    setVertexRotation(x_offset - size, y_offset + size, Angle2);
    setVertexRotation(x_offset - size, y_offset - size, Angle2);
    setVertexRotation(x_offset + size, y_offset - size, Angle2);

    Angle2 += 0.1;

    glEnd();
}

void render()
{
    glPushMatrix();

    DrawSun();
    DrawEarth();

    glPopMatrix();
}

int main(void)
{
    // GLFW 초기화
    if (!glfwInit())
        return -1;

    // 윈도우 생성
    GLFWwindow* window = glfwCreateWindow(800, 800, "Circle Example", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetErrorCallback(errorCallback);
    glfwSetKeyCallback(window, keyCallback);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        render();

        glfwSwapBuffers(window);

    }

    glfwTerminate();
    return 0;
}
