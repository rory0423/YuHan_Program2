
#include <iostream>

enum ForeColour {
    Default = 0,
    Black = 30,
    Red = 31,
    Green = 32,
    Yellow = 33,
    Blue = 34,
    Magenta = 35,
    Cyan = 36,
    White = 37,
};

void drawBlock(int objectCode) {
    // 색상 설정
    switch (objectCode) {
    case 1:
        std::cout << "\x1b[037m"; // 흰색
        break;
    case 2:
        std::cout << "\x1b[031m"; // 빨강색
        break;
    case 4:
        std::cout << "\x1b[032m"; // 녹색
        break;
    case 8:
        std::cout << "\x1b[033m"; // 노란색
        break;
    case 16:
        std::cout << "\x1b[036m"; // 청록색
        break;
    case 32:
        std::cout << "\x1b[035m"; // 마젠타색
        break;
    default:
        std::cout << "\x1b[030m"; // 기본 색상
        break;
    }

    // 블록 그리기
    std::cout << "■\n\x1b[037m";
}

int main() {
    std::cout << "화면에 그림을 그리는 프로그램입니다.\n";
    std::cout << "학번: 202327055\n";
    std::cout << "이름: 유재영\n";
    std::cout << "화면에 그릴 물체코드를 입력하세요 (종료를 원하면 64를 입력) :\n";

    int objectCode;
    while (true) {
        std::cin >> objectCode;
        if (objectCode == 64) {
            std::cout << "\x1b[037m프로그램을 종료합니다.\n";
            break;
        }
        drawBlock(objectCode);
    }

    return 0;
}