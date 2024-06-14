#pragma once
// Base class
class Object {
public:
    float x, y; // Object position
    float width, height; // Object dimensions

    Object(float x, float y, float width, float height)
        : x(x), y(y), width(width), height(height) {}
    virtual void OnCollisionEnter(Object& other) {
    }
    virtual void Render() const = 0; // 순수 가상 함수 렌더링
};

// Derived classes
class Player : public Object {
public:
    Player(float x, float y, float size)
        : Object(x,y, size, size){}
    void OnCollisionEnter(Object& other) override {
    }
    void Render() const override;
};

class EnemyBlock : public Object {
public:
    EnemyBlock(float x, float y, float width, float height)
        : Object(x, y, width, height) {}
    void OnCollisionEnter(Object& other) override {
    }
    void Render() const override;
};

class Floor : public Object {
public:
    Floor(float x, float y, float width, float height)
        : Object(x, y, width, height) {}

    void OnCollisionEnter(Object& other) override {
    }
    void Render() const override;
};

class Star : public Object {
public:
    Star(float x, float y, float width, float height)
        : Object(x, y, width, height) {}
    void OnCollisionEnter(Object& other) override {
    }
    void Render() const override;
};


int PhysicsAABB(Object& A, Object& B)
{
    return 0;
}