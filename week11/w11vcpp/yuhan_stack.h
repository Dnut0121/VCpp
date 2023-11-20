#pragma once
#include <iostream>

class Node {
public:
    int data;
    Node* next;

    // ������
    Node(int value);
};

class y_stack {
private:
    Node* top;

public:
    // ������
    y_stack();

    // �Ҹ���
    ~y_stack();

    bool isEmpty() const;

    void push(int value);

    int pop();
};
