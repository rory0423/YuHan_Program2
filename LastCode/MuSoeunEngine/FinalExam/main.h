#pragma once

// ��ũ�� ��ǥ�踦 OpenGL ��ǥ��� ��ȯ�ϴ� �Լ�
float screenToGLX(int screenX);
// ��ũ�� ��ǥ�踦 OpenGL ��ǥ��� ��ȯ�ϴ� �Լ�
float screenToGLY(int screenY);

// OpenGL ��ǥ�踦 ��ũ�� ��ǥ��� ��ȯ�ϴ� �Լ�
int glToScreenX(float glX);
// OpenGL ��ǥ�踦 ��ũ�� ��ǥ��� ��ȯ�ϴ� �Լ�
int glToScreenY(float glY);

// ��ũ�� ũ�⸦ OpenGL ũ��� ��ȯ�ϴ� �Լ�
float screenToGLSizeX(int screenWidth);
// ��ũ�� ũ�⸦ OpenGL ũ��� ��ȯ�ϴ� �Լ�
float screenToGLSizeY(int screenHeight);