#pragma once

// 스크린 좌표계를 OpenGL 좌표계로 변환하는 함수
float screenToGLX(int screenX);
// 스크린 좌표계를 OpenGL 좌표계로 변환하는 함수
float screenToGLY(int screenY);

// OpenGL 좌표계를 스크린 좌표계로 변환하는 함수
int glToScreenX(float glX);
// OpenGL 좌표계를 스크린 좌표계로 변환하는 함수
int glToScreenY(float glY);

// 스크린 크기를 OpenGL 크기로 변환하는 함수
float screenToGLSizeX(int screenWidth);
// 스크린 크기를 OpenGL 크기로 변환하는 함수
float screenToGLSizeY(int screenHeight);