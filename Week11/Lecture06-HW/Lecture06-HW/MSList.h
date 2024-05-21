#pragma once

template <typename T>
class MSNode
{
public:
    MSNode(T data) : data(data), next_node(nullptr) {}
    ~MSNode() {}

    T data;
    MSNode* next_node;
};


template <typename T>
class MSList
{
public:
    MSList() : _head(nullptr), _size(0) {}
    ~MSList() {
        while (_head) {
            MSNode<T>* next = _head->next_node;
            delete _head;
            _head = next;
        }
    }

    int get_size() { return _size; }

    void add(T data) {
        MSNode<T>* new_node = new MSNode<T>(data);
        new_node->next_node = _head;
        _head = new_node;
        _size++;
    }

    T& operator[](int index) {
        MSNode<T>* current = _head;
        for (int i = 0; i < index; ++i) {
            current = current->next_node;
        }
        return current->data;
    }

private:
    MSNode<T>* _head;
    int _size;
};

// 템플릿 클래스의 명시적 인스턴스화를 위해 필요한 선언
extern template class MSList<int>;
extern template class MSList<float>;
extern template class MSList<double>;
