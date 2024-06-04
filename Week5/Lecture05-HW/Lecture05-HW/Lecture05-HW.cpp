#include <GLFW/glfw3.h>
#include <iostream>

#pragma comment(lib, "Opengl32.lib")


float moveFactorX = 0.0f;
float moveFactorY = 0.0f;
float scaleFactor = 1.0f;

void errorCallback(int error, const char* description)
{
    std::cerr << "GLFW Error: " << description << std::endl;
}

int render()
{
    glBegin(GL_TRIANGLES);

    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f((0.0f + moveFactorX) * scaleFactor, (-0.5f + moveFactorY) * scaleFactor);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f((0.5f + moveFactorX) * scaleFactor, (0.5f + moveFactorY) * scaleFactor);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f((-0.5f + moveFactorX) * scaleFactor, (0.5f + moveFactorY) * scaleFactor);

    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f((0.0f + moveFactorX) * scaleFactor, (1.0f + moveFactorY) * scaleFactor);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f((0.0f + moveFactorX) * scaleFactor, (-0.5f + moveFactorY) * scaleFactor);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f((-0.4f + moveFactorX) * scaleFactor, (-0.75f + moveFactorY) * scaleFactor);

    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f((0.0f + moveFactorX) * scaleFactor, (1.0f + moveFactorY) * scaleFactor);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f((0.0f + moveFactorX) * scaleFactor, (-0.5f + moveFactorY) * scaleFactor);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f((0.4f + moveFactorX) * scaleFactor, (-0.75f + moveFactorY) * scaleFactor);

    glEnd();

    return 0;
}


void cursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
    static double prevX = xpos;
    static double prevY = ypos;

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
    {
        double dx = xpos - prevX;
        double dy = ypos - prevY;

        scaleFactor += dx * 0.001f;
        moveFactorY -= dy * 0.001f;

        prevX = xpos;
        prevY = ypos;
    }
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        double dx = xpos - prevX;
        double dy = ypos - prevY;

        moveFactorX += dy * 0.01f;
        moveFactorY -= dy * 0.01f;

        prevX = xpos;
        prevY = ypos;

    }
}

int main(void)
{
    //glfw라이브러리 초기화
    if (!glfwInit())
        return -1;

    GLFWwindow* window;
    window = glfwCreateWindow(1280, 768, "MuSoeunEngine", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSetErrorCallback(errorCallback);
    glfwSetCursorPosCallback(window, cursorPosCallback);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        render();

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}