#include "yuhan_stack.h"

// Node 클래스의 생성자 구현
Node::Node(int value) : data(value), next(nullptr) {}

// y_stack 클래스의 생성자 구현
y_stack::y_stack() : top(nullptr) {
    printf("생성자 호출\n");
}

// y_stack 클래스의 소멸자 구현
y_stack::~y_stack() {
    printf("소멸자 호출\n");
    while (!isEmpty()) {
        pop();
    }
}

bool y_stack::isEmpty() const {
    return top == nullptr;
}

void y_stack::push(int value) {
    Node* newNode = new Node(value);
    newNode->next = top;
    top = newNode;
}

int y_stack::pop() {
    if (!isEmpty()) {
        int poppedValue = top->data;
        Node* temp = top;
        top = top->next;
        delete temp; 
        return poppedValue;
    }
    else {
        printf("스택이 비었음\n");
        return -1; // 예외 처리를 위한 간단한 값 반환
    }
}