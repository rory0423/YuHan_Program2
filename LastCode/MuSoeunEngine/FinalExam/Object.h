#pragma once

class Object {
public:
    virtual void OnCollisionEnter(Object& other) {}
    virtual void Render() const = 0;

    // 순수 가상 함수로 getX, getY, getWidth, getHeight 정의
    virtual float getX() const = 0;
    virtual float getY() const = 0;
    virtual float getWidth() const = 0;
    virtual float getHeight() const = 0;

protected:
    float x, y; // 오브젝트의 OpenGL 좌표
};

class Player : public Object {
public:
    Player(float screenX, float screenY, float size);

    // Object 클래스의 가상 함수 오버라이드
    void OnCollisionEnter(Object& other) override {}

    void Update(float deltaTime);
    void Render() const override;

    void Jump();

    float getX() const { return x; }
    float getY() const { return y; }
    float getWidth() const { return size; }
    float getHeight() const { return size; }

private:
    float size; // 오브젝트의 크기
    float velocityY;  // 수직 속도
    float width, height;
};

class EnemyBlock : public Object {
public:
    EnemyBlock(float screenX, float screenY, float width, float height);
    ~EnemyBlock(); // 소멸자 추가

    float getX() const { return x; }
    float getY() const { return y; }
    float getWidth() const { return width; }
    float getHeight() const { return height; }

    void setX(float newX) { x = newX; }
    void setY(float newY) { y = newY; }

    bool isActive() const { return active; }
    void setActive(bool isActive) { active = isActive; }

    // Object 클래스의 가상 함수 오버라이드
    void OnCollisionEnter(Object& other) override {}
    void Render() const override;

private:
    float x, y; // OpenGL 좌표
    float width, height; // 오브젝트의 크기 (너비, 높이)
    bool active;
};

class Floor : public Object {
public:
    Floor(float screenX, float screenY, float width, float height);

    float getX() const { return x; }
    float getY() const { return y; }
    float getWidth() const { return width; }
    float getHeight() const { return height; }

    // Object 클래스의 가상 함수 오버라이드
    void OnCollisionEnter(Object& other) override {}
    void Render() const override;

private:
    float width, height; // 오브젝트의 크기 (너비, 높이)
};

// 중력 가속도 (m/s^2)와 점프 속도 (m/s)를 전역 상수로 선언
const float GRAVITY = 9.8f;  // 중력 가속도 (m/s^2)
const float JUMP_VELOCITY = 5.0f;  // 점프 속도 (m/s)

// AABB 충돌 검사 함수
bool PhysicsAABB(const Object& A, const Object& B);