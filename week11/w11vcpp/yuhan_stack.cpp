#include "yuhan_stack.h"

// Node Ŭ������ ������ ����
Node::Node(int value) : data(value), next(nullptr) {}

// y_stack Ŭ������ ������ ����
y_stack::y_stack() : top(nullptr) {
    printf("������ ȣ��\n");
}

// y_stack Ŭ������ �Ҹ��� ����
y_stack::~y_stack() {
    printf("�Ҹ��� ȣ��\n");
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
        printf("������ �����\n");
        return -1; // ���� ó���� ���� ������ �� ��ȯ
    }
}