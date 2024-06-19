#pragma once

class Object {
public:
    virtual void OnCollisionEnter(Object& other) {}
    virtual void Render() const = 0;

    // ���� ���� �Լ��� getX, getY, getWidth, getHeight ����
    virtual float getX() const = 0;
    virtual float getY() const = 0;
    virtual float getWidth() const = 0;
    virtual float getHeight() const = 0;

protected:
    float x, y; // ������Ʈ�� OpenGL ��ǥ
};

class Player : public Object {
public:
    Player(float screenX, float screenY, float size);

    // Object Ŭ������ ���� �Լ� �������̵�
    void OnCollisionEnter(Object& other) override {}

    void Update(float deltaTime);
    void Render() const override;

    void Jump();

    float getX() const { return x; }
    float getY() const { return y; }
    float getWidth() const { return size; }
    float getHeight() const { return size; }

private:
    float size; // ������Ʈ�� ũ��
    float velocityY;  // ���� �ӵ�
    float width, height;
};

class EnemyBlock : public Object {
public:
    EnemyBlock(float screenX, float screenY, float width, float height);
    ~EnemyBlock(); // �Ҹ��� �߰�

    float getX() const { return x; }
    float getY() const { return y; }
    float getWidth() const { return width; }
    float getHeight() const { return height; }

    void setX(float newX) { x = newX; }
    void setY(float newY) { y = newY; }

    bool isActive() const { return active; }
    void setActive(bool isActive) { active = isActive; }

    // Object Ŭ������ ���� �Լ� �������̵�
    void OnCollisionEnter(Object& other) override {}
    void Render() const override;

private:
    float x, y; // OpenGL ��ǥ
    float width, height; // ������Ʈ�� ũ�� (�ʺ�, ����)
    bool active;
};

class Floor : public Object {
public:
    Floor(float screenX, float screenY, float width, float height);

    float getX() const { return x; }
    float getY() const { return y; }
    float getWidth() const { return width; }
    float getHeight() const { return height; }

    // Object Ŭ������ ���� �Լ� �������̵�
    void OnCollisionEnter(Object& other) override {}
    void Render() const override;

private:
    float width, height; // ������Ʈ�� ũ�� (�ʺ�, ����)
};

// �߷� ���ӵ� (m/s^2)�� ���� �ӵ� (m/s)�� ���� ����� ����
const float GRAVITY = 9.8f;  // �߷� ���ӵ� (m/s^2)
const float JUMP_VELOCITY = 5.0f;  // ���� �ӵ� (m/s)

// AABB �浹 �˻� �Լ�
bool PhysicsAABB(const Object& A, const Object& B);